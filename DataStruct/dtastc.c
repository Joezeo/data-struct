/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.21 / 18：23
+
-             修改时间：2017.12.26 / 21：03
+
-             文件名称：dtastc.c
+
-             功能：数据结构库的函数定义
+
*/

#include "dtastc.h"

/*
----------------------------------- SqList -----------------------------------
*/

/*
+
-               函数定义
+
*/
PLIST
InitList() {

	PLIST _list = (PLIST)malloc(sizeof(LIST));
	if (!_list) {

		exit(OVERFLOW);

	}

	_list->_base = (void **)malloc(LISTINITSIZE * sizeof(void *));
	if (!(_list->_base)) {

		exit(OVERFLOW);

	}

	_list->_length = 0;
	_list->_listsize = LISTINITSIZE;

	return _list;

}
// 初始化一个线性表


Status
FreeList(PLIST plist) {

	assert(plist != NULL);

	free(plist->_base);
	plist->_base = NULL;

	free(plist);
	plist = NULL;

	return OK;

}
// 销毁一个线性表，释放内存资源


Status
EmptyList(const PLIST plist) {

	assert(plist != NULL);

	if (plist->_length == 0) {

		return TRUE;

	}

	return FALSE;

}
// 判断线性表是否为空表。是返回TRUE，否则返回FALSE


Status
ClearList(PLIST plist) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return OK;

	}

	for (UINT i = 0; i < plist->_length; i++) {

		*(plist->_base + i) = 0;

	}

	plist->_length = 0;

	return OK;

}
// 清空一个线性表，将其置为空表


int
ListLength(const PLIST plist) {

	assert(plist != NULL);

	return plist->_length;

}
// 返回线性表长度（数据元素个数）


void *
GetElem(const PLIST plist, const UINT i) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return NULL;

	}

	if (i > plist->_length || i <= 0) {

		return NULL;

	}

	return *(plist->_base + i - 1);

}
// 获取线性表的第i个数据元素,如线性表为空表返回NULL,i越界返回NULL


Status
Located(const PLIST plist, const void * e) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return FALSE;

	}

	for (UINT i = 0; i < plist->_length; i++) {

		if (*(plist->_base + i) == e) {

			return TRUE;

		}

	}

	return FALSE;

}
// 判断线性表中是否存在值为第二个参数的数据元素


Status
ListInsert(PLIST plist, const UINT i, const void * e, const int _size) {

	assert(plist != NULL);

	if (i <= 0 || i > plist->_length + 1) {

		return ERROR;

	}

	if (plist->_length == plist->_listsize) {

		AddlistSize(plist);

	}

	if(EmptyList(plist)){

		memcpy(plist->_base, e, _size);

		goto fend;
	
	}
	else if (i == plist->_length + 1) {

		memcpy(plist->_base + i - 1, e, _size);

		goto fend;

	}
	else {

		for (UINT j = plist->_length; j >= i; j--) {

			memcpy(plist->_base + j, plist->_base + j - 1, _size);

		}

		memcpy(plist->_base + i - 1, e, _size);

		goto fend;

	}

fend:
	plist->_length++;
	return OK;

}
// 线性表插入数据元素（在第二个参数位置插入元素，值为第三个参数的值）


Status
ListRemove(PLIST plist, const UINT i) {

	assert(plist != NULL);

	if (i <= 0 || i > plist->_length) {

		return ERROR;

	}

	if (EmptyList(plist)) {

		return ERROR;

	}

	if (i == plist->_length) {

		*(plist->_base + i - 1) = 0;

		goto fend;

	}
	else {

		for (UINT j = i - 1; j < plist->_length - 1; j++) {

			*(plist->_base + j) = *(plist->_base + j + 1);

			goto fend;

		}

	}

fend:
	plist->_length--;
	return OK;

}
// 线性表删除数据元素（删除位置为第二个参数）


