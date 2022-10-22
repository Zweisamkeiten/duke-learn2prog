---
date created: 2022-10-10 20:27
date updated: 2022-10-10 20:38
---

## Make Makefile

真正的大型程序,重新编译整个程序将要花费大量的时间.

make 实用程序，不仅可以自动执行此过程，还可以简化一般的编译程序。 make 命令读取一个名为 Makefile 的文件（尽管您可以要求它读取一个不同名称的输入文件），该文件指定如何编译您的程序。 具体来说，它命名了 _的目标_ 可以制作 _、它们的依赖关系_ 以及制作目标的 _规则_ 。

make 首先检查目标是否是最新的。 检查目标是否是最新的需要检查目标所依赖的所有文件本身是否都是最新的，并且它们都不比目标更新。 例如，整个程序的目标可能依赖于许多目标文件。 如果任何此类文件本身不是最新的（例如，目标文件可能依赖于 _的.c_ 刚刚更改 文件），则首先重建它。 然后 make 遵循为目标指定的任何规则，以从其依赖项构建它。 如果目标已经是最新的，那么它什么也不做。

emacs "C-c C-v" 在emacs中编译

make 的输入是一个 Makefile，它包含一个或多个规则，这些规则指定如何从其先决条件（它所依赖的文件）生成目标。 该规则由目标规范、冒号和必备文件列表组成。 在先决条件列表之后，有一个换行符，然后是从先决条件重建该目标所需的任何命令。 命令可能出现在多行； 但是，每一行必须以 TAB 字符开头（多个空格不起作用，并且不小心使用它们而不是 TAB 通常是 Makefile 问题的根源）。

运行 make 时，可以指定要构建的特定目标（如果不指定，make 使用 Makefile 中的第一个目标作为默认目标）。

一旦一个目标文件依赖的所有文件都被确认为最新, make 会检查该目标是否需要被重建. 首先,检查目标文件是否存在.如果不存在, built. 如果存在,比较上一次修改的时间与其所有前置依赖文件的上次修改时间. 如果依赖文件新于目标文件,则需要重建.

```make
myProgram: oneFile.o anotherFile.o
    gcc -o myProgram oneFile.o anotherFile.o
oneFile.o: oneFile.c oneHeader.h someHeader.h
    gcc -std=gnu99 -pedantic -Wall -c oneFile.c
anotherFile.o: anotherFile.c anotherHeader.h someHeader.h
    gcc -std=gnu99 -pedantic -Wall -c anotherFile.c
```

### 变量

```make
CFLAGS=-std=gnu99 -pedantic -Wall
myProgram: oneFile.o anotherFile.o
    gcc -o myProgram oneFile.o anotherFile.o
oneFile.o: oneFile.c oneHeader.h someHeader.h
    gcc $(CFLAGS) -c oneFile.c
anotherFile.o: anotherFile.c anotherHeader.h someHeader.h
    gcc $(CFLAGS) -c anotherFile.c
```

定义了一个变量 CFLAGS，我们将其设置为我们想要的编译标志。 然后，我们通过将其名称放在规则中的 $() 中来使用该变量。

需要注意修改 Makefile 文件并不会使 make 程序认为其中的目标文件需要重新构建

### Clean

该目标是一个特殊的目标 `phony`, 为了移除所有已编译的程序,所有的对象文件 等等.

该目标用于强制重新构建整个程序, 或者如果您需要清理目录，只留下源文件

```make
.PHONY: clean
clean:
	rm -f myProgram *.o *.c~ *.h~
```

`.PHONY: clean` 告诉 make, _clean_ 是一个虚假的目标, 实际上不希望它创建一个名为 `clean` 的文件, 也不想认为它是最新的而被跳过(因为如果存在一个名为`clean`的文件,它会被认为是最新的而被跳过).

如果需要多个虚假目标 `.PHONY: clean depend`

### Generic rules 通用规则

一个通用规则让我们指定我们希望能够从 (something).c 构建 (something).o，其中我们用百分号 (%) 表示某物。

