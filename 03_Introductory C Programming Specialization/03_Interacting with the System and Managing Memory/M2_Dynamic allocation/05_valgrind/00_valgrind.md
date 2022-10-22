---
date created: 2022-10-19 20:37
date updated: 2022-10-19 21:38
---

# Valgrind 的内存检查

## Valgrind 的内存检查

编译器可以做的仅限于代码的静态分析， _即_ 它可以在不运行代码或不知道程序输入的情况下做的事情。 因此，编译器无法检测到许多类型的问题。 这些类型的问题通常是通过在出现问题的测试用例上运行代码来发现的。

但是，仅仅因为问题发生并不意味着它对测试人员产生了有用的结果。 有时，问题可能会在没有可观察到的结果的情况下发生，可观察到的结果只是在很久以后才出现，或者可观察到的结果很难追溯到实际原因。 所有这些可能性都使测试和调试变得更加困难。

理想情况下，我们希望立即检测到任何问题并报告有关所发生情况的有用信息。 当我们直接运行一个 C 程序时，不会发生这样的事情，因为编译器不会为我们插入任何额外的检查或报告。 但是，有一些工具可以在我们运行程序时执行额外的检查，以帮助我们测试和调试程序。 就是一个这样的工具 _Valgrind_ ，特别是它的 _Memcheck_ 工具。

Valgrind 实际上是一组工具，它们的设计目的是可以根据需要添加更多工具。 但是，我们主要对 Memcheck 感兴趣，它是默认工具，将执行我们需要的检查。 每当您测试和调试代码时，都应该在 Valgrind 中运行它 （称为“valgrinding your program”）。 虽然 valgrinding 您的程序比直接运行程序要慢得多，但它将极大地帮助您进行测试和调试。 您应该修复 valgrind 报告的任何错误，即使它们似乎不是问题。

要“验证您的程序”，请运行 **valgrind** 命令，并将您的程序名称作为参数给它（Memcheck 是默认工具）。 如果您的程序采用命令行参数，只需将它们作为程序名称后的附加参数传递。 例如，如果您通常运行 **./myProgram hello 42** ，则改为运行 **valgrind ./myProgram hello 42** 。 为了获得最大的好处，您应该在程序中使用调试信息进行编译（将 -g 或 -ggdb3 选项传递给 gcc）。

当你运行 Valgrind 时，你会得到一些通常看起来像这样的输出：

```
==11907== Memcheck, a memory error detector
==11907== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==11907== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==11907== Command: ./myProgram hello 42
==11907==
==11907==
==11907== HEAP SUMMARY:
==11907==     in use at exit: 0 bytes in 0 blocks
==11907==   total heap usage: 2 allocs, 2 frees, 128 bytes allocated
==11907==
==11907== All heap blocks were freed -- no leaks are possible
==11907==
==11907== For counts of detected and suppressed errors, rerun with: -v
==11907== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

**这里以`==11907==`开头的每一行** 都是 Valgrind 输出的一部分。 注意，当你运行它时，你得到的数字会有所不同（它是进程ID，所以每次都会改变）。 Valgrind 打印一条消息告诉你它在做什么（包括它正在运行的命令），然后它运行你的程序。 在这种情况下，程序没有在 **stdout** 上产生任何输出； 但是，如果确实如此，则该输出将与 Valgrind 的输出穿插。 也没有 Valgrind 错误——如果有，它们会在发生时被打印出来。 最后，Valgrind 总结了我们的动态分配和错误。 最后一行显示我们“干净地进行了 valgrind”——我们没有 Valgrind 可以检测到的错误。 如果我们没有干净地进行 valgrind，即使输出看起来是正确的，我们也应该修复我们的程序。

请注意，如果我们的程序有错误，Valgrind 会报告它们并继续运行（直到达到某个错误限制）。 每当您遇到多个错误时，您应该从第一个错误开始，修复它，然后再转到下一个错误。 很像编译器错误，后来的问题可能是早期错误的结果。

新手程序员经常遇到的一个常见误解是，他们应该只在调试了他们的程序之后才运行 Valgrind，否则他们认为它可以工作。 但是，如果您在整个测试和调试过程中使用 Valgrind 的 Memcheck，您会发现调试过程要容易得多。 您可能会发现，您几个小时都无法弄清楚的奇怪或令人困惑的错误实际上是由您之前没有注意到的一个微妙问题引起的，而 Valgrind 可能已经为您找到了。 请注意，Valgrind 不会与使用 `-fsanitize=address` 编译的代码“共同很好地工作”，因此您应该在没有该选项的情况下进行编译以对您的代码进行 valgrind。 确保这两种工具都无法发现代码中的任何问题可能是一个好主意，因为它们可以检测到不同的问题。

我们将在这里介绍基础知识，但建议进一步阅读 Valgrind 用户手册：http: [//valgrind.org/docs/manual/manual.html](http://valgrind.org/docs/manual/manual.html) 以获取更多信息。

[01_未初始化的值](01_未初始化的值.md)

