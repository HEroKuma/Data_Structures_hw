#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>

/*------------------------------
  姓名：張力偉 B013040028
  撰寫日期:2013/10/31
  用途：歧視走棋盤遞迴版
------------------------------*/

int ChessBoard[6][6];
int next_x[8] = {-2, -1, 1, 2,  2,  1, -1, -2};
int next_y[8] = { 1,  2, 2, 1, -1, -2, -2, -1};

bool bfs(int x,int y,int step,int size)
{
  int i;
  int nx,ny;
  if(step == (size*size)){
    ChessBoard[x][y] = step;
    return 1;
  }
  ChessBoard[x][y] = step;
  for(i = 0 ;i < 8; i++){
    nx = x + next_x[i];
    ny = y + next_y[i];
    if((nx >= 0 && nx < size) && (ny >= 0 && ny < size) && ChessBoard[nx][ny] == 0 && step < (size*size)){
      if(bfs(nx,ny,step+1,size)){
        return 1;
      }
    }
  }
  ChessBoard[x][y] = 0;
  return 0;
}

int main()
{
  int i,j,step;
  int start;
  for(start = 1 ;start <= 6; start++){
    int startx = 0, starty = 0;
    step = 1;
    printf("State: %d\n",start);
    memset(ChessBoard,0,sizeof(ChessBoard));
    ChessBoard[0][0] = 1;
    if(bfs(startx,starty,step,start)){
      printf("Success!!\n");
      for(i = 0 ;i < start; i++){
        for(j = 0 ;j < start; j++){
          printf("%3d",ChessBoard[i][j]);
         }
        printf("\n");
      }
      printf("\n");
    }
    else{
      printf("Fail!!\n\n");
    }
  }
  return 0;
}  
  
