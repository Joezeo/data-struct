/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.21 / 18：23
+
-             修改时间：2018.02.03 / 19：32
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
#include <stdarg.h>

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

	void ** m_base;    // 线性表基地址
	UINT m_length;     // 线性表长度
	UINT m_listsize;   // 线性表容量

}LIST, * PLIST;

/*
+
-              函数前向声明
+
*/
PLIST
InitList(const int);
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
// 线性表插入数据元素（在第二个参数位置插入元素，值为第三个参数的值，第四个参数为数据元素的大小）


Status
ListRemove(PLIST, const UINT);
// 线性表删除数据元素（删除位置为第二个参数）

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

	void * m_data;
	struct NODE * m_next;
	struct NODE * m_pre;

}NODE, * PNODE;

typedef struct {

	PNODE m_head;    // 头指针
	PNODE m_tail;    // 尾指针
	UINT  m_cnt;     // 元素个数

}LINKLIST, * PLINKLIST;

/*
+
-              函数前向声明
+
*/

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
// 为链表新建一个节点，其数据域为传入的第二个参数的值（默认插入顺序从尾部插入），第三个参数为数据元素的大小


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

	void ** m_base;          // 栈底指针
	void ** m_top;           // 栈顶指针
	UINT m_stacksize;        // 栈容量
	UINT m_cnt;              // 当前栈元素个数

}STACK, * PSTACK;

/*
+
-              函数前向声明
+
*/
PSTACK
InitStack(const int);
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


Status
GetTop(const PSTACK, void *, const int);
// 若栈不空，返回栈顶元素的值；否则返回NULL


Status
Push(PSTACK, const void *, const int);
// 插入元素e为新的栈顶元素


Status
Pop(PSTACK, void *, const int);
// 若栈不空，则删除栈顶元素，并返回其值


/*
-----------------------------------------------------------------------------
*/





/*
----------------------------------- Quene -----------------------------------
*/

// 基于双向链表的队列，可实现动态分配内存

/*
+
-              结构体定义
+
*/
typedef struct QNODE {
	
	void * m_data;

	struct QNODE * m_nex;
	struct QNODE * m_pre;

}QNODE, * PQNODE;

typedef struct  {
	
	PQNODE m_front; // 队头指针
	PQNODE m_rear;  // 队尾指针

	UINT   m_cnt;   // 队列元素个数

}QUENE, * PQUENE;

/*
+
-              函数前向声明
+
*/

PQUENE
InitQuene();
// 构造一个空队列

Status
DestroyQuene(PQUENE);
// 销毁队列，释放内存资源

Status
ClearQuene(PQUENE);
// 将队列清空为空队列

Status
EmptyQuene(const PQUENE);
// 若队列为空队列，返回TRUE，否则返回FALSE

UINT
QueneLength(const PQUENE);
// 返回队列元素个数，及队列长度

Status
GetHead(const PQUENE, void *, const int);
// 用第二个参数获取队头元素的值，第三个参数传入数据元素的大小，不删除队头元素的值

Status
EnQuene(PQUENE, const void *, const int);
// 插入元素e为队列的新队尾元素

Status
DeQuene(PQUENE, void *, const int);
// 若队列不空，删除队列的头元素，并用第二个参数返回其值


/*
-----------------------------------------------------------------------------
*/





/*
----------------------------------- String -----------------------------------
*/

/*
+
-              结构体定义
+
*/
typedef struct {

	char * m_ch;
	int    m_length;

}STRING, * PSTRING;


/*
+
-              函数前向声明
+
*/
PSTRING
StrAssign(char *);
// 生成一个其值等于串常量chars的串

int
StrLength(const PSTRING);
// 返回串的长度

int
StrCompare(const PSTRING, const PSTRING);
// 串比较，若相等返回0，若arg1 > arg2，返回值>0,否则返回值<0

Status
ClearString(PSTRING);
// 将串清空为空串

PSTRING
StrConcat(PSTRING, PSTRING);
// 返回由两串联结而成的新串

PSTRING
SubString(PSTRING, const int, const int);
// 返回串从第二个参数（从0开始计）起，长度为第三个参数的子串

int
StrIndex(PSTRING, PSTRING, int);
// 第一个参数为主串，第二个参数为模式串，第三个参数为开始匹配的位置


/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- Array -----------------------------------
*/

/*
+
-              结构体定义
+
*/
typedef struct {

	void * m_base;      // 数组元素基址
	int    m_dim;       // 数组维数
	int  * m_bounds;    // 数组维界基址，用于储存各个维界的长度
	int  * m_constants; // 数组映像函数常量基址

}ARRAY, * PARRAY;

/*
+
-              函数前向声明
+
*/
PARRAY
InitArray(int, int, ...);
// 若维数和各维长度合法，则构造相应的数组，将其返回,否则返回NULL

Status
DestoryArray(PARRAY *);
// 销毁数组，释放内存资源

Status
Value(PARRAY, const int, void *, ...);
// 若各个下标不越界，e赋值为指定下标元素的值，并返回OK

Status
Assign(PARRAY, const int, void *, ...);
// 若各个下标不越界，则将e的值赋给指定下标元素，并返回OK

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- SMatrix -----------------------------------
*/

// 稀疏矩阵

/*
+
-              结构体定义
+
*/
typedef struct {

	int    i, j;   // 非零元的行下标和列下标
	void * m_data; // 非零元数据元素

}TRIPLE, * PTRIPLE;

typedef struct {

	TRIPLE * m_pTriples;
	int mu, nu, tu;     // 矩阵的行数，列数和非零元个数

}SMATRIX, * PSMATRIX;


/*
+
-              函数前向声明
+
*/

PTRIPLE
GetTriple(const void **, const int, const int, const int);
// 从一个二维数组中取得非零元素三元组



/*
-------------------------------------------------------------------------------
*/
#ifdef __cplusplus
}
#endif

#endif // __DTA_STC_H__ //
