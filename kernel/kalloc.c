// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);
extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

//struct kmem{
//    struct spinlock lock;
//    struct run *freelist;
//} kmem

// lab8.1 为每个CPU维护一个空闲列表
struct kmem{
  struct spinlock lock;
  struct run *freelist;
} kmem[NCPU];

void
kinit()
{
    // lab8.1 为每个CPU分配一个锁
    for (int i = 0; i < NCPU; ++i) {
        initlock(&kmem[i].lock, "kmem");
    }
    freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
    char *p;
    p = (char*)PGROUNDUP((uint64)pa_start);
    // freerange将所有可用内存分配给运行freerange的CPU。
    for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
        kfree(p);
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  // lab8.1 使用当前cpu的空闲列表和锁
  push_off();
  int id = cpuid();

  acquire(&kmem[id].lock);
  r->next = kmem[id].freelist;
  kmem[id].freelist = r;
  release(&kmem[id].lock);

  pop_off(); // 只有在中断关闭时调用它并使用其结果才是安全的
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  // lab8.1 使用当前cpu的空闲列表和锁
  push_off();
  int id = cpuid();

  acquire(&kmem[id].lock);
  r = kmem[id].freelist;
  if(r)
    kmem[id].freelist = r->next;
  else{ // lab8.1 当前CPU无可用内存时“窃取”另一个CPU空闲列表的一部分
      for (int i = 0; i < NCPU; ++i) {
          if (kmem[i].freelist)
          {
              r = kmem[i].freelist;
              kmem[i].freelist = kmem[i].freelist->next;
              break;
          }
      }
  }
  release(&kmem[id].lock);

  pop_off();

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}
