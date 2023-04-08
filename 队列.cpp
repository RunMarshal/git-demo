#include<stdio.h>
#define MaxSize 4
typedef struct{
	int data[MaxSize];
	int front,rear;
}SqQueue;

//���г�ʼ��
void InitQueue(SqQueue& Q){
	Q.front=0;
	//βָ��ָ���βԪ�� 
	Q.rear=MaxSize-1; 
}
 
//�ж϶����Ƿ�Ϊ��
bool IsEmpty(SqQueue Q){return ((Q.rear+1)%MaxSize==Q.front);}
//�ж϶����Ƿ�Ϊ��
bool IsFull(SqQueue Q){return ((Q.rear+1)%MaxSize==Q.front);}
//���
void EnQueue(SqQueue& Q,int e){
	if(IsFull(Q)) return;
	Q.rear=(Q.rear+1)%MaxSize;
	Q.data[Q.rear]=e;
} 
//����
void DeQueue(SqQueue& Q,int& e){
	if(IsEmpty(Q)) return;
	//βָ��ָ���βԪ����һ��λ�� 
	e=Q.data[Q.front];
	Q.front=(Q.front+1)%MaxSize;
}
//��ӡ��ͷԪ�� 
void PrintHead(SqQueue Q){
	if(IsEmpty(Q)) return;
	printf("%d\n",Q.data[Q.front]);
}

int main(){
	SqQueue Q;
	InitQueue(Q);
	EnQueue(Q,1);
	EnQueue(Q,2);
	PrintHead(Q);
	EnQueue(Q,3);
	
	int e;
	DeQueue(Q,e);
	PrintHead(Q);
	
	EnQueue(Q,4);
	PrintHead(Q);
	DeQueue(Q,e);
	PrintHead(Q);
}
