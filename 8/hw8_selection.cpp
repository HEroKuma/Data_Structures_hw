#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;

void selection_sort(int[],int);

int main()
{
    FILE *p;
    int Size;
    clock_t Start,End;
    float total;

    p = fopen("testdata_500000_8.txt","r");

    fscanf(p,"%d",&Size);

    int data[Size];

    for(int i = 0 ;i < Size; i++){
        fscanf(p,"%d",&data[i]);
        //cout << data[i] << " ";
    }
    Start = clock();
    selection_sort(data,Size);
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
