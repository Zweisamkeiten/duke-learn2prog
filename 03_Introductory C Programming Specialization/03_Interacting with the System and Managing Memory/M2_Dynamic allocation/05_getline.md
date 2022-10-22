---
date created: 2022-10-19 19:13
date updated: 2022-10-19 20:09
---

#getline

## getline

fgets 允许您将字符串读入预先分配的缓冲区，指定要读取的字符串的最大大小（即缓冲区中有多少空间）

getline 可以读取任意长度字符串 **#include <stdio.h>**

![](attachments/Pasted%20image%2020221019191447.png)
#newget #important
**getline** 从 第三格参数 stream 指定的文件中读取一行. 通过从文件中重复读取字符, 直到其读取到字符 `\n`, 它表示一行的结尾. 当它读取每个字符是, 它会将字符复制到内存的缓冲区中. 读取换行符后, getline 防止一个 `\0` 字符, 表示字符串的结尾.

#newget #important
getline 根据需要为字符串分配空间. getline 使用 **malloc** 和 **realloc** 来分配/扩大缓冲区**linep** 参数指向一个指针, 如果 `*linep` 为 `NULL` , getline malloc 一个新的缓冲区. 如果 `*linep` 不为 `NULL`, 则 getline 使用该缓冲区 (长度为 `*n` 字节). 如果初始缓冲区不够长,  getline 会根据需要重新分配缓冲区. 每当 getline malloc 或重新分配缓冲区时, 它都会更新 `*n` 以反映分配的字节数. 更新 `*linep` 指向新缓冲区. 当 getline 函数返回时, `*linep` 是一个指向从文件中读取的字符串的指针.

getline 函数在错误（包括文件结尾）时返回 -1，在成功时返回读取的字节数（不包括空终止符字节）请注意，返回类型是 ssize_t，它代表“有符号 size_t”——即有符号整数类型，其字节数与 size_t 相同（因此它可以返回 -1）

getline 函数有两种使用方式。

1. 用户可以向 getline 提供一个指向 malloced 缓冲区 `*linep` 的指针，该缓冲区的大小由 `linecapp` 指向 。 如果正在读取的行大于 `*linecapp` ，getline 将为用户执行重新分配并修改 `*linep` (指向新重新分配的区域)和 `*linecapp`( 新重新分配的缓冲区的大小的值)
2. 用户可以 为getline提供`NULL`缓冲区， `linep` 为指向 NULL 的指针的 linep (linep**不能** 为 NULL，但 `*linep` 可以为 `NULL`)。 在这种情况下，getline 将为用户执行 malloc 并相应地修改 `*linep` (指向新分配的区域)和 `*linecapp` (新分配的缓冲区的大小)的值 [加深理解](../../../languages/c/getline.md#^02bdc1)
3. 这两种方式可以一起使用 _——即_ ，可以编写一个循环，其中第一次不提供缓冲区，并且在后续迭代中重复使用相同的缓冲区。

```c
// getline 用法
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  size_t sz = 0;
  ssize_t len = 0;
  char *line = NULL;
  FILE *f = fopen("names.txt", "r");
  while ((len = getline(&line, &sz, f)) >= 0) {
    printf("%s", line);
  }

  free(line);
  return EXIT_SUCCESS;
  return 0;
}
```

![](attachments/Pasted%20image%2020221019193937.png)
结合getline 和 realloc 来构造字符串数组 #important

#newget
`getline`不是标准 C 库函数, 这些函数来自平台的 libc, glibc 2.10

[`getline()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html)不在 C 标准库中，而是 POSIX 2008 扩展。 通常，它可以与 POSIX 兼容的编译器一起使用，因为宏 _POSIX_C_SOURCE_ 将使用适当的值定义。 您可能有以前的旧编译器 `getline()`是标准化的，在这种情况下这是一个 GNU 扩展，你必须 `#define _GNU_SOURCE`前 `#include <stdio.h>`要启用它，并且必须使用与 GNU 兼容的编译器，例如 gcc。
`gcc 04_getline.c -o getline -std=gnu99`
![](attachments/Pasted%20image%2020221019195556.png)
或者`#define _GNU_SOURCE`前 `#include <stdio.h>`要启用它
![](attachments/Pasted%20image%2020221019195741.png)

![](attachments/Pasted%20image%2020221019200753.png)
getline 从标准输出读取字符会假定至少有4个字节

![](attachments/Pasted%20image%2020221019200846.png)
getline 分配的空间是 大于等于 sz的.

**line** 将指向一个数组，该数组被分配以保存 _前 7 个字符中带有 'H' 'e' 'l' 'l' 'o' '\n' '\0' 的sz_ 字符。 数组的任何剩余元素的值都是未定义的。
