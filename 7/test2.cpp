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

   printf("�п�J��ƭӼ�>");
   scanf("%d",&n);

   //�ʺA����Table & list(queue);
   List=(ptr*)malloc(sizeof(ptr)*n);
   HuT=(unsigned int*)malloc(sizeof(unsigned int)*n);
   WT=(char*)malloc(sizeof(char)*n);

   //�x�s���
   for(i=0;i<n;i++){
      List[i]=(ptr)malloc(sizeof(struct node));
      scanf(" %c",&(List[i]->w));
      scanf(" %f",&(List[i]->rate));
      List[i]->left=List[i]->right=NULL;
   }

   //�إ�Huffman tree
   printf("Building...\n");
   k=n;
   while(--k>0){
      //��X��ӳ̤p��
      for(i=0;i<2;i++){
         for(j=0;j<k-i;j++){
            if(List[j]->rate<List[k-i]->rate){
               temp=List[j];
               List[j]=List[k-i];
               List[k-i]=temp;
            }
         }
      }
      //�X�� (���ͷs�`�I�A�]�wrate�A�ëإ߬��l��A�A�[�Jlist)
      temp=(ptr)malloc(sizeof(struct node));
      temp->rate=List[k]->rate+List[k-1]->rate;
      temp->left=List[k];
      temp->right=List[k-1];
      List[k-1]=temp;
   }
   //�ഫ����W
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
