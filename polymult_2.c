#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DEGREE_A 9
#define MAX_DEGREE_B 9
#define MAX_TERM_NUM_A 3
#define MAX_TERM_NUM_B 3
#define MAX_TERM_NUM_D 8
#define REPETITION 3

typedef struct
{
   int degree;
   int* coef; //교재와 같이 MAX_DEGEE 크기의 배열로 선언해도 상관없으나 범용성을 위해 동적할당함.
} coef_poly;

typedef struct
{
   int coef;
   int expo;
} term;

void print_mult_sequence(int ,int);
void print_coef_poly(coef_poly*);
term* attach(term*, int*, int, int);
void polynomial_multiply(coef_poly , coef_poly, term*, int*, int*, int*);

int main()
{
   for(int r =0; r<REPETITION; r++)
   {
      coef_poly A;
      A.coef = (int*) malloc(sizeof(int)*(MAX_DEGREE_A+1));
      A.degree =0;
      for(int i=0; i<=MAX_DEGREE_A;i++)
         A.coef[i]=0;

      coef_poly B;
      B.coef = (int*) malloc(sizeof(int)*(MAX_DEGREE_B+1));
      B.degree =0;
      for(int i=0; i<=MAX_DEGREE_B;i++)
         B.coef[i]=0;

      term* D = (term*) malloc(sizeof(term)*MAX_TERM_NUM_D);
      int avail_D =0, start_D=0, end_D;

      for(int i=0; i<MAX_TERM_NUM_D; i++)      //initializing D
      {
         D[i].coef =0;
         D[i].expo =0;
      }

      int coef_tmp, expo_tmp;

      for(int i=0; i<MAX_TERM_NUM_A; i++)
      {
         printf("polynomial A의 '%d' 번째 항 입력 (계수 지수) 형식으로 입력\n" ,i+1);
         scanf("%d %d",&coef_tmp,&expo_tmp);
         A.coef[expo_tmp] = coef_tmp;
         A.degree= (A.degree<expo_tmp) ? expo_tmp: A.degree;
         fflush(stdin);
      }

      for(int i=0; i<MAX_TERM_NUM_B; i++)
      {
         printf("polynomial B의 '%d' 번째 항 입력 (계수 지수) 형식으로 입력\n" ,i+1);
         scanf("%d %d",&coef_tmp,&expo_tmp);
         B.coef[expo_tmp] = coef_tmp;
         B.degree= (B.degree<expo_tmp) ? expo_tmp: B.degree;
         fflush(stdin);
      }

      polynomial_multiply(A,B,D,&start_D,&end_D,&avail_D);

      printf("A 다항식");
      print_coef_poly(&A);
      printf("\n");
      printf("B 다항식");
      print_coef_poly(&B);
      printf("\n");

      printf("\nresult of multiplicaition ( D(x) )\n");
      for(int i= start_D; i<=end_D;i++)              //D(X)
      {
         printf("%dX^%d ",D[i].coef,D[i].expo);
         if(i!=end_D)
            printf(" + ");
      }
      printf("\n\n");

      free(A.coef);
      free(B.coef);
      free(D);
   }
}

void print_coef_poly(coef_poly* A)
{
   printf("\n");
   for(int i=A->degree; i>=0; i--)
   {
      printf("%dX^%d ",A->coef[i], i);
      if(i)
         printf(" + ");
   }
   printf("\n");
}

void polynomial_multiply(coef_poly A, coef_poly B, term* D, int* start_D, int* end_D, int* avail_D) // call by value or call by address
{
   *start_D = *avail_D;
   for(int i= A.degree + B.degree; i>=0; i--)  // D의 항 중 지수가 i인 항들 먼저 모두 계산.
   {
      int depth = A.degree+B.degree - i;
    //  printf("depth = %d\n",depth);
      for(int j= depth; j>=0; j--)
      {
         if((A.degree-j)>=0&&(B.degree-depth+j)>=0)     //A, B의 항들의 지수가 음수가 되면 패스.
         {
            if(((A.coef[A.degree-j])!=0)&&((B.coef[B.degree-depth+j]!=0)))       //곱하는 항들 중에 계수가 0이면 곱할 필요 없음.
            {
               attach(D, avail_D,(A.coef[A.degree-j])*(B.coef[B.degree-depth+j]),i);
            }
         }
      }
   } 
   *end_D = (*avail_D)-1; 
}

term* attach(term* D, int* avail_D, int coef_attach, int expo_attach)
{
   if(*avail_D>MAX_TERM_NUM_D) //마지막 항이랑 계수 같을 시 Attach 가능
   {
      printf("polynomail size is full\n");
      return D;
   }
   if(!*avail_D)     //in case avail =0 
   {
      D[*avail_D].coef = coef_attach;
      D[*avail_D].expo = expo_attach;
      (*avail_D)++;
      return D;
   }
   if(D[*avail_D-1].expo==expo_attach) //in case attach existing exponent
   {
      D[*avail_D-1].coef+=coef_attach;
      if(!D[*avail_D-1].coef)          //in case result of sum is 0 -> delete term
      {
         D[*avail_D-1].expo = 0;
         (*avail_D)--;  
      }
   }else if(*avail_D==MAX_TERM_NUM_D)  //in case no avail space and no match exponent 
   {
      printf("polynomail size is full\n");
      return D;

   }else{                    //in case add new exponent
      D[*avail_D].coef = coef_attach;
      D[*avail_D].expo = expo_attach;
      (*avail_D)++;
   }
   return D;
}

void print_mult_sequence(int a, int b)
{
   for(int i=a+b; i>=0;i--)
   {
      int depth= a+b-i;
      for(int j=depth; j>=0;j--)
      {
         if((a-j)>=0&&(b-depth+j)>=0)
         {
            printf("comepare a[%d] with b[%d]\n",(a-j),(b-depth+j));
         }
      }
   }


}