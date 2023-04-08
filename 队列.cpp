#include<stdio.h>
#define MaxSize 4
typedef struct{
	int data[MaxSize];
	int front,rear;
}SqQueue;

//队列初始化
void InitQueue(SqQueue& Q){
	Q.front=0;
	//尾指针指向队尾元素 
	Q.rear=MaxSize-1; 
}
 
//判断队列是否为空
bool IsEmpty(SqQueue Q){return ((Q.rear+1)%MaxSize==Q.front);}
//判断队列是否为满
bool IsFull(SqQueue Q){return ((Q.rear+1)%MaxSize==Q.front);}
//入队
void EnQueue(SqQueue& Q,int e){
	if(IsFull(Q)) return;
	Q.rear=(Q.rear+1)%MaxSize;
	Q.data[Q.rear]=e;
} 
//出队
void DeQueue(SqQueue& Q,int& e){
	if(IsEmpty(Q)) return;
	//尾指针指向队尾元素下一个位置 
	e=Q.data[Q.front];
	Q.front=(Q.front+1)%MaxSize;
}
//打印队头元素 
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
