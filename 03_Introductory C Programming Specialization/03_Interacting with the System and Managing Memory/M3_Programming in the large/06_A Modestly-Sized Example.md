---
date created: 2022-10-20 17:26
date updated: 2022-10-20 17:31
---

首先是我们可以定义问题中涉及的几种类型。 该视频介绍了我们如何看待 **student_t** 和 **roster_t** 类型。 我们可以类似地处理我们需要的内容来表示 **classes_t** 类型的所有类的列表。 然后我们会提出以下声明：

提出了 **main** 的通用算法

```
Read the input from the file named by argv[1] (call this r)
Make a list of all of the (unique) class names (call this result c)
Write one output file per class (from c and r)
```

要对这个算法做一些改动。 首先，我们会注意到我们没有写下任何关于返回答案的信息——然而，main 总是返回一个 int。 在这种情况下，我们应该返回 EXIT_SUCCESS。 当我们仔细考虑我们的其他函数（我们将要编写的）会做什么时，我们可能会意识到它们需要 **malloc** 一些内存——所以我们应该 **在完成后释放** 该内存。 如果我们还没有意识到这个事实，我们可能需要稍后再回来添加释放。 此外，如果我们在步骤 4 中仔细测试（使用极端情况），我们可能会意识到我们需要添加一些**错误检查**。 最终，这导致了一个很好的 main 通用算法：

```
Check that the argc == 2 (fail if not)
Read the input from the file named by argv[1] (call this the_roster)
Check that r != NULL (fail if not)
Create the list of all of the class names (call this result unique_class_list)
Write all the class roster files from unique_class_list and the_roster
Free memory held by unique_class_list
Free memory held by the_roster
return EXIT_SUCCESS
```

将每个复杂的步骤抽象成它自己的函数

```c
int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: roster inputname\n");
		return EXIT_FAILURE;
	}
	roster_t * the_roster = readInput (argv[1]);
	if (the_roster == NULL) {
		fprintf(stderr,"Could not read the roster information\n");
		return EXIT_FAILURE;
	}
	classes_t * unique_class_list = getClassList(the_roster);
	writeAllFiles(unique_class_list, the_roster);
	freeClasses(unique_class_list);
	freeRoster(the_roster);
	return EXIT_SUCCESS;
}
```

编写完 main 之后，我们现在有了五个新的编程任务，每个任务都是一个函数： **readInput** 、 **getClassList** 、 **writeAllFiles** 、 **freeClasses** 和 **freeRoster** 。

## 编写和测试

当您编写这些函数中的每一个时，您会想要测试它们。 单独测试代码的每一部分给我们带来了很多好处。 您现在可以在此处调试您遇到的任何问题，并确信每个问题在您继续之前都能正常工作（这涉及制作依赖于这些较小函数的函数）。

为它们编写测试工具， 主要函数与程序的其余部分分开

需要一种方法来查看它是否能够轻松地得到正确的输出来测试它。

## 完成程序

根据它们调用的低级函数来理解高级函数——知道 _它们_ 在做什么，而不必担心 _它们当时是如何_ 做的。 这就是良好抽象的好处。

代码很容易更改。 例如，假设更改输入文件的格式, 对代码更改的影响将仅限于 读取输入的函数及其调用的函数

## 更大的程序

随着我们的编程问题的规模不断扩大，将任务分解为可管理的部分的需求也越来越大。 编写小段代码，然后对其进行测试是取得实质性进展的唯一途径。

将较大的问题分解为较小的问题的一个重要方法是从一组最小的特性开始——实现、测试和调试这些特性——然后一次添加一个新特性。 添加每个新功能后，重新测试整个系统，并确保一切正常。 这种开发模型需要更多的纪律（抵制一次编写所有内容的诱惑 - 并希望它们都能正常工作），但在提高整体生产力和软件质量方面会有所回报。 纪律（尤其是在压力下）是优秀程序员的关键特征之一——优秀的程序员会以有纪律的方式工作（无论是实现、调试和测试），尤其是在时间压力下。 记住“匆忙会造成浪费”。

作为我们如何应用这个原则的一个例子，考虑编写一个程序让某人下棋。 我们可能做的第一件事就是编写程序以显示棋盘，但甚至不显示任何棋子。 这听起来可能不多，但它是我们可以制作的最小的一块，因此我们可以而且应该在继续之前停止并测试。 一旦我们让这部分工作，我们可能会在板上添加显示部分，然后再次测试。 下一步可能是允许用户移动棋子，但不必担心移动的合法性——只需让用户拿起任何棋子并将其放在其他任何地方。

此时，添加代码以保存和加载棋盘位置可能非常有用。 无论我们是否打算在最终游戏中使用此功能，它都将证明对测试非常有用——让我们以有效的方式设置和使用测试用例。 与所有其他功能一样，我们应该彻底测试它——我们不希望我们以后的测试因基础设施差而混淆和复杂。

在测试了这个功能之后，我们下一步将是一个一个地添加游戏规则。 我们可以为每一块移动添加基本规则，在每块移动之后，再次测试代码。 在完成所有基本动作之后，我们可以添加castling 和其他复杂的规则（并在添加它们时对其进行测试）。 然后我们可以添加代码来检查获胜（和测试）和绘图（和测试）。 如果我们希望我们的程序具有其他功能（ _例如_ ，通过网络播放），我们可以一次添加它们（对于大功能，将它们分解成更小的部分）并在我们进行时进行测试。
