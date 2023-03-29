#include <stdio.h>
#include <stdlib.h>    
 
typedef struct LNode {
    int data;    //�洢������ݡ�
    struct LNode* next;  //ָ����һ������ָ�롣
}LNode,*LinkList;

//��ʼ����ͷ�������� 
void InitList(LinkList& L){
	//�ɴ˿������ܽ�LNode* ����һ������ 
	L = (LinkList)malloc(sizeof(LNode));
	//�ÿ�ͷ��㣬����ʼ��L��nextָ�� 
	L->next = NULL;
}

//�жϴ�ͷ���������Ƿ�Ϊ�� 
bool IsEmpty(LinkList L){
	return(L->next == NULL);
}

//��β�巨���������� 
LinkList CreateList_TailInsert(LinkList& L){
	//r��βָ�룬pΪ��ӽڵ� 
	LNode *p, *r; int e;
	//������ͷ�������� 
	InitList(L);
	r = L;
	while(scanf("%d",&e)){
		p = (LNode*)malloc(sizeof(LNode));
		p->data = e;
		//��βָ��r����p�ڵ� 
		r->next = p;
		//βָ����� 
		r = p;
	} 
	//βָ��һ��Ҫ�ÿ�,��ֹ��ӡ����������ѭ�� 
	r->next = NULL;
	return L;
}

//��ͷ�巨���������� 
LinkList CreateList_HeadInsert(LinkList& L){
//pΪ����Ľ�㣬eΪp����ֵ 
	LNode *p;int e;
//������ͷ��������
	InitList(L);
	while(scanf("%d",&e)){
		p = (LNode*)malloc(sizeof(LNode));
		p->data = e;
//��p����L�͵�һ���ڵ�֮�䡣
//��һ��p��һ���ڵ�Ϊ�գ����������p��һ���ڵ�Ϊ����ӽڵ� 
		p->next = L->next;
		L->next = p; 
	}
	return L;
}

//��ͷ�巨˼·����ת���� 
LinkList List_Reverse(LinkList& L){
	if(IsEmpty(L)){
		printf("����Ϊ��");
		return NULL; 
	}
	LNode *p = L->next;
	L->next = NULL;
	while(p){
		LNode *q=p->next;
//��һ�� p->next=NULL��֮��Ϊ�� 
		p->next = L->next;
		//��pָ���next�����뵽L֮�� 
		L->next = p;
		//�ƶ�p 
		p = q;
	}
	return L;
}

//������ң����ҵ�i����� 
LNode *GetElem(LinkList L,int i){
	if(IsEmpty(L)){
		printf("����Ϊ��");
		return NULL; 
	}
	//��׳�ԣ�����i<=0����� 
	if(i == 0) return L; // L ��= NULL 
	if(i < 0) return NULL;
		//����count���� 
		int count = 1;
		LNode *p = L->next;
		while(p && (count++ < i))
			p = p->next;
	//���ص�i������ָ�룬i���ڱ��򷵻�NULL 
		return p;
}

//��ֵ���� 
LNode *LocateElem(LinkList L,int e){
	if(IsEmpty(L)){
		printf("����Ϊ��");
		return NULL; 
	}
	//�ӵ�һ����㿪ʼ���� 
	LNode *p = L->next;
	while(p && p->data!=e) p = p->next;
	//�ҵ��ͷ��ؽ�㣬�Ҳ�������NULL 
	return p;
}

//����i-1����㣬ʵ�ֲ���
//����i��ǰ��ת���ɶ�i-1�ĺ��(ǰ������ͷ���) 
LinkList List_Insert(LinkList& L,int i,int e){
	//��iֵ���Ϸ�������ԭ���� 
	if(GetElem(L,i-1) != NULL){
		LNode* pre = GetElem(L,i-1);
		//�����ָ��s����ռ䣬��Ȼ�ͻ����Ұָ�� 
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = e;
		s->next = pre->next;
		pre->next = s;
	}
	return L;
}

//ָ�����ǰ�����,�����ǽ��������� 
bool InsertPriorNode(LNode* p,LNode* s){
	if(p || s) return false;
	//��s���뵽p�󷽣��ٽ��������� 
	s->next = p->next;
	p->next = s;
	int temp = p->data;
	p->data = s->data;
	s->data = temp;
	return true;
}

//����λ��ɾ����㣬���ؽ����ֵ�� 
LinkList List_Delete(LinkList &L,int i,int &e){
	//�ж�λ���Ƿ�Ϸ� 
	if(i < 1) return L;
	//����ǰһ���ڵ�pre 
		LNode *pre = GetElem(L,i-1);
		LNode *p = pre->next;
		e = p->data;
		pre->next = p->next;
//free(p)ֻ�����pָ����ڴ棬pָ����ָ����Ƭ�ڴ� 
		free(p);
		p = NULL;
	return L;
}

// ɾ��ָ�����p 
bool DeleteNode(LNode *p){
	if(p == NULL) return false;
	if(p->next == NULL){
		free(p);
		p=NULL;
		return true;
	}
	//����q��p�ĺ������ 
	LNode *q = p->next;
	//������ֵ��ɾ��q 
	p->data = q->data;
	p->next = q->next;
	free(q);
	return true;
}


//��ӡ������� 
void Print(LinkList L){
	//����ӡ�ڱ���� 
		L=L->next;
	while(L != NULL){
		printf("%d ",L->data);
		L = L->next;
	}
	printf("\n");
}

int main() {
	//��ʼ����ָ�� 
    	LinkList L = NULL;
    	L=CreateList_HeadInsert(L);
    	Print(L);
    	int e;
    	List_Delete(L,2,e);
    	Print(L);
}
 

