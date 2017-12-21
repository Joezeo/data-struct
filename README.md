# DataStruct
[![Travis](https://img.shields.io/badge/Language-C-lightgrey.svg)]()
[![Travis](https://img.shields.io/travis/rust-lang/rust.svg)]()  
This is a static lib about datastruct.Supports generics.  
  
### `Current data structure:`  
* [Stack](https://github.com/Joezeo/DataStruct/new/master?readme=1#stack)  
  
  
#### `Stack`  
functions:  
1. `PSTACK InitStack();`  
Initializes a stack, returns the stack structure pointer.  
初始化一个栈，返回栈结构体指针。     

2. `Status DestroyStack(PSTACK sqs);`  
Destroy the stack and release the resources.  
销毁栈，释放资源。  

3. `Status ClearStack(PSTACK sqs);`  
Empty the stack element and set it to an empty stack.  
将栈元素清空，置为空栈。  

4. `Status StackEmpty(const PSTACK sqs);`  
If the stack is an empty stack, return TRUE or FALSE.  
若栈为空栈，返回TRUE，否则返回FALSE。  

5. `int StackLength(const PSTACK sqs);`  
Returns the number of stack elements (the length of the stack).   
返回栈元素的个数，即栈的长度。  

6. `void * GetTop(const PSTACK sqs);`  
If the stack is not empty, return the value of the top element of the stack;Otherwise, NULL is returned.   
若栈不空，返回栈顶元素的值；否则返回NULL。  

7. `Status Push(PSTACK sqs, void * e);`  
Insert element e to the new stack top element, if the stack capacity is full, automatic expansion capacity.   
插入元素e为新的栈顶元素，若栈容量已满，自动扩充容量。  

8. `void * Pop(PSTACK sqs);`  
If the stack is not empty, remove the top element of the stack and return its value.   
若栈不空，则删除栈顶元素，并返回其值。  



 

