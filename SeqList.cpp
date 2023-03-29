#include<stdio.h> 
#include<stdlib.h>
#define InitSize 5

typedef struct{
	int* data;
	int length,maxsize;
}SeqList;
//��ʼ���� 
void InitList(SeqList* L){
	L->data = (int*)malloc(InitSize*sizeof(int));
	L->length = 0;
	L->maxsize = InitSize;
	printf("void InitList(SeqList* L)��ʼ����\n");
}
//������Ų���ֵ 
void ListInsert(SeqList* L,int i,int e){
	if(i<1 || i>L->length+1){
		printf("���ֵ%d����",i);
	}else if(L->length >= L->maxsize){
		printf("�����������ܲ���");
	}else{
		//����i��Ԫ�ؼ��Ժ��Ԫ�غ��� 
		for(int j = L->length;j >= i;j--)
			L->data[j] = L->data[j-1];
		L->data[i-1] = e;
		L->length++;
	}
}
void ListDelete(SeqList* L,int i,int* e){
	if(i<1||i>L->length){
		printf("���ֵ%d����",i);
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
		printf("��%d��Ԫ���ǣ�%d\n",i+1,L->data[i]);
	}
}
//��ֵ���ң�����λ�� 
int LocateElem(SeqList* L,int e){
	int i=0;
	while(i<L->length){
		if(L->data[i]==e)
			return i+1;
			i++; 
	}
	//����û�д�СΪe��Ԫ�أ�����λ�� 0 
	return 0;
}
//��λ����ң�����Ԫ�� 
int GetElem(SeqList* L,int i){
	//ͨ��Ԥ��������� 
	if(i>0||i<=L->length){
		return L->data[i-1];
	}else{
		printf("λ��%d���Ϸ�������0",i);
		return 0;
	}
}
//�Զ�̬����ı�������� 
void ExSize(SeqList* L,int len){
	int*p=L->data;
	L->data=(int*)malloc((L->maxsize+len)*sizeof(int));
	for(int i=0;i<L->length;i++){
		L->data[i]=p[i];
	}
	L->maxsize=L->maxsize+len;
	//free����pָ�룬�൱��free�������� 
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
