#include<cstdlib>    //����:������B013040028
#include<iostream>   //����:2013/9/23
#include<string.h>   //��;:���δ��\�㭼

using namespace std;

int main()
{
  int i,j;
  int A[50][70]; //����һ������Á탦��Y��
    memset(A,0,sizeof(A)); //ȫ�T�w��
    A[0][0] = 1;

for(i = 1 ;i < 50; i++){       //�ĵڶ����_ʼ,ÿ���e��Ĕ�����ȥ����һ��Ĕ���
    for(j = 0 ;j < 70; j++){
        A[i][j] = A[i-1][j]*(i+1);
    }
    for(j = 0 ;j < 70; j++){
        A[i][j+1] += A[i][j] / 10;
        A[i][j] %= 10;
    }
}

  int n; //Ҫӡ�����A�˵�����

  while(cin >> n && n){
    for(i = 0 ;i < n; i++){
        cout << i+1 << "!=";
        int s = 70-1;  //array��0~69��70��
        while(A[i][s] == 0) s--;  //�ҵ��������Ԫ��
        while(s >= 0) cout << A[i][s--];  //�_ʼӡ����
        cout << endl;
    }
    cout << endl;
  }

  return 0;
}
