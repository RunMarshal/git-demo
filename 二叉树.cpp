#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode* lchild, *rchild;
}BiTNode,*BiTree;

typedef struct{
	//静态数组存储栈中元素 
	BiTree data[50]; 
	int top; //栈顶指针 
}SqStack;


//创建二叉树 
void CreateTree(BiTree &T)
{
    ElemType data;
    scanf("%d", &data);
//0代表终端节点值
    if(data == 0) {
        T = NULL;
    } else {
        T = (BiTNode *)malloc(sizeof(BiTNode));  
        T->data = data;
        printf("请输入%d的左孩子节点：", data);
        CreateTree(T->lchild);
        printf("请输入%d的右孩子节点：", data);
        CreateTree(T->rchild);
    }
}

/*
//创建二叉树 
void CreateTree(BiTree *T)  //传入一个Btree的指针的地址
{
    ElemType data;
    scanf("%d", &data);

    if(data == 0) {    //0代表终端节点值
        *T = NULL;
    } else {
        *T = (BiTNode *)malloc(sizeof(BiTNode));  
        (*T)->data = data;
        printf("请输入%d的左孩子节点：", data);
        CreateTree(&((*T)->lchild));
        printf("请输入%d的右孩子节点：", data);
        CreateTree(&((*T)->rchild));
    }
}
*/

//递归先序遍历 
void PreOrder(BiTree T){
	if(T != NULL){
		printf("%d ",T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

//非递归先序遍历
void PreOrder2(BiTree T){
	//初始化栈S ， p是遍历指针 
	SqStack S ; S.top = -1;
	BiTree p = T;
	//p或栈不为空时循环 
	while(p != NULL || S.top != -1){
		// 一路向左 
		if(p){
			//vist当前结点，并入栈 
			printf("%d ",p->data);
			S.top++;
			//储存p的位置 
			S.data[S.top] = p;
			//p一直向左走，直到左孩子为空 
			p = p->lchild;
		}else{
			//栈顶元素出栈 p退后一步 
			p = S.data[S.top--];
			//向右子树走 
			p = p->rchild;
		}
	} 
} 
//先序遍历输出叶子结点 
void PreOrder_PrintLeaves(BiTree T){
	if(T){
		if(!T->lchild && !T->rchild) 
			printf("%d ",T->data);
		PreOrder_PrintLeaves(T->lchild);
		PreOrder_PrintLeaves(T->rchild);
	}
}

//先序遍历输出叶子个数
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

//递归中序遍历 
void InOrder(BiTree T){
	if(T != NULL){
		InOrder(T->lchild);
		printf("%d ",T->data);
		InOrder(T->rchild);
	}
}

//非递归中序遍历
void InOrder2(BiTree T){
	//初始化栈S ， p是遍历指针 
	SqStack S ; S.top = -1;
	BiTree p = T;
	//p或栈不为空时循环 
	while(p != NULL || S.top != -1){
		// 一路向左 
		if(p){
			S.top++;
			//储存p的位置 
			S.data[S.top] = p;
			//p一直向左走，直到左孩子为空 
			p = p->lchild;
		}else{
			//栈顶元素出栈 p退后一步 
			p = S.data[S.top--];
			//vist当前结点
			printf("%d ",p->data);
			//向右子树走 
			p = p->rchild;
		}
	} 
} 

//递归后序遍历 
void PostOrder(BiTree T){
	if(T != NULL){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%d ",T->data);
	}
}

//非递归后序遍历
void PostOrder2(BiTree T){
	//初始化栈S ， p是遍历指针 ,r是最近访问的结点 
	SqStack S ; S.top = -1;
	BiTree p = T; BiTree r = NULL;
	//p或栈不为空时循环 
	while(p != NULL || S.top != -1){
		// 一路向左，走到最左边 
		if(p){
			S.top++;
			//储存p的位置 
			S.data[S.top] = p;
			//p一直向左走，直到左孩子为空 
			p = p->lchild;
		}else{
			//读栈顶结点，不是出栈 
			p = S.data[S.top];
			//若右子树存在，且未被访问过 
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

//后序遍历求二叉树的高度
int PostOrder_GetHeight(BiTree T){
	int h = 0;
	if(T){
		int lh = PostOrder_GetHeight(T->lchild);
		int rh = PostOrder_GetHeight(T->rchild);
		h = lh > rh ? lh + 1 : rh + 1;
		
	}
	return h;
}

//层次遍历二叉树
void LevelOrder(BiTree T) {
//如果二叉树存在，才进行层次遍历
    if (T) {	
		ElemType front = 1,rear = 1;
        BiTree a[20] = {0};
        BiTree p = NULL;
        p = T;
//根结点入队
        a[rear++] = p;
//重复执行，直至队列为空
        while (front < rear){
//从队列取出一个结点
            p = a[front++];;
//访问当前结点
            printf("%d ", p->data);
//将当前结点的左右孩子依次入队
            if (p->lchild) a[rear++] = p->lchild;
            if (p->rchild) a[rear++] = p->rchild;
        }
    } 
}

//非递归求宽度 
int Width(BiTree T){
	if(T == NULL) return 0;  
	BiTree Q[20];
//last是当层最右结点在队列中的位置
	int f=1,r=1,last=1;
//temp记局部宽度, maxw记最大宽度
	int temp = 0,maxwidth = 0;
//根结点入队列
	Q[r] = T;
	while(f<=last){
//同层结点数加1
		BiTNode *p = Q[f++];
		temp++; 
		if (p->lchild!=NULL)  Q[++r]=p->lchild;   
		if (p->rchild!=NULL)  Q[++r]=p->rchild;  
//该层结束
		if (f > last){
			last=r;
			if(temp > maxwidth) maxwidth=temp;
//last指向下层最右元素, 更新当前最大宽度
			temp=0;
		}   
	}
		return maxwidth;
}

//递归求宽度 
int count[20]={0};
int max=0;
//k是指第几层，设置从1开始 
void TreeWidth(BiTree root, int k){
        if (!root){
            return;
        }

        count[k]++;
        max = (count[k] > max ? count[k] : max);
        TreeWidth(root->lchild, k+1);
        TreeWidth(root->rchild, k+1);
}

//判断两颗二叉树是否相等
bool CompareTrees(BiTree T1,BiTree T2){
	//考虑递归结束条件，即至少有一个结点为空 
	if(T1 == NULL && T2== NULL) return 1;
	else if(T1 == NULL || T2 == NULL) return 0;
	//先判断当前结点是否相等，相等再比较左右结点 
	if(T1->data != T2->data) return 0; 
	return CompareTrees(T1->lchild,T2->lchild) && CompareTrees(T1->rchild,T2->rchild);
}
//测试两棵树是否相等 
void IsEqual(){
	BiTree Tree1;
	printf("请输入第一棵树的根节点值：");
	CreateTree(Tree1); 
	printf("第一棵树创建成功\n");
	BiTree Tree2;
	printf("请输入第二棵树的根节点值：");
	CreateTree(Tree2);
	printf("第二棵树创建成功\n"); 
	if(CompareTrees(Tree1,Tree2) == 1) printf("两棵树相等");
	else printf("两棵树不相等");
}

int main(){
	BiTree root;
	CreateTree(root);
	LevelOrder(root); 
	return 0; 
}



