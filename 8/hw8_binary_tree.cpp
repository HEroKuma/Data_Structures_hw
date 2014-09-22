#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

struct node
{
    struct node *left;
    struct node *right;
    int data;
};
void Insert(struct node**,int);
void inorder(struct node*);

int main()
{
    FILE *p;
    int Size;
    struct node *bt;
    clock_t Start,End;
    float total;

    p = fopen("testdata_500000_4.txt","r");

    fscanf(p,"%d",&Size);

    int data[Size];
    Start = clock();
    for(int i = 0 ;i < Size; i++){
        fscanf(p,"%d",&data[i]);
        Insert(&bt,data[i]);
        //cout << data[i] << " ";
    }
    //inorder(bt);

    End = clock();
    total = (float)(End - Start)/CLOCKS_PER_SEC;
    cout << "you spend " << total << "sec." << endl;

	return 0;
}

void Insert(struct node **sr,int num)
{
    if(*sr == NULL)
    {
        *sr = (struct node*)malloc(sizeof(struct node));

        (*sr) -> left = NULL;
        (*sr) -> right = NULL;
        (*sr) -> data = num;
    }
    else
    {
        if(num < (*sr) -> data)
            Insert(&((*sr)->left),num);
        else
            Insert(&((*sr)->right),num);
    }
}

void inorder(struct node *sr)
{
    if(sr != NULL)
    {
        inorder(sr -> left);
        cout << sr->data << " ";
        inorder(sr -> right);
    }
}
