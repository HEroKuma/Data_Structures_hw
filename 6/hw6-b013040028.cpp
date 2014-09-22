/*============================
學號:b013040028
姓名:張力偉
日期:11/25/2013
目的：模擬多項式加法跟乘法
============================*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Link{
        int exp;
        int coef;
        struct Link* pNext;
};

typedef struct Link* Poly;
typedef struct Link* pLink;

void AddData(Poly,int,int);
void Travel(Poly);
void InputData(Poly,int);
void LinkAdd(Poly,Poly,Poly);
void LinkMul(Poly,Poly,Poly);
void RemoveCoefZero(Poly);
void ReleaseLink(Poly);

int main()
{
  int n,m;
  while(cin >> n){
        Poly A, B, Add_C, Mul_D;
        A = (pLink)malloc(sizeof(struct Link));
        A->pNext = NULL;

        B = (pLink)malloc(sizeof(struct Link));
        B->pNext = NULL;

        Add_C = (pLink)malloc(sizeof(struct Link));
        Add_C->pNext = NULL;

        Mul_D = (pLink)malloc(sizeof(struct Link));
        Mul_D->pNext = NULL;

        InputData(A,n);
        cin >> m;
        if(n == 0 && m == 0){
          ReleaseLink(A);
          ReleaseLink(B);
          ReleaseLink(Add_C);
          ReleaseLink(Mul_D);
          break;
        }
        InputData(B,m);
        LinkAdd(A, B, Add_C);
        LinkMul(A, B, Mul_D);
        RemoveCoefZero(Add_C);
        printf("ADD");
        Travel(Add_C);
        RemoveCoefZero(Mul_D);
        printf("MULT");
        Travel(Mul_D);
        ReleaseLink(A);
        ReleaseLink(B);
        ReleaseLink(Add_C);
        ReleaseLink(Mul_D);
  }

        return 0;
}

void AddData(Poly p, int _coef, int _exp)
{
        Poly tmp = p;

        while(tmp->pNext!=NULL){
                if(tmp->pNext->exp == _exp){
                        tmp->pNext->coef += _coef;
                        return ;
                }
                else if(tmp->pNext->exp > _exp){
                        Poly tmp2 = tmp->pNext;
                        tmp->pNext = (pLink)malloc(sizeof(struct Link));
                        tmp->pNext->exp = _exp;
                        tmp->pNext->coef=_coef;
                        tmp->pNext->pNext = tmp2;
                        return ;

                }
                else{
                        tmp=tmp->pNext;
                }
        }
        tmp->pNext = (pLink)malloc(sizeof(struct Link));
        tmp->pNext->pNext = NULL;
        tmp->pNext->coef = _coef;
        tmp->pNext->exp = _exp;
}
void Travel(Poly p)
{
        Poly tmp = p->pNext;
        printf("\n\n");
        if(tmp==NULL){
                printf("0\n");
                return ;
        }

        while(tmp!=NULL){
                if(tmp==p->pNext)printf("%d %d\n",  tmp->coef,tmp->exp);
                else printf("%d %d\n",  tmp->coef,tmp->exp);
                tmp = tmp->pNext;
        }
        printf("\n");
}
void InputData(Poly p,int n)
{
        int i=0;
        int _coef=0, _exp=0;
        for(i=0; i<n; i++){
                scanf("%d%d",&_coef,&_exp);
                AddData(p, _coef, _exp );

        }
}
void LinkAdd(Poly A, Poly B, Poly C)
{
        Poly tmpA = A->pNext;
        Poly tmpB = B->pNext;

        while(tmpA!=NULL) AddData(C, tmpA->coef, tmpA->exp), tmpA=tmpA->pNext;
        while(tmpB!=NULL) AddData(C, tmpB->coef, tmpB->exp), tmpB=tmpB->pNext;
}
void LinkMul(Poly A, Poly B, Poly C)
{
        Poly tmpA = A->pNext;
        Poly tmpB = B->pNext;

        while(tmpA!=NULL){
                tmpB = B->pNext;

                while(tmpB!=NULL){
                        AddData(C, tmpA->coef * tmpB->coef,        tmpA->exp + tmpB->exp);
                        tmpB = tmpB ->pNext;
                }
                tmpA = tmpA->pNext;
        }
}
void RemoveCoefZero(Poly p)
{
        Poly pre = p;
        Poly cur = p->pNext;

        while(cur!=NULL){
                if(cur->coef==0) {
                        pre->pNext = cur->pNext;
                        free(cur);
                        cur = pre->pNext;
                        continue;
                }
                pre = cur;
                cur = cur->pNext;
        }
}

void ReleaseLink(Poly p)
{
        Poly tmp = p->pNext;
        while(tmp!=NULL){
                p->pNext = tmp->pNext;
                free(tmp);
                tmp = p->pNext;
        }
        free(p);
}
