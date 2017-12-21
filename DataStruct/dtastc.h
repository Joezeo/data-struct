/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.21 / 18：23
+
-             修改时间：2017.12.21 / 18：23
+
-             文件名称：dtastc.h
+
-             功能：数据结构库的头文件，包括宏、结构体、的定义，函数前向声明
+
*/

#ifndef __DTASTC_H__
#define __DTASTC_H__

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STACKINITSIZE  50
// 栈初始化时的起始容量

#define STACKINCREMENT 10
// 栈增加容量

/*
+
-              状态码定义
+
*/
#define TRUE           1      
#define FALSE          0
#define OK             0
#define ERROR         -1
#define OVERFLOW      -2

typedef unsigned int UINT;
typedef int Status;

typedef struct {

	void ** base;          // 栈底指针
	void ** top;           // 栈顶指针
	UINT stacksize;        // 栈容量
	UINT cnt;              // 当前栈元素个数

}STACK, * PSTACK;

/*
+
-              函数前向声明
+
*/

PSTACK
InitStack();

Status
DestroyStack(PSTACK);

Status
ClearStack(PSTACK);

Status
StackEmpty(const PSTACK);

int
StackLength(const PSTACK);

void *
GetTop(const PSTACK);

Status
Push(PSTACK, void *);

void *
Pop(PSTACK);

static Status
AddStackSize(PSTACK);

#ifdef __cplusplus
}
#endif

#endif
