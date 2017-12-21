# DataStruct
[![Travis](https://img.shields.io/badge/Language-C-lightgrey.svg)]()
[![Travis](https://img.shields.io/travis/rust-lang/rust.svg)]()  
This is a static lib about data structure by C.Supports generics.  
> 这是一个关于数据结构的C语言静态链接库，支持泛型。  
  
### `Method of operation:`  
Use ` visual studio 2017 ` compiled generated `.lib` file.  
> 用`visual studio 2017`编译后生成.lib文件。  

Method 1: use absolute/relative path to include header files, using #pragma precompiled instruction link library.  
> 方法一： 直接使用绝对/相对路径包含头文件，使用 #pragma 预编译指令链接库。    

`#include "../dtastc.h"`  
`#pragma comment(lib,"../debug/DataStruct.lib")`  
  
Method 2: modify the included directory, library directory, and dependency items of the project properties.(Steps to omit)  
> 方法二：修改项目属性的包含目录，库目录，附加依赖项。(步骤省略)  
   
### `Current data structure:`  
* [Stack](https://github.com/Joezeo/DataStruct#stack)  
  
  
#### `Stack`  
functions:  
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
  
  


 

