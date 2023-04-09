#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode* lchild, *rchild;
}BiTNode,*BiTree;

typedef struct{
	//��̬����洢ջ��Ԫ�� 
	BiTree data[50]; 
	int top; //ջ��ָ�� 
}SqStack;


//���������� 
void CreateTree(BiTree &T)
{
    ElemType data;
    scanf("%d", &data);
//0�����ն˽ڵ�ֵ
    if(data == 0) {
        T = NULL;
    } else {
        T = (BiTNode *)malloc(sizeof(BiTNode));  
        T->data = data;
        printf("������%d�����ӽڵ㣺", data);
        CreateTree(T->lchild);
        printf("������%d���Һ��ӽڵ㣺", data);
        CreateTree(T->rchild);
    }
}

/*
//���������� 
void CreateTree(BiTree *T)  //����һ��Btree��ָ��ĵ�ַ
{
    ElemType data;
    scanf("%d", &data);

    if(data == 0) {    //0�����ն˽ڵ�ֵ
        *T = NULL;
    } else {
        *T = (BiTNode *)malloc(sizeof(BiTNode));  
        (*T)->data = data;
        printf("������%d�����ӽڵ㣺", data);
        CreateTree(&((*T)->lchild));
        printf("������%d���Һ��ӽڵ㣺", data);
        CreateTree(&((*T)->rchild));
    }
}
*/

