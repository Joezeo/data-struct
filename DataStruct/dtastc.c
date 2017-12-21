#include "dtastc.h"

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

	sqs->base = (void **)malloc(STACKINITSIZE * sizeof(void*));
	if (!(sqs->base)) {

		exit(OVERFLOW);

	}	
	
	sqs->top = sqs->base;
	sqs->stacksize = STACKINITSIZE;
	sqs->cnt = 0;

	return sqs;

}
// 构造一个空栈


Status
DestroyStack(PSTACK sqs) {

	assert(sqs != NULL);

	free(sqs->base);
	sqs->base = NULL;
	sqs->top = NULL;

	free(sqs);
	sqs = NULL;

	return OK;

}
// 销毁栈，释放资源


Status
ClearStack(PSTACK sqs) {

	assert(sqs != NULL);

	sqs->top = sqs->base;
	sqs->cnt = 0;

	return OK;

}
// 将栈元素清空，置为空栈


Status
StackEmpty(const PSTACK sqs) {

	assert(sqs != NULL);

	if (sqs->cnt == 0)
		return TRUE;

	return FALSE;

}
// 若栈为空栈，返回TRUE，否则返回FALSE


int
StackLength(const PSTACK sqs) {

	assert(sqs != NULL);

	return sqs->cnt;

}
// 返回栈元素的个数，即栈的长度


void *
GetTop(const PSTACK sqs) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return NULL;

	}

	return *(sqs->top - 1);

}
// 若栈不空，用返回栈顶元素地址；否则返回ERROR


Status
Push(PSTACK sqs, void * e) {

	assert(sqs != NULL);

	assert(sqs != NULL);

	if (sqs->cnt == sqs->stacksize) {

		AddStackSize(sqs);

	}

	*(sqs->top) = e;
	sqs->cnt++;

	return OK;

}
// 插入元素e为新的栈顶元素

void *
Pop(PSTACK sqs) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return NULL;

	}

	sqs->top--;
	sqs->cnt--;

	return *(sqs->top + 1);

}
// 若栈不空，则删除栈顶元素，并返回其值


static Status
AddStackSize(PSTACK sqs) {

	assert(sqs != NULL);

	void **add = (void **)realloc(sqs->base,
		(sqs->stacksize + STACKINCREMENT) * sizeof(void*));

	if (!add) {

		exit(OVERFLOW);

	}

	sqs->base = add;
	sqs->stacksize += STACKINCREMENT;

	return OK;

}
// 增加栈的容量
