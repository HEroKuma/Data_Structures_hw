#include <stdio.h>
unsigned long long int num = 0;
int ackerman(int m,int n)
{
  num++;
  if (m == 0) return(n + 1);
  if (m > 0 && n == 0) return(ackerman(m - 1,1));
  return(ackerman(m - 1,ackerman(m,n - 1)));
}
int main()
{
  int m,n;
  printf("enter m and n:");
  while(scanf("%d %d",&m,&n) != EOF){
    printf("A(%d,%d)=%d\n",m,n,ackerman(m,n));
    printf("enter m and n:");
    printf("%d\n",num);
    num = 0;
  }
  return 0;
}
