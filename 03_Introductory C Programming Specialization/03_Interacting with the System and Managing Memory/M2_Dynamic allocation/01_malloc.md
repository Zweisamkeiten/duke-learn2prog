---
date created: 2022-10-17 19:15
date updated: 2022-10-17 19:47
---

## 动态分配的目的

```c
//broken code: do not do

int * initArray(int howLarge) {
	int myArray[howLarge];
	for (int i = 0; i < howLarge; i++) {
		myArray[i] = i;
	}
	return myArray;
}
```

这段代码不起作用的原因是数组是在栈上创建的。 栈上的变量只存在于函数结束之前，此时栈帧消失了.

执行更复杂的创建任务的函数, 并让结果在创建它们的函数之外持续存在 -- _动态内存分配_
#newget
动态内存分配允许程序员请求在 _堆_（下图中以紫色突出显示）而不是栈上分配特定数量的内存。 因为内存不在栈帧中，所以函数返回时不会释放。 相反，程序员在使用完内存后必须显式释放内存。

![](attachments/Pasted%20image%2020221017190630.png)

动态内存分配涉及分配内存（使用 **malloc** 函数）和在不再需要时释放该内存（使用 **free** 函数）。 程序员可能还希望以不同的大小重新分配一块内存（例如，您可能认为一个包含 8 个元素的数组就足够了，然后读取一些输入并发现您需要 16 个）。 可能 **realloc** 函数允许程序员完全做到这一点——要求标准库分配一个新的（更大或更小的）内存块，将原始的内容复制到新的，并释放旧的（尽管库 _会_ 优化此过程是否可以将块展开到位）。 对于所有这三个函数，包括 _**<stdlib.h>**_ 。 我们还将看到一个很棒的函数 **getline** ，用于使用动态分配读取任意长度的字符串。
#newget

## malloc

动态内存分配的最基本函数称为 **执行** 内存 **分配** ( **malloc** )。 调用此函数是动态分配内存的方式.

malloc 函数接受一个参数，告诉它需要多少内存，并以 _void *_ 的形式返回一个指向该分配内存的指针

可以将 void * 分配 给任何其他指针类型，因此只需将 malloc 的返回结果分配给您要初始化的任何指针

![](attachments/Pasted%20image%2020221017191200.png)

因此可以在函数内malloc内存并分配给一个指针,并返回指针. 就可以在其他位置使用该部分内存.

```c
// fix initArray
int * intArray(int howLarge) {
	int *array = malloc(howLarge * sizeof(*array));
	if (array != NULL) {
		for (int i = 0; i < howLarge; i++) {
			array[i] = i;
		}
	}
	return array;
}
```

如果 malloc 失败（ _即_ 返回 NULL），则该函数将返回 NULL——这会将处理错误的任务推给调用此函数的人。 每当您编写一个您不知道应该如何处理错误的函数时，让调用者处理错误是一个很好的策略。

## More complex structures

使用 malloc 分配一个结构体. 再给结构体中的指针分配内存块, 这样就能在堆中形成复杂的数据结构.

通过 malloc 具有指针的结构在堆中形成复杂的数据结构，然后将它们设置为指向堆中的其他位置（它们本身指向由 malloc 分配的内存块）

```c
struct point_tag {
	int x;
	int y;
};
typedef struct point_tag point_t;
struct polygon_tag {
	size_t num_points;
	point_t * points;
};
typedef struct polygon_tag polygon_t;
polygon_t * makeRectangle(point_t c1, point_t c2) {
	polygon_t * answer = malloc(sizeof(*answer));
	answer->num_points = 4;
	answer->points = malloc(answer->num_points * sizeof(*answer->points));
	answer->points[0] = c1;
	answer->points[1].x = c1.x;
	answer->points[1].y = c2.y;
	answer->points[2] = c2;
	answer->points[3].x = c2.x;
	answer->points[3].y = c1.y;
	return answer;
}
```

有一个函数为多边形（一个结构）分配空间，它本身有一个指向点数组的指针。 这个特殊的函数会创建一个矩形，因此它会分配 4 个点的空间并在将其答案返回给调用者之前填充它们。

## 浅拷贝与深拷贝

假设我们有一个 **polygon_t * p1** 指向我们创建的多边形（ _例如_ ，通过调用 **makeRectangle** ），并且我们想要复制它所指向的多边形。 如果我们只写以下内容，我们只会复制指针——我们不会真正复制它指向的对象

```c
polygon_t * p2 = p1; //just copy pointer
```

![](attachments/Pasted%20image%2020221017194157.png)

### 浅拷贝

使用 malloc，我们可以创建一个副本

```c
polygon_t * p2 = malloc(sizeof(*p2));
*p2 = *p;
```

![](attachments/Pasted%20image%2020221017194255.png)

现在，我们有两个多边形，但只有 _一个_ 点数组。 我们创建了 _多边形的浅表副本_ ——我们通过精确复制多边形内部的字段来制作多边形的副本。 浅拷贝中的每个指针都指向与原始指针中的对应指针完全相同的内存位置。 在某些情况下，浅拷贝可能是我们想要的。 但是，如果我们 执行 **p1->points[0].x = 42;** 我们也将改变p2的0点坐标, 因为**p1->points**指向与**p2->points**相同的内存.

请注意，在释放具有浅拷贝的对象时，我们还必须小心——我们需要注意仅在完成两个浅拷贝时才释放点数组。 由于它们共享内存，如果我们在使用完一个点数组后释放点数组，然后尝试使用另一个副本，它将有一个悬空指针。

### 深拷贝

如果我们想要两个完全不同的多边形对象，我们想要做一个 _深拷贝_ ——我们不只是复制指针，分配新内存并制作该指针指向的深拷贝.

```c
polygon_t * p2 = malloc(sizeof(*p2));
p2->num_points = p1->num_points;
p2->points = malloc(p2->num_points * sizeof(*p2->points));
for (size_t i = 0; i < p2->num_points; i++) {
	p2->points[i] = p1->points[i];
}
```
![](attachments/Pasted%20image%2020221017194847.png)

