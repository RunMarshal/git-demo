#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MaxSize 50

typedef struct{
	//静态数组存储栈中元素 
	char data[MaxSize]; 
	int top; //栈顶指针 
}SqStack;
//初始化栈 
void InitStack(SqStack& S){ S.top=-1;}
//判断栈空
bool IsEmpty(SqStack S){return (S.top==-1);}
//判断栈满
bool IsFull(SqStack S){return (S.top==MaxSize-1);} 

//入栈 
bool Push(SqStack& S,char c){
	if(IsFull(S))  return false;
	S.data[++S.top]=c; return true;}
//出栈 
char Pop(SqStack& S){
	if(IsEmpty(S)) return 0;
	char x=S.data[S.top--]; return x;
}

//用顺序栈判断回文序列 
bool IsHuiWen(char* str){
	SqStack S;
	//初始化栈 
	InitStack(S);
	//获取字符串长度 
	int len=strlen(str);
	if(len==0) return false;
	int i;
	//将字符串一半字符入栈 
	for(i=0;i<len/2;i++){
		Push(S,str[i]);
	}
	//依次比较出栈字符和未入栈字符 
	while(!IsEmpty(S)){
		char temp=Pop(S);
		if(temp!=str[i++]) 
			return false;
	}
	return true;
}

//读栈顶元素
bool GetTop(SqStack S){
	if(IsEmpty(S)) return false;
	printf("%d\n",S.data[S.top]);
} 
int main(){
	char* s="abc";
	printf("%d",IsHuiWen(s));
}
