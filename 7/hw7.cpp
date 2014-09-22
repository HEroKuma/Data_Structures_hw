#include<iostream>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<stdio.h>
#include<vector>
#include<cstring>
#include<map>
#include<fstream>
#define MAX 300

using namespace std;

struct MyNode{
    string x;
    int s;
    unsigned char index;
    struct MyNode *l;
    struct MyNode *r;
};
typedef struct MyNode node;

struct Map{
  bool istrue;
  string C;
  string I;
  int len;
};
typedef struct Map Map;


Map Find[MAX];

bool cmp(node N,node M)
{
  if(N.s != M.s) return N.s > M.s;
  else return N.index > M.index;
}

void travel(node* ptr)
{
  if(ptr != NULL){
    free(ptr);
    //cout << ptr->x << ":" << ptr->s << endl;
    travel(ptr->l);
    travel(ptr->r);
  }
}

void trace(node *ptr)
{
  if(ptr != NULL){
    if(ptr -> l)
      ptr -> l -> x = ptr -> x + '0';
    if(ptr -> r)
      ptr -> r -> x = ptr -> x + '1';
    trace(ptr -> l);
    if(ptr -> r == NULL && ptr -> l == NULL){
      //cout << ptr -> index << " : " << ptr->x << endl;
      int temp;
      temp = ptr->index;
      Find[temp].C = ptr -> index;
      Find[temp].I = ptr -> x;
      Find[temp].istrue = true;
    }
    trace(ptr -> r);
  }
}

