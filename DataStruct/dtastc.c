/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.21 / 18：23
+
-             修改时间：2018.03.21 / 12：32
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

static Status
__addlistSize(PLIST);
// 静态函数，增加线性表的容量

/*
+
-               函数定义
+
*/
PLIST
InitList(const int _size) {

	assert(_size > 0);

	PLIST _list = (PLIST)malloc(sizeof(LIST));
	if (!_list) {

		exit(OVERFLOW);

	}

	_list->m_base = (void **)malloc(LISTINITSIZE * _size);
	if (!(_list->m_base)) {

		exit(OVERFLOW);

	}

	_list->m_length = 0;
	_list->m_listsize = LISTINITSIZE;

	return _list;

}
// 初始化一个线性表


Status
FreeList(PLIST plist) {

	assert(plist != NULL);

	free(plist->m_base);
	plist->m_base = NULL;

	free(plist);
	plist = NULL;

	return OK;

}
// 销毁一个线性表，释放内存资源


Status
EmptyList(const PLIST plist) {

	assert(plist != NULL);

	if (plist->m_length == 0) {

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

	for (UINT i = 0; i < plist->m_length; i++) {

		*(plist->m_base + i) = 0;

	}

	plist->m_length = 0;

	return OK;

}
// 清空一个线性表，将其置为空表


int
ListLength(const PLIST plist) {

	assert(plist != NULL);

	return plist->m_length;

}
// 返回线性表长度（数据元素个数）


void *
GetElem(const PLIST plist, const UINT i) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return NULL;

	}

	if (i > plist->m_length || i <= 0) {

		return NULL;

	}

	return *(plist->m_base + i - 1);

}
// 获取线性表的第i个数据元素,如线性表为空表返回NULL,i越界返回NULL


Status
Located(const PLIST plist, const void * e) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return FALSE;

	}

	for (UINT i = 0; i < plist->m_length; i++) {

		if (*(plist->m_base + i) == e) {

			return TRUE;

		}

	}

	return FALSE;

}
// 判断线性表中是否存在值为第二个参数的数据元素


Status
ListInsert(PLIST plist, const UINT i, const void * e, const int _size) {

	assert(plist != NULL);
	assert(_size > 0);

	if (i <= 0 || i > plist->m_length + 1) {

		return ERROR;

	}

	if (plist->m_length == plist->m_listsize) {

		__addlistSize(plist);

	}

	if(EmptyList(plist)){

		memcpy(plist->m_base, e, _size);

		goto fend;
	
	}
	else if (i == plist->m_length + 1) {

		memcpy(plist->m_base + i - 1, e, _size);

		goto fend;

	}
	else {

		for (UINT j = plist->m_length; j >= i; j--) {

			memcpy(plist->m_base + j, plist->m_base + j - 1, _size);

		}

		memcpy(plist->m_base + i - 1, e, _size);

		goto fend;

	}

fend:
	plist->m_length++;
	return OK;

}
// 线性表插入数据元素（在第二个参数位置插入元素，值为第三个参数的值，第四个参数为数据元素的大小）


Status
ListRemove(PLIST plist, const UINT i) {

	assert(plist != NULL);

	if (i <= 0 || i > plist->m_length) {

		return ERROR;

	}

	if (EmptyList(plist)) {

		return ERROR;

	}

	if (i == plist->m_length) {

		*(plist->m_base + i - 1) = 0;

		goto fend;

	}
	else {

		for (UINT j = i - 1; j < plist->m_length - 1; j++) {

			*(plist->m_base + j) = *(plist->m_base + j + 1);

			goto fend;

		}

	}

fend:
	plist->m_length--;
	return OK;

}
// 线性表删除数据元素（删除位置为第二个参数）


static Status
__addlistSize(PLIST plist) {

	assert(plist != NULL);

	void ** add = (void **)realloc(plist->m_base,
		(plist->m_listsize + LISTINCREMENT) * sizeof(void *));

	if (!add) {

		exit(OVERFLOW);

	}

	plist->m_base = add;
	plist->m_listsize += LISTINCREMENT;

	return OK;

}
// 静态函数，增加线性表的容量

