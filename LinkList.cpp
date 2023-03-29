#include <stdio.h>
#include <stdlib.h>    
 
typedef struct LNode {
    int data;    //存储结点数据。
    struct LNode* next;  //指向下一个结点的指针。
}LNode,*LinkList;

//初始化带头结点的链表 
void InitList(LinkList& L){
	//由此看出不能将LNode* 看成一种类型 
	L = (LinkList)malloc(sizeof(LNode));
	//置空头结点，即初始化L的next指针 
	L->next = NULL;
}

//判断带头结点的链表是否为空 
bool IsEmpty(LinkList L){
	return(L->next == NULL);
}

//用尾插法创建单链表 
LinkList CreateList_TailInsert(LinkList& L){
	//r是尾指针，p为添加节点 
	LNode *p, *r; int e;
	//创建有头结点的链表 
	InitList(L);
	r = L;
	while(scanf("%d",&e)){
		p = (LNode*)malloc(sizeof(LNode));
		p->data = e;
		//用尾指针r连接p节点 
		r->next = p;
		//尾指针后移 
		r = p;
	} 
	//尾指针一定要置空,防止打印函数陷入死循环 
	r->next = NULL;
	return L;
}

//用头插法创建单链表 
LinkList CreateList_HeadInsert(LinkList& L){
//p为插入的结点，e为p的数值 
	LNode *p;int e;
//创建有头结点的链表
	InitList(L);
	while(scanf("%d",&e)){
		p = (LNode*)malloc(sizeof(LNode));
		p->data = e;
//将p插入L和第一个节点之间。
//第一次p下一个节点为空，其他情况，p下一个节点为已添加节点 
		p->next = L->next;
		L->next = p; 
	}
	return L;
}

//以头插法思路，反转链表 
LinkList List_Reverse(LinkList& L){
	if(IsEmpty(L)){
		printf("链表为空");
		return NULL; 
	}
	LNode *p = L->next;
	L->next = NULL;
	while(p){
		LNode *q=p->next;
//第一次 p->next=NULL，之后不为空 
		p->next = L->next;
		//将p指针的next结点插入到L之后 
		L->next = p;
		//移动p 
		p = q;
	}
	return L;
}

//按序查找，查找第i个结点 
LNode *GetElem(LinkList L,int i){
	if(IsEmpty(L)){
		printf("链表为空");
		return NULL; 
	}
	//健壮性，考虑i<=0的情况 
	if(i == 0) return L; // L ！= NULL 
	if(i < 0) return NULL;
		//定义count计数 
		int count = 1;
		LNode *p = L->next;
		while(p && (count++ < i))
			p = p->next;
	//返回第i个结点的指针，i大于表长则返回NULL 
		return p;
}

//按值查找 
LNode *LocateElem(LinkList L,int e){
	if(IsEmpty(L)){
		printf("链表为空");
		return NULL; 
	}
	//从第一个结点开始查找 
	LNode *p = L->next;
	while(p && p->data!=e) p = p->next;
	//找到就返回结点，找不到返回NULL 
	return p;
}

//查找i-1个结点，实现插入
//将对i的前插转化成对i-1的后插(前提是有头结点) 
LinkList List_Insert(LinkList& L,int i,int e){
	//当i值不合法，返回原链表 
	if(GetElem(L,i-1) != NULL){
		LNode* pre = GetElem(L,i-1);
		//必须给指针s分配空间，不然就会产生野指针 
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = e;
		s->next = pre->next;
		pre->next = s;
	}
	return L;
}

//指定结点前插操作,核心是交换数据域 
bool InsertPriorNode(LNode* p,LNode* s){
	if(p || s) return false;
	//将s插入到p后方，再交换数据域 
	s->next = p->next;
	p->next = s;
	int temp = p->data;
	p->data = s->data;
	s->data = temp;
	return true;
}

//根据位序删除结点，返回结点数值域 
LinkList List_Delete(LinkList &L,int i,int &e){
	//判断位序是否合法 
	if(i < 1) return L;
	//查找前一个节点pre 
		LNode *pre = GetElem(L,i-1);
		LNode *p = pre->next;
		e = p->data;
		pre->next = p->next;
//free(p)只清空了p指向的内存，p指针仍指向那片内存 
		free(p);
		p = NULL;
	return L;
}

// 删除指定结点p 
bool DeleteNode(LNode *p){
	if(p == NULL) return false;
	if(p->next == NULL){
		free(p);
		p=NULL;
		return true;
	}
	//定义q是p的后驱结点 
	LNode *q = p->next;
	//交换数值域，删除q 
	p->data = q->data;
	p->next = q->next;
	free(q);
	return true;
}


//打印输出链表 
void Print(LinkList L){
	//不打印哨兵结点 
		L=L->next;
	while(L != NULL){
		printf("%d ",L->data);
		L = L->next;
	}
	printf("\n");
}

int main() {
	//初始化空指针 
    	LinkList L = NULL;
    	L=CreateList_HeadInsert(L);
    	Print(L);
    	int e;
    	List_Delete(L,2,e);
    	Print(L);
}
 

