#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

int main()
{
  int n,i,j,num,con;

  while(std::cin >> n){

    int sq[n][n];             //�Ыؤ@�ӤG���}�C�s���G
    memset(sq,0,sizeof(sq));  //�����k�s
    num = 1;i = n/2;j = n-1;  //�H�̥k��̤��C�����}�Y�}�l��

   while(num <= n*n){
      if(i == -1 && j == n){j = n-2;i = 0;} //�W�X�}�C��ɮɭn���B�z
      else {
        if(j == n) j = 0;  //�@�ˬO��ɳB�z
        if(i < 0) i = n-1; //�P�W
      }
    if(sq[i][j]){j--;j--;i++;continue;} //���F�誺�ܴN�����w����m����
    else
      sq[i][j]=num++;  //�S�F�誺�ܶ뺡�L
      j++,i--;         //�맹�᩹�k�W�貾��
    }
  for(i = 0 ;i < n; i++){               //�L�X��!!
    for(j = 0,num = 0; j < n; j++){
      printf("%2d ",sq[i][j]);
      num+=sq[i][j];
    }
    printf("\n");
  }
  }
  return 0;
}
