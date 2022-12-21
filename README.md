# lab2:system calls
### 开始日期：2022.12.20
### 完成日期：2022.12.21

- ### `心得`
  - 在lab1中，我在user下通过系统调用完成了几个小程序的编写，而在lab2中，我需要在kernel下完成系统调用的编写。
  - 系统调用都需要在核心态下运行，因此我需要了解：1.用户程序如何完成系统调用。 2.用户态的数据与核心态的数据如何完成交换。 
    - 1.系统调用的完成：汇编代码通过使用RISC-V的ecall指令触发中断，将程序从用户态切换到内核态，并将待执行的系统调用函数编码存放在寄存器a7内。ecall会触发中断后，中断代码会将寄存器中的数据保存到当前进程的中断帧trapframe中。进入核心态之后，syscall.c会读取trapframe中保存的寄存器值，取出a7，映射到相应的系统调用函数并运行。
    - 2.数据交换：
      - 用户态 -> 核心态：用户程序会把系统调用所需的参数放在寄存器a0和a1内，然后复制到当前进程的trapframe内，系统调用直接读取trapframe的a0和a1，即可得到用户态的数据。如果用户程序传递的是一个指针，walkaddr会检查用户提供的地址是否为当前进程用户地址空间的一部分，因此程序不能欺骗内核读取其他内存。
      - 核心态 -> 用户态：用户程序会把地址作为参数传给系统调用，该地址将用来接受需要的数据。而系统调用的返回值将只作为程序是否成功运行的标志，返回值将保存在trapframe的a0中。
      - 谨慎地完成数据交换可以很好地保证操作系统的"防御性"以及程序之间的"隔离性"。
- ### `任务1 Trace`
  - 描述：添加一个系统调用跟踪功能。
  - syscall中监测到trace函数后，将当前进程的proc结构体中的mask设置为待追踪的系统调用函数编号。
  - 为了跟踪子进程，需要将mask值赋给子进程。
  - 追踪到目标系统调用后，等待该系统调用返回，然后从trapframe->a0中输出他的返回值。
  - 收获：熟悉了系统调用的流程以及用户态与核心态之间数据交流的方式。
- ### `任务2 Sysinfo`
  - 描述：添加一个系统调用用来收集系统的运行信息，包括空闲内存量和运行的进程数。
  - sysinfo需要将一个结构体复制回用户空间，这涉及到核心态到用户态的数据交换，需要使用argaddr()把需要返回的数据放入用户程序提供的地址内。
  - 空闲内存使用量：阅读kalloc.c代码可以发现，内存是通过链表进行保存的，所有空闲的内存保存在freelist内，通过遍历整个链表即可获得当前空闲的内存数。
  - 运行的进程数量：阅读proc.c代码可以发现，proc数组保存了所有的进程状态，遍历数组，找到所有状态不为UNUSED的进程并统计数量即可。
  - 收获：任务2使我进一步加深了核心态到用户态的数据传输方式的理解，并且还涉及到了内存管理和进程管理，这部分还没有系统地进行学习，好在题目不难，应该是在抛砖引玉吧。
- ### `xv6启动过程初探`
