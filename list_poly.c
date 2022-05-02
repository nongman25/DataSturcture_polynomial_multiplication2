#include <stdio.h>
#include <stdlib.h>

typedef struct node *list;
typedef struct node
{
    int coef;
    int exp;
    list link;
};


int main()
{
    list D= (list)malloc(sizeof(struct node));
    D->coef=500;
    D->exp= 3;
    list A= (list)malloc(sizeof(struct node));
    A->coef=4;
    A->exp= 2;
    D->link=A;
    A->link = NULL;

    list A2= (list)malloc(sizeof(struct node));
    A2->coef=2;
    A2->exp= 1;

    A2->link= D->link;
    D->link = A2;


    list t= D;
    for(;t!=NULL; t=t->link)
    {
        printf("%3dx^%2d ",t->coef, t->exp);
    }
    printf("\n");


}
