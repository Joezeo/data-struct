/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.21 / 18：23
+
-             修改时间：2017.12.21 / 22：38
+
-             文件名称：dtastc.c
+
-             功能：数据结构库的函数定义
+
*/
#include "dtastc.h"

/*
---------------------------------- LinkList ----------------------------------
*/

/*
+
-               函数定义
+
*/
static PNODE
NewNode(void * e) {

	PNODE newnode = (PNODE)malloc(sizeof(NODE));
	if (!newnode) {

		exit(OVERFLOW);

	}

	newnode->_data = e;
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
AddNode(PLINKLIST lklist, void * e) {

	assert(lklist != NULL);
	assert(e != NULL);

	PNODE newnode = NewNode(e);

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
	assert(e != NULL);

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
InsertNodeAfter(PNODE node, void * e) {

	assert(node != NULL);
	assert(e != NULL);

	PNODE tmp = node->_next;
	PNODE newnode = NewNode(e);

	newnode->_next = tmp;
	newnode->_pre = node;

	node->_next = newnode;
	tmp->_pre = newnode;

	return OK;


}
// 在第一参数结点后插入数据域为第二个参数的新节点


Status
InsertNodeBefore(PNODE node, void * e) {

	assert(node != NULL);
	assert(e != NULL);

	PNODE tmp = node->_pre;
	PNODE newnode = NewNode(e);

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
---------------------------------- Stack ----------------------------------
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
Push(PSTACK sqs, void * e) {

	assert(sqs != NULL);

	assert(sqs != NULL);

	if (sqs->_cnt == sqs->_stacksize) {

		AddStackSize(sqs);

	}

	*(sqs->_top) = e;
	sqs->_cnt++;

	return OK;

}
// 插入元素e为新的栈顶元素


void *
Pop(PSTACK sqs) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return NULL;

	}

	sqs->_top--;
	sqs->_cnt--;

	return *(sqs->_top + 1);

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
---------------------------------------------------------------------------
*/
