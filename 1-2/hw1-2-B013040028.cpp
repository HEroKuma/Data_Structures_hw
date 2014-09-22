#include<cstdlib>    //姓名:張力偉B013040028
#include<iostream>   //日期:2013/9/23
#include<string.h>   //用途:簡單大數運算

using namespace std;

int main()
{
  int i,j;
  int A[50][70]; //創建一個陣列用來儲存結果
    memset(A,0,sizeof(A)); //全員歸零
    A[0][0] = 1;

for(i = 1 ;i < 50; i++){       //從第二行開始,每格裡面的數字拿去乘上一格的數字
    for(j = 0 ;j < 70; j++){
        A[i][j] = A[i-1][j]*(i+1);
    }
    for(j = 0 ;j < 70; j++){
        A[i][j+1] += A[i][j] / 10;
        A[i][j] %= 10;
    }
}

  int n; //要印出的階乘到多少

  while(cin >> n && n){
    for(i = 0 ;i < n; i++){
        cout << i+1 << "!=";
        int s = 70-1;  //array有0~69共70格
        while(A[i][s] == 0) s--;  //找到不為零的元素
        while(s >= 0) cout << A[i][s--];  //開始印出來
        cout << endl;
    }
    cout << endl;
  }

  return 0;
}
