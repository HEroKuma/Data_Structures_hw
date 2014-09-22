#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<string>

using namespace std;

struct node
{
    struct node *left;
    struct node *right;
    int data;
};

void Insert_Binary_Tree(struct node**,int);
void inorder(struct node*);
void selection_sort(int[],int);
void Merge(int[],int,int);
void mergeSort(int[],int);

FILE *output;

int main()
{
	FILE *p;
	int Size;
	struct node *bt;
    bt = NULL;
	p = fopen("input.txt","r");

	fscanf(p,"%d",&Size);

	int *Sele;
	int *Tree;
	int *mergeA;

	Sele = (int*)malloc(sizeof(int)*Size);
	Tree = (int*)malloc(sizeof(int)*Size);
	mergeA = (int*)malloc(sizeof(int)*Size);

	for(int i = 0 ;i < Size; i++){
		fscanf(p,"%d",&Sele[i]);
		Tree[i] = Sele[i];
		mergeA[i] = Sele[i];
	}

	selection_sort(Sele,Size); // a
	output = fopen("outputA.txt","w");
	fprintf(output,"Selection Sort\n");
	for(int i = 0 ;i < Size; i++){
		fprintf(output,"%d\n",Sele[i]);
	}
	fclose(output);
	for(int i = 0 ;i < Size; i++){ //b
		Insert_Binary_Tree(&bt,Tree[i]);
	}
	output = fopen("outputB.txt","w");
	fprintf(output,"Binary Tree Sort\n");
	inorder(bt);
	fclose(output);

	mergeSort(mergeA,Size);//c
	output = fopen("outputC.txt","w");
	fprintf(output,"Merge Sort\n");
	for(int i = 0 ;i < Size; i++){
		fprintf(output,"%d\n",mergeA[i]);
	}
	fclose(output);



	free(Sele);
	free(Tree);
	free(mergeA);
	fclose(p);

	return 0;
}

void selection_sort(int tag[],int MAX)
{
	 int position,temp;
	 for (int c = 0 ; c < ( MAX - 1 ) ; c++ ){
		position = c;
		for (int d = c + 1 ; d < MAX ; d++ ){
			if ( tag[position] > tag[d] )
			position = d;
		}
		if ( position != c ){
			temp = tag[c];
			tag[c] = tag[position];
			tag[position] = temp;
		}
	}
}

void Insert_Binary_Tree(struct node **sr,int num)
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
            Insert_Binary_Tree(&((*sr)->left),num);
        else
            Insert_Binary_Tree(&((*sr)->right),num);
    }
}

void inorder(struct node *sr)
{
    if(sr != NULL)
    {
        inorder(sr -> left);
	fprintf(output,"%d\n",sr->data);
        inorder(sr -> right);
    }
}

void Merge(int *arr, int size1, int size2) {
    int temp[size1+size2];
    int ptr1=0, ptr2=0;

    while (ptr1+ptr2 < size1+size2) {
        if (ptr1 < size1 && arr[ptr1] <= arr[size1+ptr2] || ptr1 < size1 && ptr2 >= size2)
            temp[ptr1+ptr2] = arr[ptr1++];

        if (ptr2 < size2 && arr[size1+ptr2] < arr[ptr1] || ptr2 < size2 && ptr1 >= size1)
            temp[ptr1+ptr2] = arr[size1+ptr2++];
    }

    for (int i=0; i < size1+size2; i++)
        arr[i] = temp[i];
}

void mergeSort(int *arr, int Size) {
    if (Size == 1)
        return;

    int size1 = Size/2, size2 = Size-size1;
    mergeSort(arr, size1);
    mergeSort(arr+size1, size2);
    Merge(arr, size1, size2);
}
