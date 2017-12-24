# DataStruct
[![Travis](https://img.shields.io/badge/Language-C-lightgrey.svg)]()
[![Travis](https://img.shields.io/badge/Project%20type-Static%20lib-orange.svg)]()
[![Travis](https://img.shields.io/travis/rust-lang/rust.svg)]()
[![Travis](https://img.shields.io/badge/Current%20state-building-yellow.svg)]()  
This is a static lib about data structure by C.Supports generics.  
> 这是一个关于数据结构的C语言静态链接库，支持泛型。  
---
### `Method of operation:`  
Use ` visual studio 2017 ` compiled generated `.lib` file.  
> 用`visual studio 2017`编译后生成.lib文件。  

Method 1: use absolute/relative path to include header files, using #pragma precompiled instruction link library.  
> 方法一： 直接使用绝对/相对路径包含头文件，使用 #pragma 预编译指令链接库。    

`#include "../dtastc.h"`  
`#pragma comment(lib,"../debug/DataStruct.lib")`  
  
Method 2: modify the included directory, library directory, and dependency items of the project properties.(Steps to omit)  
> 方法二：修改项目属性的包含目录，库目录，附加依赖项。(步骤省略)  
---
### `Current data structure:`  
* [List(SqList)](https://github.com/Joezeo/DataStruct#list)
* [LinkList](https://github.com/Joezeo/DataStruct#linklist)  
* [Stack](https://github.com/Joezeo/DataStruct#stack)  
---    
#### `List`   
**introduce:**  
Realize the basic function of the SqList, which counts the linear table from 1,and automatic expansion capacity.   
> 实现线性表基本功能，此线性表从1开始计数，自动扩充容量。  
  
**functions:**  
1. `PLIST InitList();`  
Initialize a SqList.  
> 初始化一个线性表。 
  
2. `Status FreeList(PLIST plist);`  
Destroy a SqList and release memory resources.  
> 销毁一个线性表，释放内存资源。   

3. `Status EmptyList(const PLIST plist);`  
Determine whether a SqList is an empty table.Returns TRUE, or FALSE.  
> 判断线性表是否为空表。是返回TRUE，否则返回FALSE。  
  
4. `Status ClearList(PLIST plist);`  
Empty a SqList and set it to an empty list.  
> 清空一个线性表，将其置为空表。  
  
5. `int ListLength(const PLIST plist);`  
Returns the SqList length (the number of data elements).  
> 返回线性表长度（数据元素个数）。  
  
6. `void * GetElem(const PLIST plist, const int  i);`  
Gets the ith data element of the Sqlist, such as the SqList returns NULL for the empty table, and i transboundary returns NULL.   
> 获取线性表的第i个数据元素,如线性表为空表返回NULL,i越界返回NULL。  
  
7. `Status Located(const PLIST plist, const void * e);`  
Determines whether there is a data element with a value of the second parameter in the SqList.  
>  判断线性表中是否存在值为第二个参数的数据元素。  
  
8. `Status ListInsert(PLIST plist, const int i, const void * e);`  
The SqList inserts the data element (insert the element at the second parameter position, and the value is the value of the third parameter).  
> 线性表插入数据元素（在第二个参数位置插入元素，值为第三个参数的值）。  
  
9. `Status ListRemove(PLIST plist, const int i);`  
The SqList removes the data element (the delete position is the second parameter).   
> 线性表删除数据元素（删除位置为第二个参数）。  
  
[return/返回](https://github.com/Joezeo/DataStruct#current-data-structure)   
---

#### `LinkList`  
**introduce:**  
The node includes the front/rear node pointer, and the list does not include the empty head node.  
> 节点包括前/后节点指针，链表不包括空头结点。  
  
**functions:**  
1. `Status FreeNode(PNODE node);`  
Release the memory space for this node.  
> 释放此节点的内存空间。  
  
2. `PLINKLIST Initlklist();`  
Initialize an empty linked list with no head nodes.  
> 初始化一个不带头结点的空链表。  
  
3. `Status FreelkList(PLINKLIST lklist);`  
Destroy list, free memory space.  
> 销毁链表，释放内存空间。  
  
4. `Status ClearlkList(PLINKLIST lklist);`  
Empty lists for empty linked lists.  
> 清空链表为空链表。  
  
5. `Status EmptylkList(const PLINKLIST lklist);`  
To determine if a list is empty, it returns TRUE;Otherwise return FALSE.  
> 判断一个链表是否为空，是则返回TRUE；否则返回FALSE。  
  
6. `Status AddNode(PLINKLIST lklist, void * e);`  
To create a new node for the list, its data domain is the value of the second parameter passed in (the default insertion sequence is inserted from the tail).   
> 为链表新建一个节点，其数据域为传入的第二个参数的值（默认插入顺序从尾部插入）。   
   
7. `Status RemoveNode(PLINKLIST lklist);`   
The linked list removes one node.(by default delete from the tail).  
> 链表删除一个结点。(默认从尾部删除)。  
  
8. `int lkListLength(const PLINKLIST lklist);`  
Returns the length of the list (the number of elements).  
> 返回链表的长度(元素个数)。  
  
9. `PNODE GetNode(const PLINKLIST lklist, void * e);`  
Locate the node in the list of data fields as the second parameter value, and return the address, if not found, to return NULL.  
> 在链表中查找数据域为第二个参数值的节点，并返回其地址,如没找到，返回NULL。  
  
10. `Status InsertNodeAfter(PNODE node, void * e);`  
Insert the data domain into the new node of the second parameter after the first parameter node.  
> 在第一参数结点后插入数据域为第二个参数的新节点。  
  
11. `Status InsertNodeBefore(PNODE node, void * e);`  
Insert the data domain into the new node of the second parameter before the first parameter node.   
> 在第一参数结点前插入数据域为第二个参数的新节点。  
  
[return/返回](https://github.com/Joezeo/DataStruct#current-data-structure)  
---
  
#### `Stack`  
**introduce:**  
Use sequential tables as the basis of the stack.  
> 使用顺序表作为栈的基础。  
  
**functions:**  
1. `PSTACK InitStack();`  
Initializes a stack, returns the stack structure pointer.  
> 初始化一个栈，返回栈结构体指针。     
  
  
2. `Status DestroyStack(PSTACK sqs);`  
Destroy the stack and release the resources.  
> 销毁栈，释放资源。  
  
  
3. `Status ClearStack(PSTACK sqs);`  
Empty the stack element and set it to an empty stack.  
> 将栈元素清空，置为空栈。  
  
  
4. `Status StackEmpty(const PSTACK sqs);`  
If the stack is an empty stack, return TRUE or FALSE.  
> 若栈为空栈，返回TRUE，否则返回FALSE。  
  
  
5. `int StackLength(const PSTACK sqs);`  
Returns the number of stack elements (the length of the stack).   
> 返回栈元素的个数，即栈的长度。  
  
  
6. `void * GetTop(const PSTACK sqs);`  
If the stack is not empty, return the value of the top element of the stack;Otherwise, NULL is returned.   
> 若栈不空，返回栈顶元素的值；否则返回NULL。  
  
  
7. `Status Push(PSTACK sqs, void * e);`  
Insert element e to the new stack top element, if the stack capacity is full, automatic expansion capacity.   
> 插入元素e为新的栈顶元素，若栈容量已满，自动扩充容量。  
  
  
8. `void * Pop(PSTACK sqs);`  
If the stack is not empty, remove the top element of the stack and return its value.   
> 若栈不空，则删除栈顶元素，并返回其值。  
  
[return/返回](https://github.com/Joezeo/DataStruct#current-data-structure)  
---
  


 

