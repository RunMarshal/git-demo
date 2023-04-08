#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MaxSize 50

typedef struct{
	//��̬����洢ջ��Ԫ�� 
	char data[MaxSize]; 
	int top; //ջ��ָ�� 
}SqStack;
//��ʼ��ջ 
void InitStack(SqStack& S){ S.top=-1;}
//�ж�ջ��
bool IsEmpty(SqStack S){return (S.top==-1);}
//�ж�ջ��
bool IsFull(SqStack S){return (S.top==MaxSize-1);} 

//��ջ 
bool Push(SqStack& S,char c){
	if(IsFull(S))  return false;
	S.data[++S.top]=c; return true;}
//��ջ 
char Pop(SqStack& S){
	if(IsEmpty(S)) return 0;
	char x=S.data[S.top--]; return x;
}

//��˳��ջ�жϻ������� 
bool IsHuiWen(char* str){
	SqStack S;
	//��ʼ��ջ 
	InitStack(S);
	//��ȡ�ַ������� 
	int len=strlen(str);
	if(len==0) return false;
	int i;
	//���ַ���һ���ַ���ջ 
	for(i=0;i<len/2;i++){
		Push(S,str[i]);
	}
	//���αȽϳ�ջ�ַ���δ��ջ�ַ� 
	while(!IsEmpty(S)){
		char temp=Pop(S);
		if(temp!=str[i++]) 
			return false;
	}
	return true;
}

//��ջ��Ԫ��
bool GetTop(SqStack S){
	if(IsEmpty(S)) return false;
	printf("%d\n",S.data[S.top]);
} 
int main(){
	char* s="abc";
	printf("%d",IsHuiWen(s));
}