```make
# A good start, but we lost the dependencies on the header files
CFLAGS=-std=gnu99 -pedantic -Wall
myProgram: oneFile.o anotherFile.o
    gcc -o myProgram oneFile.o anotherFile.o
%.o: %.c
    gcc $(CFLAGS) -c $<
.PHONY: clean
clean:
    rm -f myProgram *.o *.c~ *.h~
```

用一个通用规则替换了每个目标文件的两个规则。 它指定如何从同名文件中生成以 .o 结尾的文件，但该同名文件使用 .c为后缀。在此规则中，我们不能编写源文件的文字名称，因为它会随规则的每个实例而变化。 相反，我们必须使用特殊的内置变量 $<，它将设置为规则的第一个先决条件的名称（在本例中为 .c 文件的名称）。

这样的修改使得目标文件不再依赖相关的头文件.如果要更改头文件,make将不会重建所有相关的目标文件. 当然可以使得每一个目标文件都依赖所有的头文件(例如 `%.o: %.c *.h`), 但这样会使得更改头文件时,会使得所有目标文件都重建. 因此可以通过在 makefile中添加额外的依赖信息来更好解决

```make
# This fixes the problem
CFLAGS=-std=gnu99 -pedantic -Wall
myProgram: oneFile.o anotherFile.o
    gcc -o myProgram oneFile.o anotherFile.o
%.o: %.c
    gcc $(CFLAGS) -c $<
.PHONY: clean
clean:
    rm -f myProgram *.o *.c~ *.h~
oneFile.o: oneHeader.h someHeader.h
anotherFile.o: anotherHeader.h someHeader.h
```

make 理解我们只是提供了额外的依赖信息，因为我们没有指定任何命令。

手动管理所有这些依赖关系信息既乏味又容易出错。
有一个名为 makedepend 的工具将编辑 Makefile 以将所有这些信息放在最后。 在其最简单的用法中，makedepend 将所有源文件（即所有 .c 和/或 .cpp 文件）作为参数，并编辑 Makefile。 也可以给它多种选项，比如 -I path 告诉它在指定路径中查找包含文件。 有关详细信息，请参阅 man makedepend。

### 内置通用规则

一些通用规则非常普遍，以至于它们内置在 make 中，甚至不必编写它们。

以使用 make -p 查看所有规则（包括内置规则和 Makefile 指定的规则）, 但是如果是在一个makefile目录下,它也会照常构建该makefile.

可以执行 **make -p -f/dev/null** 来使用特殊文件 /dev/null 作为我们的 Makefile（从 /dev/null 结果读取立即进入文件末尾，因此结果将是一个没有规则的 Makefile，因此它不会做任何事情）。

```make
%.o: %.c
# commands to execute (built-in):
    $(COMPILE.c) $(OUTPUT_OPTION) $<
```

COMPILE.c 和 OUTPUT_OPTION 的定义 包含在 make -p 的输出中：

```make
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
OUTPUT_OPTION = -o $@
```

默认情况下，CFLAGS（C 编译器的标志）和 CPPFLAGS（C 预处理器的标志 143）以及 TARGET_ARCH（指定目标体系结构的标志）为空。 默认情况下，CC（C 编译器命令）是 cc（取决于我们的系统配置方式，它可能是也可能不是 gcc）。 任何这些变量（或任何其他变量）的默认值都可以通过在我们的 Makefile 中指定它们的值来覆盖。 请注意，OUTPUT_OPTION 中的 _$@_ 是一个特殊变量，它是当前目标的名称（很像 `\$<` 是第一个依赖文件的名称）。

基本上归结为默认规则是：cc -c -o something.o something.c

```make
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall
myProgram: oneFile.o anotherFile.o
    gcc -o myProgram oneFile.o anotherFile.o
.PHONY: clean depend
clean:
    rm -f myProgram *.o *.c~ *.h~
depend:
    makedepend anotherFile.c oneFile.c
# DO NOT DELETE
anotherFile.o: anotherHeader.h someHeader.h
oneFile.o: oneHeader.h someHeader.h
```