int main()
{
  FILE *p1;
  FILE *p2;
  FILE *trueFile;
  int length = 0;

  node *rootptr;
  node Set[MAX];
  char inputFile[200];
  vector<node> tree_node;
  vector<node>::iterator it;
  int num_of_char = 0;

  for(int i = 0 ;i < MAX; i++){
    Set[i].index = i;
    Set[i].s = 0;
    Set[i].l = NULL;
    Set[i].r = NULL;
    Find[i].istrue = false;
  }
  unsigned char c;
  trueFile = fopen("first.txt","rwb+");
  scanf("%s",inputFile);
  p1 = fopen(inputFile,"rwb+");
  while(fscanf(p1,"%c",&c) != EOF){
    fprintf(trueFile,"%c",c);
  }
  fclose(trueFile);
  fclose(p1);
  trueFile = fopen("first.txt","rwb+");
  while(fscanf(trueFile,"%c",&c) != EOF){
    printf("%c",c);
    Set[c].s++;
    length++;
    //fprintf(trueFile,"%c",c);
  }
  fclose(trueFile);
cout << "read file successful" << endl;
  sort(Set,Set+MAX,cmp);
cout << "sort successful" << endl;
  for(int i = 0 ;i < MAX; i++)
    if(Set[i].s){
        num_of_char++;
    }

  node build_tree[num_of_char];
  node tree[num_of_char];

  int con = 0;

  for(int i = 0 ;i < num_of_char; i++){
    if(Set[i].s){
        build_tree[con].index = Set[i].index;
        build_tree[con].s = Set[i].s;
        tree[con].index = Set[i].index;
        tree[con].s = Set[i].s;
        con++;
    }
  }

  for(int i = 0 ;i < num_of_char; i++){
    tree_node.push_back(Set[i]);
    //cout << Set[i].index << " " << Set[i].s << endl;
  }
cout << "index create successful" << endl;

  int n = num_of_char;
  int num_of_char2 = num_of_char;

  while(!tree_node.empty()){
    node *root = new node;
    node *n1 = new node;
    node *n2 = new node;
    *n1 = tree_node.back();
    tree_node.pop_back();
    *n2 = tree_node.back();
    tree_node.pop_back();
    root -> l = n1;
    root -> r = n2;
    root -> index = n2 -> index;
    root -> s = n1->s + n2 -> s;
    if(root -> s == length)
        rootptr = root;
    else
        tree_node.push_back(*root);
    sort(tree_node.begin(),tree_node.end(),cmp);
  }
cout << "build tree successful" << endl;
  //travel(rootptr);

  //cout << "=====¤À¹j²Å=======" <<endl;
  trace(rootptr);

  /*for(int i = 0 ;i < MAX; i++){
    if(Find[i].C[0])
        cout << Find[i].C << " " << Find[i].I << endl ;
  }*/

  p1 = fopen("file.txt","rwb+");
  p2 = fopen("out.txt","rwb+");
  while(fscanf(p1,"%c",&c) != EOF){
        fprintf(p2,"%s",Find[c].I.c_str());
        //printf("%s",Find[c].I.c_str());
  }
cout << "num of index insert successful" << endl;
  //printf("\n");
  fclose(p2);
  FILE *p3;
  p2 = fopen("out.txt","rwb+");

  string temp = "";
  char f1[MAX];
  char f2[MAX];
  char ttemp;
  unsigned char Final[8];

  p3 = fopen("header.hfm","rwb+");
  int num_of_head = 0;

  for(int i = 0 ;i < MAX; i++)
    if(Find[i].istrue) num_of_head++;
  fprintf(p3,"%d\n",num_of_head);

  int total_length = 0;
  while(fscanf(p2,"%c",&ttemp) != EOF) total_length++;
  fprintf(p3,"%d\n",total_length);

  for(int i = 0 ;i < MAX; i++){
    if(Find[i].istrue) fprintf(p3,"%s\n%s\n",Find[i].C.c_str(),Find[i].I.c_str());
  }
  fclose(p2);
  p2 = fopen("out.txt","rwb+");
  while(fscanf(p2,"%c",&ttemp) != EOF){
    total_length++;
    temp += ttemp;
    while(temp.length() > 7){
      for(int i = 0 ; i < 8; i++){
        if(temp[i] == '1') Final[i] = 1;
        else Final[i] = 0;
      }
      fprintf(p3,"%c",(Final[0]<<7)|(Final[1]<<6)|(Final[2]<<5)|(Final[3]<<4)|(Final[4]<<3)|(Final[5]<<2)|(Final[6]<<1)|(Final[7]));
      temp.erase(0,8);
    }
  }
  int ii;
  if(temp.length() > 0){
    for(ii = 0 ;ii < temp.length(); ii++){
        if(temp[ii] == '1') Final[ii] = 1;
        else Final[ii] = 0;
    }
    for(;ii<8;ii++){
        Final[ii] = 0;
    }
    fprintf(p3,"%c",(Final[0]<<7)|(Final[1]<<6)|(Final[2]<<5)|(Final[3]<<4)|(Final[4]<<3)|(Final[5]<<2)|(Final[6]<<1)|(Final[7]));
  }
  fclose(p1);
  fclose(p2);
  fclose(p3);
cout << "header create successful" << endl;
  travel(rootptr);
cout << "tree delete successful" << endl;
//===================================================
  cout << "¡ô--------¡õ" << endl;
  p3 = fopen("header.hfm","rwb+");
  int head_num,length_num;
  fscanf(p3,"%d",&head_num);
  fscanf(p3,"%d",&length_num);
  cout << head_num << endl;
  Map found[head_num];
  cout << length_num << endl;
  int search_num = head_num;
  while(head_num--){
    fscanf(p3,"%s %s",f1,f2);
    found[head_num].C = f1;
    found[head_num].I = f2;
    found[head_num].len = found[head_num].I.length();
    cout << found[head_num].C << ":" << found[head_num].I << ":" << found[head_num].len << endl;
  }
  cout << endl << "List create success" << endl;
  cout << endl;

  unsigned char cc;
  fscanf(p3,"%c",&cc);
  FILE *p4;
  p4 = fopen("final.txt","rwb+");
  int cont_length = 0;
  while(fscanf(p3,"%c",&cc) != EOF){
    //printf("%c",cc);
    if(cont_length < length_num){
      int base[8] = {128,64,32,16,8,4,2,1};
      for(int i = 0 ;i < 8; i++){
          if((int)cc/base[i]==1 && cont_length < length_num){
            cont_length++;
            //cout << '1';
            fprintf(p4,"1");
          }
          else if(cont_length < length_num){
            cont_length++;
            //cout << '0';
            fprintf(p4,"0");
          }
          cc%=base[i];
      }
      //cout << endl;
    }
  }
  cout << endl << "binary index create success" << endl;
  fclose(p4);
  p4 = fopen("final.txt","rwb+");
  FILE *p5;
  p5 = fopen("ReallyFinal.txt","rwb+");
  string final_index = "";
  string index_temp;
  unsigned char xx[1];
  while(fscanf(p4,"%c",&xx[0]) != EOF){
    index_temp = xx[0];
    final_index += index_temp;
    for(int i = 0 ;i < search_num; i++){
        if(final_index == found[i].I){
          /*unsigned char OAO[found[i].len];
          char QAQ;
          for(int j = 0 ;j < found[i].len; j++){
            QAQ = found[i].I[j];
          }*/
          fprintf(p5,"%c",found[i].C[0]);
          final_index.erase(0,found[i].I.length());
        }
    }
  }
  cout << endl << "Finally" << endl;
  fclose(p5);
  cout << endl;
  fclose(p3);

  return 0;
}
