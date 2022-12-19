# MIT6.S081-2020-labs
MIT6.S081实验官方纯净源代码，原作者（Calvin Haynes）转载于MIT官方仓库git clone git://g.csail.mit.edu/xv6-labs-2020（未在GitHub上放出），在此Fork过来，感谢原作者Calvin Haynes以及MIT6.S081授课团队。

## 学习目标
- 加深对**操作系统**的理解，从更底层的视角了解并实现操作系统的相关功能
- 加深对**UNIX**的理解，熟悉UNIX的常用指令
- 加深对C/C++的理解
- 在工作简历上作为一段项目经历  

## 分支说明

- `main`分支：
- 记录自己的学习进度和心得，督促自己不断学习，打好基础，为明年工作做好准备，冲冲冲！
  - **lab1:Util**
    - 开始日期：2022.12.04
    - 完成日期：2022.12.15
    - 心得：
      - 环境配置：万事开头难啊，配置实验的运行和调试环境花了我好几天的时间，由于电脑的CPU是M2，网上能够搜到的参考资料十分有限（CSDN真是个垃圾），因此踩了不少的坑，期间一度认为M2无法兼容xv6，差点放弃，好在最后还是比较完美的解决了环境配置问题。不过反过来想一下，这段折磨的经历或许可以帮助我更好地坚持下去。~~在即将放弃的时候能够提醒自己计算一下沉没成本。~~
      - 额外的小知识：我对C++的接触比较少（仅限于刷算法题），学习的也不够系统，更是没有任何C++相关的项目经历，这间接导致了我在环境配置中遇到了很多奇怪的问题，为此我不得不花费额外的时间去学习相关的知识，比如：Makefile，IDE配置和远程调试，Git。这些实用型的小知识不需要太过全面地学习，但是从0到1是必要的，之后的话可以在工作中继续熟能生巧。
      - 学习收获（以后将用知识导图展现）：第一章主要还是在"管中窥豹"，介绍了一些常用的系统调用（pipe，fork，exec，wait等等），以及基于这些系统调用实现的shell功能（IO重定向，管道）。
      - 实验收获（以后将用知识导图展现）：课程中学到的知识其实是有限且抽象的，做实验、阅读源码和参考文档会带来更多的收获，第一个lab并不难，需要注意的是：1.管道通讯中要及时关闭不必要的文件描述符。 2.大多数命令都不接受标准输入作为参数，只能直接在命令行输入参数，这会导致无法用管道命令传递参数。

  - **lab2:system calls**
    - 开始时间：2022.12.20
    - 完成时间：进行中。。。
    - 进度：
      - | index  | lab| state|
        | --- | :--- | :---: |
        | 1  | System call tracing| X |
        | 2 | Sysinfo| X |
      
- `其他分支`：
  - 一个分支对应一个lab，会在make grade取得100分后上传上来，每份代码都会包含详细的注释，方便自己复习。

## 环境说明
- mac os 13.1
- Clion 2021
- Apple M2
