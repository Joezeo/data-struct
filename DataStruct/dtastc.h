/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.21 / 18：23
+
-             修改时间：2017.12.26 / 21：02
+
-             文件名称：dtastc.h
+
-             功能：数据结构库的头文件，包括宏、结构体的定义，函数前向声明
+
*/

#ifndef __DTA_STC_H__
#define __DTA_STC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

/*
----------------------------------- SqList -----------------------------------
*/

#define LISTINITSIZE  50
// 顺序表初始容量

#define LISTINCREMENT 10
// 顺序表增加容量

/*
+
-              结构体定义
+
*/
typedef struct {

	void ** _base;    // 线性表基地址
	UINT _length;     // 线性表长度
	UINT _listsize;   // 线性表容量

}LIST, * PLIST;

/*
+
-              函数前向声明
+
*/
PLIST
InitList();
// 初始化一个线性表


Status
FreeList(PLIST);
// 销毁一个线性表，释放内存资源


Status
EmptyList(const PLIST);
// 判断线性表是否为空表。是返回TRUE，否则返回FALSE


Status
ClearList(PLIST);
// 清空一个线性表，将其置为空表


int
ListLength(const PLIST);
// 返回线性表长度（数据元素个数）


void *
GetElem(const PLIST, const UINT);
// 获取线性表的第i个数据元素,如线性表为空表返回NULL，,i越界返回NULL


Status
Located(const PLIST, const void *);
// 判断线性表中是否存在值为第二个参数的数据元素


Status
ListInsert(PLIST, const UINT, const void *, const int);
// 线性表插入数据元素（在第二个参数位置插入元素，值为第三个参数的值）


Status
ListRemove(PLIST, const UINT);
// 线性表删除数据元素（删除位置为第二个参数）


static Status
AddlistSize(PLIST);
// 静态函数，增加线性表的容量

/*
------------------------------------------------------------------------------
*/





/*
---------------------------------- LinkList ----------------------------------
*/

/*
+
-              结构体定义
+
*/
typedef struct NODE {

	void * _data;
	struct NODE * _next;
	struct NODE * _pre;

}NODE, * PNODE;

typedef struct {

	PNODE _head;    // 头指针
	PNODE _tail;    // 尾指针
	UINT  _cnt;     // 元素个数

}LINKLIST, * PLINKLIST;

/*
+
-              函数前向声明
+
*/
static PNODE
NewNode(void *, const int);
// 创建一个新的节点，其数据域为传入的参数的值


Status
FreeNode(PNODE);
// 释放此节点的内存空间


PLINKLIST
Initlklist();
// 初始化一个不带头结点的空链表


Status
FreelkList(PLINKLIST);
// 销毁链表，释放内存空间


Status
ClearlkList(PLINKLIST);
// 清空链表为空链表


Status
EmptylkList(const PLINKLIST);
// 判断一个链表是否为空，是则返回TRUE；否则返回FALSE


Status
AddNode(PLINKLIST, void *, const int);
// 为链表新建一个节点，其数据域为传入的第二个参数的值（默认插入顺序从尾部插入）


Status
RemoveNode(PLINKLIST);
// 链表删除一个结点。(默认从尾部删除)


int
lkListLength(const PLINKLIST);
// 返回链表的长度(元素个数)


PNODE
GetNode(const PLINKLIST, void *);
// 在链表中查找数据域为第二个参数值的节点，并返回其地址,如没找到，返回NULL


Status
InsertNodeAfter(PNODE, void *, const int);
// 在第一参数结点后插入数据域为第二个参数的新节点


Status
InsertNodeBefore(PNODE, void *, const int);
// 在第一参数结点前插入数据域为第二个参数的新节点

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- Stack -----------------------------------
*/

#define STACKINITSIZE  50
// 栈初始化时的起始容量

#define STACKINCREMENT 10
// 栈增加容量

/*
+
-              结构体定义
+
*/
typedef struct {

	void ** _base;          // 栈底指针
	void ** _top;           // 栈顶指针
	UINT _stacksize;        // 栈容量
	UINT _cnt;              // 当前栈元素个数

}STACK, * PSTACK;

/*
+
-              函数前向声明
+
*/
PSTACK
InitStack();
// 构造一个空栈


Status
DestroyStack(PSTACK);
// 销毁栈，释放资源


Status
ClearStack(PSTACK);
// 将栈元素清空，置为空栈

Status
StackEmpty(const PSTACK);
// 若栈为空栈，返回TRUE，否则返回FALSE


int
StackLength(const PSTACK);
// 返回栈元素的个数，即栈的长度


void *
GetTop(const PSTACK);
// 若栈不空，返回栈顶元素的值；否则返回NULL


Status
Push(PSTACK, void *, const int);
// 插入元素e为新的栈顶元素


Status
Pop(PSTACK, void *, const int);
// 若栈不空，则删除栈顶元素，并返回其值


static Status
AddStackSize(PSTACK);
// 增加栈的容量

/*
-----------------------------------------------------------------------------
*/

#ifdef __cplusplus
}
#endif

#endif // __DTA_STC_H__ //
