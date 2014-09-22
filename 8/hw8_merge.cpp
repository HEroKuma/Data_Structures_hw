#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;

void Merge(int,int,int[],int[]);
void mergeSort(int,int,int[],int[]);

int main()
{
    FILE *p;
    int Size;
    clock_t Start,End;
    float total;

    p = fopen("testdata_500000_1.txt","r");

    fscanf(p,"%d",&Size);

    int data[Size];
    int tmp[Size];

    for(int i = 0 ;i < Size; i++){
        fscanf(p,"%d",&data[i]);
    }

    Start = clock();
    mergeSort(0,Size,tmp,data);
    End = clock();

    /*
    for(int i = 0 ;i < Size; i++){
        cout << data[i] << " ";
    }
    */
    total = (float)(End - Start)/CLOCKS_PER_SEC;
    cout << "you spend " << total << "sec." << endl;

	return 0;
}

void Merge(int left,int right,int tmp[],int num[])
{
    int i,j,k;
    int mid = (left + right) / 2;

    for (k = 0,i = left,j = mid+1;i <= mid || j <= right; k++)
    {
        if (i > mid)
            tmp[k] = num[j++];
        else if (j > right)
            tmp[k] = num[i++];
        else if (num[i] < num[j])
            tmp[k] = num[i++];
        else
            tmp[k] = num[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++)
        num[i] = tmp[k];
}

void mergeSort(int left, int right,int tmp[],int num[])
{
    int mid = (left + right) / 2;

    if (left < right)
    {
        mergeSort(left, mid,tmp,num);
        mergeSort(mid+1, right,tmp,num);
        Merge(left,right,tmp,num);
    }
}