static Status
AddlistSize(PLIST plist) {

	assert(plist != NULL);

	void ** add = (void **)realloc(plist->_base,
		(plist->_listsize + LISTINCREMENT) * sizeof(void *));

	if (!add) {

		exit(OVERFLOW);

	}

	plist->_base = add;
	plist->_listsize += LISTINCREMENT;

	return OK;

}
// 静态函数，增加线性表的容量

/*
------------------------------------------------------------------------------
*/





/*
---------------------------------- LinkList ----------------------------------
*/

/*
+
-               函数定义
+
*/
static PNODE
NewNode(void * e, const int _size) {

	PNODE newnode = (PNODE)malloc(sizeof(NODE));
	if (!newnode) {

		exit(OVERFLOW);

	}

	memcpy(newnode->_data, e, _size);
	newnode->_next = NULL;
	newnode->_pre = NULL;

	return newnode;

}
// 创建一个新的节点，其数据域为传入的参数的值


Status
FreeNode(PNODE node) {

	assert(node != NULL);

	if (node->_pre != NULL) {

		PNODE tmp = node->_pre;
		tmp->_next = node->_next;

	}
	if (node->_next != NULL) {

		PNODE tmp = node->_next;
		tmp->_pre = node->_pre;

	}

	free(node);
	node = NULL;

	return OK;

}
// 释放此节点的内存空间


PLINKLIST
Initlklist() {

	PLINKLIST lklist = (PLINKLIST)malloc(sizeof(LINKLIST));
	if (!lklist) {

		exit(OVERFLOW);

	}

	lklist->_cnt = 0;
	lklist->_head = NULL;
	lklist->_tail = NULL;

	return lklist;

}
// 初始化一个不带头结点的空链表


Status
FreelkList(PLINKLIST lklist) {

	assert(lklist != NULL);

	if (EmptylkList(lklist)) {

		free(lklist);
		lklist = NULL;
		
		return OK;

	}

	PNODE pre = NULL;
	PNODE cur = lklist->_head;

	while (cur != NULL) {

		pre = cur->_next;
		free(cur);
		cur = pre;

	}

	free(lklist);
	lklist = NULL;

	return OK;

}
// 销毁链表，释放内存空间


Status
ClearlkList(PLINKLIST lklist) {

	assert(lklist != NULL);

	if (EmptylkList(lklist)) {

		return ERROR;

	}

	PNODE pre = NULL;
	PNODE cur = lklist->_head;

	while (cur != NULL) {

		pre = cur->_next;
		free(cur);
		cur = pre;

	}

	lklist->_head = NULL;
	lklist->_tail = NULL;
	lklist->_cnt = 0;

	return OK;

}
// 清空链表为空链表


Status
EmptylkList(const PLINKLIST lklist) {

	assert(lklist != NULL);

	if (lklist->_cnt == 0) {

		return TRUE;

	}

	return FALSE;

}
// 判断一个链表是否为空，是则返回TRUE；否则返回FALSE


Status
AddNode(PLINKLIST lklist, void * e, const int _size) {

	assert(lklist != NULL);

	PNODE newnode = NewNode(e, _size);

	if (EmptylkList(lklist)) {

		lklist->_head = newnode;
		lklist->_tail = newnode;

	}
	else {

		PNODE tmp = NULL;
		tmp = lklist->_tail;
		lklist->_tail->_next = newnode;
		lklist->_tail = newnode;
		lklist->_tail->_pre = tmp;

	}

	lklist->_cnt++;

	return OK;

}
// 为链表新建一个节点，其数据域为传入的第二个参数的值（默认插入顺序从尾部插入）


Status
RemoveNode(PLINKLIST lklist) {

	assert(lklist != NULL);

	PNODE tmp = lklist->_tail;

	if (EmptylkList(lklist)) {

		return ERROR;

	}

	lklist->_tail = lklist->_tail->_pre;
	lklist->_tail->_next = NULL;
	lklist->_cnt--;

	free(tmp);
	tmp = NULL;

	return OK;

}
// 链表删除一个结点。(默认从尾部删除)


int
lkListLength(const PLINKLIST lklist) {

	assert(lklist != NULL);

	return lklist->_cnt;

}
// 返回链表的长度(元素个数)


