#include<stdio.h> 
#include<stdlib.h>
#define InitSize 5

typedef struct{
	int* data;
	int length,maxsize;
}SeqList;
//初始化表 
void InitList(SeqList* L){
	L->data = (int*)malloc(InitSize*sizeof(int));
	L->length = 0;
	L->maxsize = InitSize;
	printf("void InitList(SeqList* L)初始化表\n");
}
//根据序号插入值 
void ListInsert(SeqList* L,int i,int e){
	if(i<1 || i>L->length+1){
		printf("序号值%d有误",i);
	}else if(L->length >= L->maxsize){
		printf("表已满，不能插入");
	}else{
		//将第i个元素及以后的元素后移 
		for(int j = L->length;j >= i;j--)
			L->data[j] = L->data[j-1];
		L->data[i-1] = e;
		L->length++;
	}
}
void ListDelete(SeqList* L,int i,int* e){
	if(i<1||i>L->length){
		printf("序号值%d有误",i);
	}else{
		*e=L->data[i-1];
		for(int j=i-1;j<L->length-1;j++){
			L->data[j]=L->data[j+1];
		}
		L->length--;
	}
}
void PrintList(SeqList* L){
	for(int i=0;i<L->length;i++){
		printf("第%d个元素是：%d\n",i+1,L->data[i]);
	}
}
//按值查找，返回位序 
int LocateElem(SeqList* L,int e){
	int i=0;
	while(i<L->length){
		if(L->data[i]==e)
			return i+1;
			i++; 
	}
	//表中没有大小为e的元素，返回位序 0 
	return 0;
}
//按位序查找，返回元素 
int GetElem(SeqList* L,int i){
	//通过预测提高性能 
	if(i>0||i<=L->length){
		return L->data[i-1];
	}else{
		printf("位序%d不合法，返回0",i);
		return 0;
	}
}
//对动态分配的表进行扩容 
void ExSize(SeqList* L,int len){
	int*p=L->data;
	L->data=(int*)malloc((L->maxsize+len)*sizeof(int));
	for(int i=0;i<L->length;i++){
		L->data[i]=p[i];
	}
	L->maxsize=L->maxsize+len;
	//free掉了p指针，相当于free整个数组 
	free(p);
}
int main(){
	SeqList L;
	InitList(&L);
	ListInsert(&L,1,1);
	ListInsert(&L,2,2);
	ListInsert(&L,2,3);
	PrintList(&L);
	int e=-1; 
	ListDelete(&L,2,&e);
	printf("%d\n",e);
	PrintList(&L);
	int i=GetElem(&L,1); 
	int elem=GetElem(&L,i);
	printf("%d",elem); 
	return 0;
}