/*
------------------------------------------------------------------------------
*/





/*
---------------------------------- LinkList ----------------------------------
*/

static PNODE
__newNode(void *, const int);
// 创建一个新的节点，其数据域为传入的参数的值

/*
+
-               函数定义
+
*/

Status
FreeNode(PNODE node) {

	assert(node != NULL);

	if (node->m_pre != NULL) {

		PNODE tmp = node->m_pre;
		tmp->m_next = node->m_next;

	}
	if (node->m_next != NULL) {

		PNODE tmp = node->m_next;
		tmp->m_pre = node->m_pre;

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

	lklist->m_cnt = 0;
	lklist->m_head = NULL;
	lklist->m_tail = NULL;

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
	PNODE cur = lklist->m_head;

	while (cur != NULL) {

		pre = cur->m_next;
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
	PNODE cur = lklist->m_head;

	while (cur != NULL) {

		pre = cur->m_next;
		free(cur);
		cur = pre;

	}

	lklist->m_head = NULL;
	lklist->m_tail = NULL;
	lklist->m_cnt = 0;

	return OK;

}
// 清空链表为空链表


Status
EmptylkList(const PLINKLIST lklist) {

	assert(lklist != NULL);

	if (lklist->m_cnt == 0) {

		return TRUE;

	}

	return FALSE;

}
// 判断一个链表是否为空，是则返回TRUE；否则返回FALSE


Status
AddNode(PLINKLIST lklist, void * e, const int _size) {

	assert(lklist != NULL);
	assert(_size > 0);

	PNODE newnode = __newNode(e, _size);

	if (EmptylkList(lklist)) {

		lklist->m_head = newnode;
		lklist->m_tail = newnode;

	}
	else {

		PNODE tmp = NULL;
		tmp = lklist->m_tail;
		lklist->m_tail->m_next = newnode;
		lklist->m_tail = newnode;
		lklist->m_tail->m_pre = tmp;

	}

	lklist->m_cnt++;

	return OK;

}
// 为链表新建一个节点，其数据域为传入的第二个参数的值（默认插入顺序从尾部插入），第三个参数为数据元素的大小


Status
RemoveNode(PLINKLIST lklist) {

	assert(lklist != NULL);

	PNODE tmp = lklist->m_tail;

	if (EmptylkList(lklist)) {

		return ERROR;

	}

	lklist->m_tail = lklist->m_tail->m_pre;
	lklist->m_tail->m_next = NULL;
	lklist->m_cnt--;

	free(tmp);
	tmp = NULL;

	return OK;

}
// 链表删除一个结点。(默认从尾部删除)


int
lkListLength(const PLINKLIST lklist) {

	assert(lklist != NULL);

	return lklist->m_cnt;

}
// 返回链表的长度(元素个数)


PNODE
GetNode(const PLINKLIST lklist, void * e) {

	assert(lklist != NULL);

	if (EmptylkList(lklist)) {

		return NULL;

	}

	PNODE node = lklist->m_head;

	for (; node != NULL; node = node->m_next) {

		if (node->m_data == e) {

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

	assert(_size > 0);

	assert(node != NULL);

	PNODE tmp = node->m_next;
	PNODE newnode = __newNode(e, _size);

	newnode->m_next = tmp;
	newnode->m_pre = node;

	node->m_next = newnode;
	tmp->m_pre = newnode;

	return OK;


}
// 在第一参数结点后插入数据域为第二个参数的新节点， 第三个参数为数据元素的大小


Status
InsertNodeBefore(PNODE node, void * e, const int _size) {

	assert(_size > 0);

	assert(node != NULL);

	PNODE tmp = node->m_pre;
	PNODE newnode = __newNode(e, _size);

	newnode->m_pre = tmp;
	newnode->m_next = node;

	tmp->m_next = newnode;
	node->m_pre = newnode;

	return OK;

}
// 在第一参数结点前插入数据域为第二个参数的新节点，第三个参数为数据元素的大小


static PNODE
__newNode(void * e, const int _size) {

	assert(_size > 0);

	PNODE newnode = (PNODE)malloc(sizeof(NODE));
	if (!newnode) {

		exit(OVERFLOW);

	}

	memcpy(newnode->m_data, e, _size);
	newnode->m_next = NULL;
	newnode->m_pre = NULL;

	return newnode;

}
// 创建一个新的节点，其数据域为传入的参数的值

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- Stack -----------------------------------
*/

static Status
__addStackSize(PSTACK);
// 增加栈的容量

/*
+
-               函数定义
+
*/
PSTACK
InitStack(const int _size) {

	assert(_size > 0);

	PSTACK sqs = (PSTACK)malloc(sizeof(STACK));
	if (!sqs) {

		exit(OVERFLOW);

	}

	sqs->m_base = (void **)malloc(STACKINITSIZE * _size);
	if (!(sqs->m_base)) {

		exit(OVERFLOW);

	}	
	
	sqs->m_top = sqs->m_base;
	sqs->m_stacksize = STACKINITSIZE;
	sqs->m_cnt = 0;

	return sqs;

}
// 构造一个空栈


Status
DestroyStack(PSTACK sqs) {

	assert(sqs != NULL);

	free(sqs->m_base);
	sqs->m_base = NULL;
	sqs->m_top = NULL;

	free(sqs);
	sqs = NULL;

	return OK;

}
// 销毁栈，释放资源


Status
ClearStack(PSTACK sqs) {

	assert(sqs != NULL);

	sqs->m_top = sqs->m_base;
	sqs->m_cnt = 0;

	return OK;

}
// 将栈元素清空，置为空栈


Status
StackEmpty(const PSTACK sqs) {

	assert(sqs != NULL);

	if (sqs->m_cnt == 0)
		return TRUE;

	return FALSE;

}
// 若栈为空栈，返回TRUE，否则返回FALSE


int
StackLength(const PSTACK sqs) {

	assert(sqs != NULL);

	return sqs->m_cnt;

}
// 返回栈元素的个数，即栈的长度


Status
GetTop(const PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);
	assert(_size > 0);

	if (StackEmpty(sqs)) {

		return ERROR;

	}

	memcpy(e, sqs->m_top - 1, _size);

	return OK;

}
// 若栈不空，返回栈顶元素的值；否则返回NULL。第二个参数为数据元素的大小


Status
Push(PSTACK sqs, const void * e, const int _size) {

	assert(sqs != NULL);
	assert(_size > 0);

	if (sqs->m_cnt == sqs->m_stacksize) {

		__addStackSize(sqs);

	}

	memcpy(sqs->m_top, e, _size);

	sqs->m_top++;
	sqs->m_cnt++;

	return OK;

}
// 插入元素e为新的栈顶元素，第三个参数是数据元素的大小


Status
Pop(PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);
	assert(_size > 0);

	if (StackEmpty(sqs)) {

		return ERROR;

	}

	sqs->m_top--;
	sqs->m_cnt--;

	memcpy(e, sqs->m_top, _size);

	return OK;

}
// 若栈不空，则删除栈顶元素，并返回其值，第三个参数是数据元素的大小


static Status
__addStackSize(PSTACK sqs) {

	assert(sqs != NULL);

	void **add = (void **)realloc(sqs->m_base,
		(sqs->m_stacksize + STACKINCREMENT) * sizeof(*(sqs->m_top)));

	if (!add) {

		exit(OVERFLOW);

	}

	sqs->m_base = add;
	sqs->m_stacksize += STACKINCREMENT;

	return OK;

}
// 增加栈的容量

/*
-----------------------------------------------------------------------------
*/




/*
----------------------------------- Quene -----------------------------------
*/

static PQNODE
__newQnode(const void *, const int);
// 静态函数，创建一个新的队列结点

static Status
__destroyQnode(PQNODE);
// 静态函数，删除传入的结点

/*
+
-              函数定义
+
*/

PQUENE
InitQuene() {

	PQUENE pQuene = (PQUENE)malloc(sizeof(QUENE));
	if (!pQuene)
		exit(OVERFLOW);

	pQuene->m_front = NULL;
	pQuene->m_rear  = NULL;
	pQuene->m_cnt   = 0;

	return pQuene;

}
// 构造一个空队列


Status
DestroyQuene(PQUENE pQuene) {

	assert(pQuene != NULL);

	ClearQuene(pQuene);

	free(pQuene);
	pQuene = NULL;

	return OK;

}
// 销毁队列，释放内存资源


Status
ClearQuene(PQUENE pQuene) {

	assert(pQuene != NULL);

	if (!EmptyQuene(pQuene)) {

		PQNODE pPre = NULL;
		PQNODE pCur = pQuene->m_front;

		while (pCur != NULL) {

			pPre = pCur->m_nex;
			__destroyQnode(pCur);
			pCur = pPre;

		}

	}

	pQuene->m_cnt = 0;

	return OK;

}
// 将队列清空为空队列


Status
EmptyQuene(const PQUENE pQuene) {

	assert(pQuene != NULL);

	if (pQuene->m_cnt == 0)
		return TRUE;

	return FALSE;

}
// 若队列为空队列，返回TRUE，否则返回FALSE


UINT
QueneLength(const PQUENE pQuene) {

	assert(pQuene != NULL);

	return pQuene->m_cnt;

}
// 返回队列元素个数，及队列长度


Status
GetHead(const PQUENE pQuene, void * e, const int _size) {

	assert(pQuene != NULL);
	assert(e != NULL);
	assert(_size > 0);

	memcpy(e, pQuene->m_front->m_data, _size);

	return OK;

}
// 用第二个参数获取队头元素的值，第三个参数传入数据元素的大小，不删除队头元素的值


Status
EnQuene(PQUENE pQuene, const void * e, const int _size) {

	assert(pQuene != NULL);
	assert(e != NULL);
	assert(_size > 0);

	PQNODE newNode = __newQnode(e, _size);

	if (EmptyQuene(pQuene)) {

		pQuene->m_front = newNode;
		pQuene->m_rear  = newNode;

	}
	else {

		pQuene->m_rear->m_nex = newNode;
		newNode->m_pre = pQuene->m_rear;

		pQuene->m_rear = newNode;

	}

	pQuene->m_cnt++;

	return OK;

}
// 插入元素e为队列的新队尾元素


Status
DeQuene(PQUENE pQuene, void * e, const int _size) {

	assert(pQuene != NULL);
	assert(_size > 0);

	if (EmptyQuene(pQuene)) {

		return ERROR;

	}

	memcpy(e, pQuene->m_front->m_data, _size);

	PQNODE pTmp = pQuene->m_front;

	pQuene->m_front = pTmp->m_nex;

	pQuene->m_front->m_pre = NULL;

	pQuene->m_cnt--;

	__destroyQnode(pTmp);

	return OK;

}
// 若队列不空，删除队列的头元素，并用第二个参数返回其值


static PQNODE
__newQnode(const void * e, const int _size) {

	assert(e != NULL);
	assert(_size > 0);

	PQNODE newNode = (PQNODE)malloc(sizeof(QNODE));
	if (!newNode)
		exit(OVERFLOW);

	newNode->m_data = (void *)malloc(_size);
	if (!(newNode->m_data))
		exit(OVERFLOW);

	memcpy(newNode->m_data, e, _size);

	newNode->m_nex = NULL;
	newNode->m_pre = NULL;

	return newNode;

}
// 静态函数，创建一个新的队列结点


static Status
__destroyQnode(PQNODE pQnode) {

	assert(pQnode != NULL);

	free(pQnode->m_data);
	pQnode->m_data = NULL;

	free(pQnode);
	pQnode = NULL;

	return OK;

}
// 静态函数，删除传入的结点


/*
-----------------------------------------------------------------------------
*/





/*
----------------------------------- String -----------------------------------
*/

static
__getNext(int *, char *, int);

/*
+
-              函数定义
+
*/
PSTRING
StrAssign(char * chars) {

	assert(chars != NULL);

	int len = 0;

	PSTRING pString = (PSTRING)malloc(sizeof(STRING));
	if (!pString)
		exit(OVERFLOW);

	for (char * i = chars; *i != '\0'; len++, i++)
		; // 求串chars的长度

	pString->m_ch = (char *)malloc(len * sizeof(char));
	if (!(pString->m_ch))
		exit(OVERFLOW);

	for (int i = 0; i < len; i++) {

		*(pString->m_ch + i) = chars[i];

	}

	pString->m_length = len;
	
	return pString;

}
// 生成一个其值等于串常量chars的串


int
StrLength(const PSTRING pString) {

	assert(pString != NULL);

	return pString->m_length;

}
// 返回串的长度


int
StrCompare(const PSTRING arg1, const PSTRING arg2) {

	assert(arg1 != NULL);
	assert(arg2 != NULL);

	for (int i = 0; i < arg1->m_length && i < arg2->m_length; i++) {

		if (arg1->m_ch[i] != arg2->m_ch[i])
			return (arg1->m_ch[i] - arg2->m_ch[i]);

	}

	return (arg1->m_length - arg2->m_length);

}
// 串比较，若相等返回0，若arg1 > arg2，返回值>0,否则返回值<0


Status
ClearString(PSTRING pString) {

	assert(pString != NULL);

	if (pString->m_ch) {

		free(pString->m_ch);

		pString->m_ch = NULL;

	}

	pString->m_length = 0;

	return OK;
		

}
// 将串清空为空串


PSTRING
StrConcat(PSTRING pStr1, PSTRING pStr2) {

	assert(pStr1 != NULL);
	assert(pStr2 != NULL);

	PSTRING nStr = (PSTRING)malloc(sizeof(STRING));
	if (!nStr)
		exit(OVERFLOW);

	nStr->m_ch = (char *)malloc((pStr1->m_length + pStr2->m_length) * sizeof(char));
	if (!(nStr->m_ch))
		exit(OVERFLOW);

	for (int i = 0; i < pStr1->m_length; i++) {

		nStr->m_ch[i] = pStr1->m_ch[i];

	}

	for (int i = 0; i < pStr2->m_length; i++) {

		nStr->m_ch[i + pStr1->m_length] = pStr2->m_ch[i];

	}

	nStr->m_length = pStr1->m_length + pStr2->m_length;

	return nStr;

}
// 返回由两串联结而成的新串


PSTRING
SubString(PSTRING pStr, const int pos, const int len) {

	assert(pStr != NULL);

	if (pos < 0 || pos >= pStr->m_length || len < 0 || len > pStr->m_length - pos)
		return NULL;

	PSTRING subStr = (PSTRING)malloc(len * sizeof(STRING));
	if (!subStr)
		exit(OVERFLOW);

	subStr->m_ch = (char *)malloc(len * sizeof(char));
	if (!(subStr->m_ch))
		exit(OVERFLOW);

	for (int i = 0; i < len; i++) {

		subStr->m_ch[i] = pStr->m_ch[i + pos];

	}

	subStr->m_length = len;

	return subStr;

}
// 返回串从第二个参数（从0开始计）起，长度为第三个参数的子串


int
StrIndex(PSTRING pStr, PSTRING pPat, int pos) {

	// 采用 KMP 算法

	assert(pStr != NULL);
	assert(pPat != NULL);

	int i = pos, j = 0;

	int * NEXT = (int *)malloc(pPat->m_length * sizeof(int));
	if (!NEXT)
		exit(OVERFLOW);

	__getNext(NEXT, pPat->m_ch, pPat->m_length);

	while (i < pStr->m_length && j < pPat->m_length) {

		if (j == -1 || pStr->m_ch[i] == pPat->m_ch[j]) {

			i++;
			j++;

		} // 匹配成功，或者 j=-1（及从模式串第一位开始匹配）
		else {

			j = NEXT[j];

		} // 失配，j 回溯

	}

	if (j >= pPat->m_length)
		return i - pPat->m_length;

	return 0;

}
// 第一个参数为主串，第二个参数为模式串，第三个参数为开始匹配的位置


static
__getNext(int * next, char * pat, int len) {

	assert(next != NULL);
	assert(pat != NULL);

	int i = 0, j = -1;
	next[0] = -1;

	while (i < len) {

		if (j == -1 || pat[i] == pat[j]) {

			i++;
			j++;
			next[i] = j;

		}
		else
			j = next[j];

	}

}

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- Array -----------------------------------
*/

static int
__locate(PARRAY, va_list);
// 若va_list指示的各个下标合法，则求出该下标元素在数组中的映像地址off，否则返回-1

/*
+
-              函数定义
+
*/
PARRAY
InitArray(int size, int dim, ...) {

	if (dim < 1)
		return NULL;

	int     elemCnt = 1;
	va_list ap;
	
	PARRAY pArray = (PARRAY)malloc(sizeof(ARRAY));
	if (!pArray)
		exit(OVERFLOW);

	pArray->m_dim = dim;

	pArray->m_bounds = (int *)malloc(dim * sizeof(int));
	if (!(pArray->m_bounds))
		exit(OVERFLOW);

	va_start(ap, dim);
	for (int i = 0; i < dim; i++) {

		pArray->m_bounds[i] = va_arg(ap, int);
		if (pArray->m_bounds[i] < 0)
			return NULL;

		elemCnt *= pArray->m_bounds[i];

	} // 储存数组各个维界长度，并计算数据元素总数
	va_end(ap);

	pArray->m_base = (void *)malloc(size * elemCnt);
	if (!(pArray->m_base))
		exit(OVERFLOW);

	pArray->m_constants = (int *)malloc(dim * sizeof(int));
	if (!(pArray->m_constants))
		exit(OVERFLOW);

	pArray->m_constants[dim - 1] = 1;
	for (int i = dim - 2; i >= 0; i--) {

		pArray->m_constants[i] = pArray->m_bounds[i + 1] * pArray->m_constants[i + 1];

	} // 各个维界元素首地址偏转量

	return pArray;

}
// 若维数和各维长度合法，则构造相应的数组，将其返回，否则返回NULL


Status
DestoryArray(PARRAY * ppArray) {

	assert(ppArray != NULL);

	if ((*ppArray)->m_base)
		free((*ppArray)->m_base);

	if ((*ppArray)->m_bounds)
		free((*ppArray)->m_bounds);

	if ((*ppArray)->m_constants)
		free((*ppArray)->m_constants);

	free(*ppArray);

	*ppArray = NULL;

	return OK;

}
// 销毁数组，释放内存资源


Status
Value(PARRAY pArray, const int size, void * e, ...) {

	assert(pArray != NULL);
	assert(e != NULL);

	va_list ap;
	int result;

	va_start(ap, e);

	if ((result = __locate(pArray, ap)) == -1)
		return ERROR;

	va_end(ap);

	memcpy(e, (char *)(pArray->m_base) + result * size, size);

	return OK;

}
// 若各个下标不越界，e赋值为指定下标元素的值，并返回OK


Status
Assign(PARRAY pArray, const int size, void * e, ...) {

	assert(pArray != NULL);
	assert(e != NULL);

	va_list ap;
	int result;

	va_start(ap, e);

	if ((result = __locate(pArray, ap)) == -1)
		return ERROR;

	va_end(ap);

	memcpy((char *)(pArray->m_base) + result * size, e, size);

	return OK;

}
// 若各个下标不越界，则将e的值赋给指定下标元素，并返回OK


static int
__locate(PARRAY pArray, va_list ap) {

	assert(pArray != NULL);

	int off = 0;

	for (int i = 0; i < pArray->m_dim; i++) {

		int ind = va_arg(ap, int);
		if (ind < 0 || ind >= pArray->m_bounds[i])
			return -1;

		off += pArray->m_constants[i] * ind;

	}

	return off;

}
// 若va_list指示的各个下标合法，则求出该下标元素在数组中的映像地址off，否则返回-1

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- SMatrix -----------------------------------
*/

// 稀疏矩阵

/*
+
-              函数定义
+
*/

PTRIPLE
GetTriple(void ** args, const int size, const int x, const int y) {

	assert(args != NULL);

	void * com = (void *)malloc(size);
	if (!com)
		exit(OVERFLOW);

	memset(com, 0, size);

	int cnt = 0;

	// 判断非零元的个数
	for(int i = 0; i < x; i++)
		for (int j = 0; j < y; j++) {

			if (memcmp(com, (void *)(*((char **)args + i) + j * size), size) != 0)
				cnt++;

		}

	// 分配三元组数组
	PTRIPLE pTriple = (PTRIPLE)malloc(cnt * sizeof(TRIPLE));
	if (!pTriple)
		exit(OVERFLOW);

	for (int i = 0; i < cnt; i++)
		pTriple[i].m_data = (void *)malloc(size);

	cnt = 0;
	
	//  三元数组赋值
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++) {

			if (memcmp(com, (void *)(*((char **)args + i) + j * size), size) != 0) {

				pTriple[cnt].i = i;
				pTriple[cnt].j = j;

				memcpy(pTriple[cnt].m_data, 
					(void *)(*((char **)args + i) + j * size), 
					size);
 
				cnt++;

			}
				

		}

	free(com);
	com = NULL;

	return pTriple; // 返回三元数组

}
// 从一个二维数组中取得非零元素三元组


PSMATRIX
CreateSMatrix(const PTRIPLE pTriple, const int row, const int col, const int cnt) {

	assert(pTriple != NULL);

	PSMATRIX pSmatrix = (PSMATRIX)malloc(sizeof(SMATRIX));
	if (!pSmatrix)
		exit(OVERFLOW);

	pSmatrix->m_pTriples = pTriple;

	pSmatrix->mu = row;
	pSmatrix->nu = col;
	pSmatrix->tu = cnt;

	return pSmatrix;

}
// 创建稀疏矩阵


Status
DestroySMatrix(PSMATRIX * pSmatrix) {

	assert(pSmatrix != NULL);


	for (int i = 0; i < (*pSmatrix)->tu; i++) {

		free(((*pSmatrix)->m_pTriples + i)->m_data);
		((*pSmatrix)->m_pTriples + i)->m_data = NULL;

	}

	free((*pSmatrix)->m_pTriples);
	(*pSmatrix)->m_pTriples = NULL;

	free((*pSmatrix));
	pSmatrix = NULL;

	return OK;

}
// 销毁稀疏矩阵，释放内存资源
/*
-------------------------------------------------------------------------------
*/






/*
----------------------------------- BinaryTree -----------------------------------
*/

// 二叉树

static PTNODE
__createTnode(void *, const int);
// 根据参数生成一个二叉树结点


/*
+
-              函数定义
+
*/

PBITREE
InitBiTree() {

	PBITREE pBiTree = (PBITREE)malloc(sizeof(BITREE));
	if (!pBiTree)
		exit(OVERFLOW);

	pBiTree->m_root = NULL;
	pBiTree->m_cnt  = 0;

	return pBiTree;

}
// 构造一个空二叉树


static PTNODE
__createTnode(void * e, const int size) {

	assert(e != NULL);
	assert(size >= 0);

	PTNODE pTnode = (PTNODE)malloc(sizeof(TNODE));
	if (!pTnode)
		exit(OVERFLOW);

	pTnode->m_data = (void *)malloc(size);
	if (!(pTnode->m_data))
		exit(OVERFLOW);

	memcpy(pTnode->m_data, e, size);

	pTnode->m_lChild = NULL;
	pTnode->m_rChild = NULL;

	return pTnode;

}
// 根据参数生成一个二叉树结点


/*
----------------------------------------------------------------------------------
*/
