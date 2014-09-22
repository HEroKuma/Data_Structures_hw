#include<stdio.h>
#include<stdlib.h>
unsigned int *HuT;
char *WT;
typedef struct node *ptr;
struct node{
   char w;
   float rate;
   ptr left,right;
};

void inorder(ptr tree,int *index,unsigned int addr){
   if(tree->left==NULL){
      HuT[*index]=addr;
      WT[*index]=tree->w;
      (*index)++;
   }
   else{
      inorder(tree->left,index,addr<<1);
      inorder(tree->right,index,(addr<<1)+1);
   }
}
int main(){
   int n,i,j,k,index=0;
   ptr *List,temp;
   char bc[33];

   printf("請輸入資料個數>");
   scanf("%d",&n);

   //動態產生Table & list(queue);
   List=(ptr*)malloc(sizeof(ptr)*n);
   HuT=(unsigned int*)malloc(sizeof(unsigned int)*n);
   WT=(char*)malloc(sizeof(char)*n);

   //儲存資料
   for(i=0;i<n;i++){
      List[i]=(ptr)malloc(sizeof(struct node));
      scanf(" %c",&(List[i]->w));
      scanf(" %f",&(List[i]->rate));
      List[i]->left=List[i]->right=NULL;
   }

   //建立Huffman tree
   printf("Building...\n");
   k=n;
   while(--k>0){
      //選出兩個最小的
      for(i=0;i<2;i++){
         for(j=0;j<k-i;j++){
            if(List[j]->rate<List[k-i]->rate){
               temp=List[j];
               List[j]=List[k-i];
               List[k-i]=temp;
            }
         }
      }
      //合併 (產生新節點，設定rate，並建立為子樹，再加入list)
      temp=(ptr)malloc(sizeof(struct node));
      temp->rate=List[k]->rate+List[k-1]->rate;
      temp->left=List[k];
      temp->right=List[k-1];
      List[k-1]=temp;
   }
   //轉換到表格上
   inorder(List[0],&index,1);
   printf("Huffman code table\n");
   for(i=0;i<n;i++){
      for(j=0;(HuT[i]>>j)>0;j++);
      for(bc[--j]='\0',--j;j>=0;j--){
         bc[j]=(HuT[i]&1)+48;
         HuT[i]>>=1;
      }
      printf("%c %s\n",WT[i],bc);
   }
   return 0;
}