PNODE
GetNode(const PLINKLIST lklist, void * e) {

	assert(lklist != NULL);

	if (EmptylkList(lklist)) {

		return NULL;

	}

	PNODE node = lklist->_head;

	for (; node != NULL; node = node->_next) {

		if (node->_data == e) {

			break;

		}

	}

	if (node == NULL) {

		return NULL;

	}

	return node;

}
// 在链表中查找数据域为第二个参数值的节点，并返回其地址,如没找到，返回NULL


Status
InsertNodeAfter(PNODE node, void * e, const int _size) {

	assert(node != NULL);

	PNODE tmp = node->_next;
	PNODE newnode = NewNode(e, _size);

	newnode->_next = tmp;
	newnode->_pre = node;

	node->_next = newnode;
	tmp->_pre = newnode;

	return OK;


}
// 在第一参数结点后插入数据域为第二个参数的新节点


Status
InsertNodeBefore(PNODE node, void * e, const int _size) {

	assert(node != NULL);

	PNODE tmp = node->_pre;
	PNODE newnode = NewNode(e, _size);

	newnode->_pre = tmp;
	newnode->_next = node;

	tmp->_next = newnode;
	node->_pre = newnode;

	return OK;

}
// 在第一参数结点前插入数据域为第二个参数的新节点

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- Stack -----------------------------------
*/

/*
+
-               函数定义
+
*/
PSTACK
InitStack() {

	PSTACK sqs = (PSTACK)malloc(sizeof(STACK));
	if (!sqs) {

		exit(OVERFLOW);

	}

	sqs->_base = (void **)malloc(STACKINITSIZE * sizeof(void*));
	if (!(sqs->_base)) {

		exit(OVERFLOW);

	}	
	
	sqs->_top = sqs->_base;
	sqs->_stacksize = STACKINITSIZE;
	sqs->_cnt = 0;

	return sqs;

}
// 构造一个空栈


Status
DestroyStack(PSTACK sqs) {

	assert(sqs != NULL);

	free(sqs->_base);
	sqs->_base = NULL;
	sqs->_top = NULL;

	free(sqs);
	sqs = NULL;

	return OK;

}
// 销毁栈，释放资源


Status
ClearStack(PSTACK sqs) {

	assert(sqs != NULL);

	sqs->_top = sqs->_base;
	sqs->_cnt = 0;

	return OK;

}
// 将栈元素清空，置为空栈


Status
StackEmpty(const PSTACK sqs) {

	assert(sqs != NULL);

	if (sqs->_cnt == 0)
		return TRUE;

	return FALSE;

}
// 若栈为空栈，返回TRUE，否则返回FALSE


int
StackLength(const PSTACK sqs) {

	assert(sqs != NULL);

	return sqs->_cnt;

}
// 返回栈元素的个数，即栈的长度


void *
GetTop(const PSTACK sqs) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return NULL;

	}

	return *(sqs->_top - 1);

}
// 若栈不空，返回栈顶元素的值；否则返回NULL


Status
Push(PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);

	if (sqs->_cnt == sqs->_stacksize) {

		AddStackSize(sqs);

	}

	memcpy(sqs->_top, e, _size);

	sqs->_top++;
	sqs->_cnt++;

	return OK;

}
// 插入元素e为新的栈顶元素


Status
Pop(PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return ERROR;

	}

	sqs->_top--;
	sqs->_cnt--;

	memcpy(e, sqs->_top, _size);

	return OK;

}
// 若栈不空，则删除栈顶元素，并返回其值


static Status
AddStackSize(PSTACK sqs) {

	assert(sqs != NULL);

	void **add = (void **)realloc(sqs->_base,
		(sqs->_stacksize + STACKINCREMENT) * sizeof(void*));

	if (!add) {

		exit(OVERFLOW);

	}

	sqs->_base = add;
	sqs->_stacksize += STACKINCREMENT;

	return OK;

}
// 增加栈的容量

/*
-----------------------------------------------------------------------------
*/
