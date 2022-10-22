---
date created: 2022-10-12 10:29
---

`gdb -i=mi`相当于 `gdb --interpreter=mi`.

简而言之， `--interpreter=mi`使 `gdb`呈现面向机器的文本界面，而不是没有它的面向人的命令提示符。 Emacs 的 `gud`buffer 解析来自该接口的输出，并向您呈现类似于普通 gdb 接口的内容。

这 `--interpreter`标志记录 [在这里](https://sourceware.org/gdb/onlinedocs/gdb/Mode-Options.html#Mode-Options) ，并且 `GDB/MI`接口记录 [在这里](https://sourceware.org/gdb/onlinedocs/gdb/GDB_002fMI.html) 。 那 `-i`是一个别名 `--interpreter` [这里](https://sourceware.org/gdb/onlinedocs/gdb/Interpreters.html) 。

C-h m

描述 Emacs 的 GDB 模式的特点。

M-s

执行到另一个源代码行，例如 GDB `step`命令; 还 更新显示窗口以显示当前文件和位置。

M-n

在这个函数中执行到下一个源代码行，跳过所有函数 调用，如 GDB `next`命令。 然后更新显示窗口 显示当前文件和位置。

M-i

执行一条指令，如 GDB `stepi`命令; 更新 相应地显示窗口。

M-x gdb-nexti

使用 GDB 执行下一条指令 `nexti`命令; 更新 相应地显示窗口。

C-c C-f

执行直到退出选定的堆栈帧，如 GDB `finish`命令。

M-c

继续执行你的程序，比如 GDB `continue`命令。 _警告：_ 在 Emacs v19 中，这个命令是 C-c C-p.

M-u

增加数字参数指示的帧数 （参见 GNU Emacs 手册中的 “数字参数”部分）， 像 GDB `up`命令。 _警告：_ 在 Emacs v19 中，这个命令是 C-c C-u.

M-d

减少数字参数指示的帧数，例如 广发银行 `down`命令。 _警告：_ 在 Emacs v19 中，这个命令是 C-c C-d.

C-x &

读取光标所在的数字，并插入到末尾 GDB I/O 缓冲区。 例如，如果你想反汇编代码 在之前显示的地址周围，键入 disassemble; 然后将光标移动到地址显示，然后拿起 论据 `disassemble`通过键入 C-x &. 您可以通过定义列表的元素来进一步自定义 `gdb-print-command`; 一旦定义，您可以格式化或 否则进程号由 C-x &在他们之前 插入。 一个数字参数 C-x &表示你 希望特殊格式，并且还充当索引来选择 列表。 如果列表元素是字符串，则要插入的数字是 使用 Emacs 函数格式化 `format`; 否则数 作为参数传递给相应的列表元素。
