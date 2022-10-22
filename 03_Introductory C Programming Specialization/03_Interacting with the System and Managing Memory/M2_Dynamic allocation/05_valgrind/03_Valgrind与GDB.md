---
date created: 2022-10-19 21:56
date updated: 2022-10-22 17:05
---

## valgrind 与 GDB

同时运行 GDB 和 Valgrind，并让 Valgrind 在遇到错误时告诉 GDB，将控制权交给 GDB。
#valgrind #gdb #debug
使用选项 **--vgdb=full --vgdb-error=0** _运行 Valgrind ，_ 那么 Valgrind 将在遇到第一个错误时停止并将控制权交给 GDB

```
==24099== (action at startup) vgdb me ...
==24099==
==24099== TO DEBUG THIS PROCESS USING GDB: start GDB like this
==24099==   /path/to/gdb ./a.out
==24099== and then give GDB the following command
==24099==   target remote | /usr/lib/valgrind/../../bin/vgdb --pid=24099
==24099== --pid is optional if only one valgrind process is running
```

此时，Valgrind 已经启动了程序，但还没有进入 main——它正在等待你启动 GDB 并将其连接到 Valgrind。 我们可以通过运行 GDB（在单独的终端或 Emacs 缓冲区中）然后将 Valgrind 给我们的目标命令复制并粘贴到 GDB 的命令提示符中来实现：

```
(gdb) target remote | /usr/lib/valgrind/../../bin/vgdb --pid=24099
Remote debugging using | /usr/lib/valgrind/../../bin/vgdb --pid=24099
relaying data between gdb and process 24099
Reading symbols from /lib64/ld-linux-x86-64.so.2...Reading symbols from ...
done.
Loaded symbols for /lib64/ld-linux-x86-64.so.2
0x00000000040012d0 in _start () from /lib64/ld-linux-x86-64.so.2
(gdb)
```

给 GDB 一个 **continue** 命令，让它一直运行，直到 Valgrind 遇到错误。 此时，Valgrind 将中断程序并将控制权返回给 GDB。 你现在可以给 GDB 任何你想要的命令，这样你就可以调查你的程序的状态。

通过 **monitor** 命令运行一些新命令。 例如，如果我们试图调试与指针相关的错误，并且想知道哪些变量仍然指向特定的内存位置，我们可以使用 **monitor who_points_at** 命令来做到这一点：

```
gdb) monitor who_points_at 0x51fc040
==24303== Searching for pointers to 0x51fc040
==24303== *0xfff000450 points at 0x51fc040
==24303==  Location 0xfff000450 is 0 bytes inside local var "p"
==24303==  declared at example.c:6, in frame #0 of thread 1
```

Memcheck还有许多其他 **监控** 可用的 的更多信息，请参阅 [http://valgrind.org/docs/manual/mc-manual.html#mc-manual.monitor-commands 。](http://valgrind.org/docs/manual/mc-manual.html#mc-manual.monitor-commands) 命令。 有关可用 **监视器** 命令及其参数