指定了我们想要使用 gcc 作为 C 编译器 (CC)，并指定了我们想要的 CFLAGS。 现在，当我们尝试从 C 文件编译目标文件时，默认规则将导致

**gcc -std=gnu99 -pedantic -Wall -c -o something.o something.c**

_depend_ 使用我们正在使用的两个 C 源文件运行 makedepend。 # DO NOT DELETE 行和它下面的所有内容都是 makedepend 在我运行 makedepend 时添加到我们的 Makefile 中的。

### 内置函数

现在仍然需要在几个地方手动列出源文件和目标文件。 如果要添加一个新的源文件，但忘记更新 makedepend 下所要搜索的c文件，那么当运行 makedepend 时，我们最终不会得到该文件的正确依赖项。 同样，我们可能忘记在正确的位置添加目标文件（例如，如果我们将它添加到编译命令行，而不是整个程序的依赖项，我们可能不会在需要时重建该目标文件）。

可以通过使用 make 的一些内置函数来自动计算当前目录中的 .c 文件集，然后从该列表中生成目标对象文件的列表来解决这些问题。 make 中函数调用的语法是 $ (functionName arg1, arg2, arg3)。 我们可以使用  $(wildcard pattern) 函数来生成当前目录下的 .c 文件列表：SRCS = $ (wildcard \*.c)。 然后我们可以使用  $(patsubst pattern, replacement, text) 函数将 .c 结尾替换为 .o 结尾：OBJS = $ (patsubst %.c, %.o,  $(SRCS))。 完成此操作后，我们可以在 Makefile 中使用 $ (SRCS) 和  $(OBJS)：

```make
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
myProgram: $(OBJS)
    gcc -o $@ $(OBJS)
.PHONY: clean depend
clean:
    rm -f myProgram *.o *.c~ *.h~
depend:
    makedepend $(SRCS)
# DO NOT DELETE
anotherFile.o: anotherHeader.h someHeader.h
oneFile.o: oneHeader.h someHeader.h
```

可以更花哨一点。 在实际项目中，我们可能希望构建代码的调试版本（不进行优化，使用 -ggdb3 来打开调试信息——有关调试的更多信息，请参见下一个模块），以及我们代码的优化版本，它将运行得更快（编译器努力工作以改进它生成的指令，但这些转换通常会使调试变得相当困难）。 我们可以在调试标志和优化标志之间来回更改我们的 CFLAGS，并记住每次切换时都要clean。 但是，我们也可以只设置 Makefile 来构建调试和优化的目标文件以及具有不同名称的二进制文件：

```make
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -O3
DBGFLAGS = -std=gnu99 -pedantic -Wall -ggdb3 -DDEBUG
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
DBGOBJS=$(patsubst %.c,%.dbg.o,$(SRCS))
.PHONY: clean depend all
all: myProgram myProgram-debug
myProgram: $(OBJS)
    gcc -o $@ -O3 $(OBJS)
myProgram-debug: $(DBGOBJS)
    gcc -o $@ -ggdb3 $(DBGOBJS)
%.dbg.o: %.c
    gcc $(DBGFLAGS) -c -o $@ $<
clean:
    rm -f myProgram myProgram-debug *.o *.c~ *.h~
depend:
    makedepend $(SRCS)
    makedepend -a -o .dbg.o  $(SRCS)
# DO NOT DELETE
anotherFile.o: anotherHeader.h someHeader.h
oneFile.o: oneHeader.h someHeader.h
```

### 并行计算

make 的一个有用特性，尤其是在现代多核系统上，是让它并行运行独立任务的能力。 如果你给 make -j 选项，它会要求它并行运行尽可能多的任务。 您可能希望要求它在任何给定时间将并行任务的数量限制为特定数量，您可以通过将该数量指定为 -j 选项的参数来做到这一点（make -j8 最多可并行运行 8 个任务）。 在大型项目中，这可能会对构建所需的时间产生重大影响。
