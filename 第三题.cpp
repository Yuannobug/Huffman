#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>

typedef struct leaf
{
	int name;
	int fry;
	struct leaf* lchild;
	struct leaf* rchild;
	struct leaf* next;
	struct leaf* pre;
}leaf,*pleaf;

typedef struct stacknode
{
	int data;
	struct stacknode* next;
	struct stacknode* pre;
}stacknode,*pstacknode;

typedef struct stack
{
	pstacknode tail;
	pstacknode head;
}stack,*pstack;


void Enlist(pleaf& head,int e,int num)
{
	pleaf p = NULL;
	pleaf p1 = head;
	pleaf p2 = head;
	if (head == NULL)
	{
		p = (pleaf)malloc(sizeof(leaf));
		if (p == NULL)
		{
			printf("error");
			exit;
		}
		head = p;
		head->next = NULL;
		head->fry = e;
		head->name = num;
		p->lchild = NULL;
		p->rchild = NULL;
	}
	else if (e < head->fry)
	{
		p = (pleaf)malloc(sizeof(leaf));
		if (p == NULL)
		{
			printf("error");
			exit;
		}
		p->next = head;
		head->pre = p;
		head = p;
		p->name = num;
		p->fry = e;
		p->lchild = NULL;
		p->rchild = NULL;
	}
	else 
	{
		while (p1!=NULL&& e > p1->fry)
		{
			p2 = p1;
			p1 = p1->next;
	    }
		p = (pleaf)malloc(sizeof(leaf));
		if (p == NULL)
		{
			printf("error");
			exit;
		}
		if (p1 == NULL)
		{
			p2->next = p;
			p->pre = p2;
			p->fry = e;
			p->name = num;
			p->next = NULL;
			p->lchild = NULL;
			p->rchild = NULL;
		}
		else
		{
			p1->pre->next = p;
			p->pre = p1->pre;
			p->next = p1;
			p1->pre = p;
			p->fry = e;
			p->name = num;
			p->lchild = NULL;
			p->rchild = NULL;
		}
	}
}

void sum(pleaf& head)
{
	pleaf p = (pleaf)malloc(sizeof(leaf));
	pleaf head1 = head;
	pleaf head2 = head->next;
	if (p == NULL)
	{
		printf("error");
		exit;
	}
	p->lchild = head;
	p->rchild = head->next;
	p->fry = head->fry + head->next->fry;
	p->name = 0;
	head = head->next->next;
	pleaf p1 = head;
	pleaf p2 = head;
	if (head == NULL)
	{
		head = p;
		p->next = NULL;
	}
	else
	{
		if (p->fry < head->fry)
		{
			p->next = head;
			head->pre = p;
			head = p;
		}
		else
		{
			while (p1 != NULL && p->fry>= p1->fry)
			{
				p2 = p1;
				p1 = p1->next;
			}
			if (p1 == NULL)
			{
				p2->next = p;
				p->pre = p2;
				p->next = NULL;
			}
			else
			{
				p1->pre->next = p;
				p->pre = p1->pre;
				p->next = p1;
				p1->pre = p;
			}
		}
	}
}

void Enstack(pstack& S,int i)
{
	pstacknode p =(pstacknode)malloc(sizeof(stacknode));
	if (p == NULL)
	{
		printf("error");
		exit;
	}
	p->data = i;
	if (S->head == S->tail && S->head == NULL)
	{
		S->head = p;
		S->tail = p;
		S->head->next = NULL;
	}
	else
	{
		S->tail->next = p;
		p->pre = S->tail;
		S->tail = p;
		p->next = NULL;
	}

}

void Destack(pstack& S)
{
	pstacknode p = NULL;
	if (S->head == S->tail && S->head == NULL)
	{
		printf("error");
		return;
	}
	else if (S->head == S->tail && S->head != NULL)
	{
		free(S->head);
		S->head = S->tail = NULL;
	}
	else
	{
		p = S->tail->pre;
		S->tail->pre->next = NULL;
		free(S->tail);
		S->tail = p;
	}
}

void Print(pleaf T, int  mycode[][10], pstack& S)//
{
	int i = 0;
	pstacknode p = S->head;
	if (T->lchild==NULL&&T->rchild==NULL)//
	{
		while (p != NULL)
		{
			*(*(mycode + T->name - 1) + i) = p->data;
			p = p->next;
			i++;
		}
		*(*(mycode + T->name - 1) + i) = -1;
	}
    else
	{
		Enstack(S, 0);
		Print(T->lchild,mycode,S);
		Destack(S);
		Enstack(S,1);
		Print(T->rchild, mycode, S);
		Destack(S);
	}
	
}

int main()
{
	int k = 0; int i = 0; int e = 0; int j = 0;
	pleaf head = NULL;
	stack S = {0};
	scanf("%d", &k);
	for (i = 0; i < k; i++)
	{
		scanf("%d", &e);
		Enlist(head,e,i+1);
	}
	while (head->next != NULL)
	{
		sum(head);
	}
	int mycode[100][10] = { 0 };
	S.head=S.tail = NULL;
	pstack S1 = &S;
	Print(head,mycode,S1);//
	for (i = 0; i < k; i++)//
	{
		j = 0;
		while (mycode[i][j] != -1)
		{
			printf("%d", mycode[i][j]);
			j++;
		}
		printf("\n");
	}
}