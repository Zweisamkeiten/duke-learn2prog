---
date created: 2022-10-19 22:15
---

## memcheck.h

程序中与 Valgrind 的工具进行交互。 例如，我们可能想要显式地检查一个值是否在程序中的某个点被初始化（ _例如_ ，作为调试有关未初始化值的错误的一部分）。 Valgrind 提供了头文件，例如 **memcheck.h** ，其中包含各种用于此目的的宏。 例如，我们可以将之前用作未初始化值示例的函数更改为

```c
void f(int x) {
	int y;
	int z = x + y;
	VALGRIND_CHECK_MEM_IS_DEFINED(&z,sizeof(z));
	printf("%d\n", z);
}
```

现在，当我们在 valgrind 中运行这个程序时，我们会更直接地收到错误消息：

```
==12425== Uninitialised byte(s) found during client check request
==12425==    at 0x4007C9: f (uninit4.c:8)
==12425==    by 0x400811: main (uninit4.c:17)
==12425==  Address 0xfff000410 is on thread 1's stack
==12425==  Uninitialised value was created by a stack allocation
==12425==    at 0x400765: f (uninit4.c:5)
```

Memcheck 的许多功能都可以通过这些宏获得。 大多数其他工具都有类似的头文件，以便程序直接与它们交互。 请参阅 [http://valgrind.org/docs/manual/mc-manual.html#mc-manual.clientreqs 。](http://valgrind.org/docs/manual/mc-manual.html#mc-manual.clientreqs) 有关详细信息，