//�ݹ�������� 
void PreOrder(BiTree T){
	if(T != NULL){
		printf("%d ",T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

//�ǵݹ��������
void PreOrder2(BiTree T){
	//��ʼ��ջS �� p�Ǳ���ָ�� 
	SqStack S ; S.top = -1;
	BiTree p = T;
	//p��ջ��Ϊ��ʱѭ�� 
	while(p != NULL || S.top != -1){
		// һ·���� 
		if(p){
			//vist��ǰ��㣬����ջ 
			printf("%d ",p->data);
			S.top++;
			//����p��λ�� 
			S.data[S.top] = p;
			//pһֱ�����ߣ�ֱ������Ϊ�� 
			p = p->lchild;
		}else{
			//ջ��Ԫ�س�ջ p�˺�һ�� 
			p = S.data[S.top--];
			//���������� 
			p = p->rchild;
		}
	} 
} 
//����������Ҷ�ӽ�� 
void PreOrder_PrintLeaves(BiTree T){
	if(T){
		if(!T->lchild && !T->rchild) 
			printf("%d ",T->data);
		PreOrder_PrintLeaves(T->lchild);
		PreOrder_PrintLeaves(T->rchild);
	}
}

//����������Ҷ�Ӹ���
int  PreOrder_PrintLeavesNum(BiTree T,int num){
	if(T){
		if(!T->lchild && !T->rchild){
			printf("%d ",T->data);
			num++;
		}
		PreOrder_PrintLeavesNum(T->lchild,num);
		PreOrder_PrintLeavesNum(T->rchild,num);
	}
}

//�ݹ�������� 
void InOrder(BiTree T){
	if(T != NULL){
		InOrder(T->lchild);
		printf("%d ",T->data);
		InOrder(T->rchild);
	}
}

//�ǵݹ��������
void InOrder2(BiTree T){
	//��ʼ��ջS �� p�Ǳ���ָ�� 
	SqStack S ; S.top = -1;
	BiTree p = T;
	//p��ջ��Ϊ��ʱѭ�� 
	while(p != NULL || S.top != -1){
		// һ·���� 
		if(p){
			S.top++;
			//����p��λ�� 
			S.data[S.top] = p;
			//pһֱ�����ߣ�ֱ������Ϊ�� 
			p = p->lchild;
		}else{
			//ջ��Ԫ�س�ջ p�˺�һ�� 
			p = S.data[S.top--];
			//vist��ǰ���
			printf("%d ",p->data);
			//���������� 
			p = p->rchild;
		}
	} 
} 

//�ݹ������� 
void PostOrder(BiTree T){
	if(T != NULL){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%d ",T->data);
	}
}

//�ǵݹ�������
void PostOrder2(BiTree T){
	//��ʼ��ջS �� p�Ǳ���ָ�� ,r��������ʵĽ�� 
	SqStack S ; S.top = -1;
	BiTree p = T; BiTree r = NULL;
	//p��ջ��Ϊ��ʱѭ�� 
	while(p != NULL || S.top != -1){
		// һ·�����ߵ������ 
		if(p){
			S.top++;
			//����p��λ�� 
			S.data[S.top] = p;
			//pһֱ�����ߣ�ֱ������Ϊ�� 
			p = p->lchild;
		}else{
			//��ջ����㣬���ǳ�ջ 
			p = S.data[S.top];
			//�����������ڣ���δ�����ʹ� 
			if(p->rchild && p->rchild != r){
				p = p->rchild;
			}
			else{
				p = S.data[S.top];
				S.top--;
				printf("%d ",p->data);
				r = p;
				p = NULL;
			}
		}
	} 
} 

//���������������ĸ߶�
int PostOrder_GetHeight(BiTree T){
	int h = 0;
	if(T){
		int lh = PostOrder_GetHeight(T->lchild);
		int rh = PostOrder_GetHeight(T->rchild);
		h = lh > rh ? lh + 1 : rh + 1;
		
	}
	return h;
}

//��α���������
void LevelOrder(BiTree T) {
//������������ڣ��Ž��в�α���
    if (T) {	
		ElemType front = 1,rear = 1;
        BiTree a[20] = {0};
        BiTree p = NULL;
        p = T;
//��������
        a[rear++] = p;
//�ظ�ִ�У�ֱ������Ϊ��
        while (front < rear){
//�Ӷ���ȡ��һ�����
            p = a[front++];;
//���ʵ�ǰ���
            printf("%d ", p->data);
//����ǰ�������Һ����������
            if (p->lchild) a[rear++] = p->lchild;
            if (p->rchild) a[rear++] = p->rchild;
        }
    } 
}

//�ǵݹ����� 
int Width(BiTree T){
	if(T == NULL) return 0;  
	BiTree Q[20];
//last�ǵ������ҽ���ڶ����е�λ��
	int f=1,r=1,last=1;
//temp�Ǿֲ����, maxw�������
	int temp = 0,maxwidth = 0;
//����������
	Q[r] = T;
	while(f<=last){
//ͬ��������1
		BiTNode *p = Q[f++];
		temp++; 
		if (p->lchild!=NULL)  Q[++r]=p->lchild;   
		if (p->rchild!=NULL)  Q[++r]=p->rchild;  
//�ò����
		if (f > last){
			last=r;
			if(temp > maxwidth) maxwidth=temp;
//lastָ���²�����Ԫ��, ���µ�ǰ�����
			temp=0;
		}   
	}
		return maxwidth;
}

//�ݹ����� 
int count[20]={0};
int max=0;
//k��ָ�ڼ��㣬���ô�1��ʼ 
void TreeWidth(BiTree root, int k){
        if (!root){
            return;
        }

        count[k]++;
        max = (count[k] > max ? count[k] : max);
        TreeWidth(root->lchild, k+1);
        TreeWidth(root->rchild, k+1);
}

//�ж����Ŷ������Ƿ����
bool CompareTrees(BiTree T1,BiTree T2){
	//���ǵݹ������������������һ�����Ϊ�� 
	if(T1 == NULL && T2== NULL) return 1;
	else if(T1 == NULL || T2 == NULL) return 0;
	//���жϵ�ǰ����Ƿ���ȣ�����ٱȽ����ҽ�� 
	if(T1->data != T2->data) return 0; 
	return CompareTrees(T1->lchild,T2->lchild) && CompareTrees(T1->rchild,T2->rchild);
}
//�����������Ƿ���� 
void IsEqual(){
	BiTree Tree1;
	printf("�������һ�����ĸ��ڵ�ֵ��");
	CreateTree(Tree1); 
	printf("��һ���������ɹ�\n");
	BiTree Tree2;
	printf("������ڶ������ĸ��ڵ�ֵ��");
	CreateTree(Tree2);
	printf("�ڶ����������ɹ�\n"); 
	if(CompareTrees(Tree1,Tree2) == 1) printf("���������");
	else printf("�����������");
}

int main(){
	BiTree root;
	CreateTree(root);
	LevelOrder(root); 
	return 0; 
}



