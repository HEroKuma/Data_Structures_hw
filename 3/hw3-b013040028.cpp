#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>

int ChessBoard[8][8];

bool Travel(int FirstX,int FirstY,int Size)
{
  int next_x[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
  int next_y[8] = {1, 2, 2, 1, -1, -2, -2, -1};

  ChessBoard[FirstX][FirstY] = 1;
  int NextX = FirstX;
  int NextY = FirstY;
  int nextstep_x[8] = {0};
  int nextstep_y[8] = {0};
  int exit[8] = {0};

  for(int m = 2 ;m < Size*Size+1; m++){
    for(int i = 0 ;i < 8; i++)
      exit[i] = 0;
      int count = 0;
      for(int i = 0 ;i < 8; i++){
        int tmp_i = NextX + next_x[i];
        int tmp_j = NextY + next_y[i];
        if(tmp_i < 0 || tmp_i > (Size-1) || tmp_j < 0 || tmp_j > (Size-1)){
          continue;
        } 
        if(0 == ChessBoard[tmp_i][tmp_j]){
  	  nextstep_x[count] = tmp_i;
  	  nextstep_y[count] = tmp_j;
	  count++;
        }
      }
    int min = 0;
    if(count < 1){
      return false;
    }
    if(1 == count){
      min = 0;
    } 
    else{
      for(int i = 0 ;i < count; i++){
        for(int j = 0 ;j < 8; j++){
       	  int tmp_i = nextstep_x[i] + next_x[j];
	  int tmp_j = nextstep_y[i] + next_y[j];
	  if(tmp_i < 0 || tmp_i > (Size-1) || tmp_j < 0 || tmp_j > (Size-1)){
	    continue;
	  } 
	  if(0 == ChessBoard[tmp_i][tmp_j]){
	    exit[i]++;
	  }
        }
      }
    int tmp = exit[0];
    min = 0;
    for(int i = 1 ;i < count; i++){
      if(tmp > exit[i]){
        tmp = exit[i];
        min = i;
      }
    }
    }
    NextX = nextstep_x[min];
    NextY = nextstep_y[min];
    ChessBoard[NextX][NextY] = m;
  }
  return true;
}

int main()
{
  int startx = 0, starty = 0;
  int i,j;
  int start;
  for(start = 1 ;start <= 6; start++){
    printf("State: %d\n",start);
    memset(ChessBoard,0,sizeof(ChessBoard));
    if(Travel(startx,starty,start)){
      printf("Complete\n");
      for(i = 0 ;i < start; i++){
        for(j = 0 ;j < start; j++){
          if(ChessBoard[i][j]) printf("%2d ",ChessBoard[i][j]);
        }
        printf("\n");
      }
    }
    else{
      printf("Fail\n");
    }
    printf("\n");
  }
  return 0;
}  
  
