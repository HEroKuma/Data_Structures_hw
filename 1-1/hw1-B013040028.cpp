#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

int main()
{
  int n,i,j,num,con;

  while(std::cin >> n){

    int sq[n][n];             //創建一個二維陣列存結果
    memset(sq,0,sizeof(sq));  //全員歸零
    num = 1;i = n/2;j = n-1;  //以最右行最中列的為開頭開始填

   while(num <= n*n){
      if(i == -1 && j == n){j = n-2;i = 0;} //超出陣列邊界時要做處理
      else {
        if(j == n) j = 0;  //一樣是邊界處理
        if(i < 0) i = n-1; //同上
      }
    if(sq[i][j]){j--;j--;i++;continue;} //有東西的話就往指定的位置移動
    else
      sq[i][j]=num++;  //沒東西的話塞滿他
      j++,i--;         //塞完後往右上方移動
    }
  for(i = 0 ;i < n; i++){               //印出來!!
    for(j = 0,num = 0; j < n; j++){
      printf("%2d ",sq[i][j]);
      num+=sq[i][j];
    }
    printf("\n");
  }
  }
  return 0;
}
