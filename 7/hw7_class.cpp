/*===========================================
 *Author:張力偉(B013040028)
 *Date:2014/8/28
 *Purpose:實作霍夫曼編碼去壓縮跟解壓縮檔案
===========================================*/
#include<iostream>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<cstring>
#include<map>
#include<fstream>
#define MAX 257

using namespace std;

struct node
{
    int s;
    unsigned char Char;
    struct node *l;
    struct node *r;
    string data;
};
typedef struct node node;

map<unsigned char,string> List_for_header;
map<unsigned char,string>::iterator MapIt;

bool cmp(node,node);
void travel(node*);
void trace(node*);

int length = 0;
int num_of_char = 0;
int choose;
long long int size_for_byte;
int total_length = 0;
FILE *ReadFile;
node Set[MAX];
char InputFile_Name[200];
unsigned char c;
vector<node> tree_node;
vector<node> index;
vector<node>::iterator it;




class compress
{
public:
    void com()
    {
        cout << "Enter the trace" << endl;
        scanf("%s",InputFile_Name);
        ReadFile = fopen(InputFile_Name,"rb");
        fseek(ReadFile,0,SEEK_END);
        size_for_byte = ftell(ReadFile);
        fclose(ReadFile);
        cout << endl << "The size of your input is :" << size_for_byte << "byte." << endl;
//=====================================================
        ReadFile = fopen(InputFile_Name,"rb");
        while(fscanf(ReadFile,"%c",&c) != EOF)
        {
            Set[c].s++;
            length++;
        }
        fclose(ReadFile);
        cout << endl << "File reading successful" << endl;
//=====================================================
        sort(Set,Set+MAX,cmp);
        cout << endl << "sorting successful" << endl;
//=====================================================
        for(int i = 0 ; i < MAX; i++)
            if(Set[i].s)
            {
                num_of_char++;
            }
        for(int i = 0 ; i < num_of_char; i++)
        {
            tree_node.push_back(Set[i]);
        }
        cout << endl << "index create successful" << endl;
//=====================================================
        node *rootptr;
        if(num_of_char != 1)
        {
            while(!tree_node.empty())
            {
                node *root = new node;
                node *n1 = new node;
                node *n2 = new node;
                *n1 = tree_node.back();
                tree_node.pop_back();
                *n2 = tree_node.back();
                tree_node.pop_back();
                root -> l = n1;
                root -> r = n2;
                root -> Char = n2 -> Char;
                root -> s = n1->s + n2 -> s;
                if(root -> s == length)
                    rootptr = root;
                else
                    tree_node.push_back(*root);
                sort(tree_node.begin(),tree_node.end(),cmp);
            }
        }
        else
        {
            node *n1 = new node;
            *n1 = tree_node.back();
            tree_node.pop_back();
            rootptr = n1;
        }
        //travel(rootptr);
        cout << endl << "build tree successful" << endl;
//=====================================================
        if(size_for_byte != 0)  trace(rootptr);
        cout << endl << "map create successful" << endl;
//=====================================================
        FILE *for_header;
        ReadFile = fopen(InputFile_Name,"rb");
        for_header = fopen("2.befor_header.txt","wb");
        if(size_for_byte != 0)
        {
            while(fscanf(ReadFile,"%c",&c) != EOF)
            {
                MapIt = List_for_header.find(c);
                fprintf(for_header,"%s",MapIt->second.c_str());
                total_length += MapIt->second.length();
            }
        }
        fclose(ReadFile);
        fclose(for_header);
        cout << endl << "string create success" << endl;

//=====================================================
        unsigned char String_to_char[8];
        int temp = 0;
        ReadFile = fopen("2.befor_header.txt","rb");
        for_header = fopen("3.header.hfm","wb");
        if(size_for_byte == 0)
        {
            fprintf(for_header,"0\n0\n");
        }
        else
        {
            fprintf(for_header,"%lld\n%d\n%d\n",size_for_byte,num_of_char,total_length);
            for(MapIt = List_for_header.begin() ; MapIt != List_for_header.end(); MapIt++)
                fprintf(for_header,"%c\n%s\n",MapIt->first,MapIt->second.c_str());
            while(fscanf(ReadFile,"%c",&c) != EOF)
            {
                if(c == '1') String_to_char[temp] = 1;
                else String_to_char[temp] = 0;
                temp++;
                if(temp > 7)
                {
                    fprintf(for_header,"%c",(String_to_char[0]<<7)|(String_to_char[1]<<6)|(String_to_char[2]<<5)|(String_to_char[3]<<4)|(String_to_char[4]<<3)|(String_to_char[5]<<2)|(String_to_char[6]<<1)|(String_to_char[7]));
                    temp = 0;
                }
            }
            int filled;
            if(temp > 0)
            {
                for(filled = 0 ; filled < temp; filled++)
                {
                };
                for(; filled < 8; filled++)
                {
                    String_to_char[filled] = 0;
                }
                fprintf(for_header,"%c",(String_to_char[0]<<7)|(String_to_char[1]<<6)|(String_to_char[2]<<5)|(String_to_char[3]<<4)|(String_to_char[4]<<3)|(String_to_char[5]<<2)|(String_to_char[6]<<1)|(String_to_char[7]));
            }
        }
        fclose(ReadFile);
        fclose(for_header);
        remove("2.befor_header.txt");
        if(size_for_byte != 0) trace(rootptr);
        cout << endl << "compress successful" << endl;
    }
};
class decompress
{
public:
    int decom()
    {
        map<string,unsigned char> decompress_index;
        map<string,unsigned char>::iterator decompress_it;
        vector<node> decompress_tree;
        int decompress_char;
        int decompress_length;
        long long int hfm_byte;
        long long int decompress_size;
        unsigned char trash1,trash2;
        unsigned char decompress_charA;
        char string_temp[MAX];
        string decompress_string;
        FILE *Final;
//=====================================================
        cout << endl << endl << "Enter the trace you want decompress" << endl;
        char decompress_trace[200];
        scanf("%s",decompress_trace);
        ReadFile = fopen(decompress_trace,"rb");
        fseek(ReadFile,0,SEEK_END);
        hfm_byte = ftell(ReadFile);
        cout << "The size of decompress file is: " << hfm_byte << "byte." << endl;
        fclose(ReadFile);
//=====================================================
        ReadFile = fopen("3.header.hfm","rb");
        Final = fopen("4.befor_final.txt","wb");

        fscanf(ReadFile,"%lld%c",&decompress_size,&trash1);
        if(decompress_size == 0)
        {
            fprintf(Final,"");
            fclose(ReadFile);
            fclose(Final);
            Final = fopen("5.finally.txt","wb");
            fprintf(Final,"");
            fclose(Final);
            return 0;
        }
        fscanf(ReadFile,"%d%c",&decompress_char,&trash1);
        fscanf(ReadFile,"%d%c",&decompress_length,&trash1);
        if(decompress_char == 1)
        {
            fclose(Final);
            Final = fopen("5.finally.txt","wb");
            //printf("%d~%d",decompress_char,decompress_length);
            fscanf(ReadFile,"%c%c",&decompress_charA,&trash1);
            //printf("%c",decompress_charA);
            for(int i = 0 ; i < decompress_size; i++)
            {
                //printf("%c",decompress_charA);
                fprintf(Final,"%c",decompress_charA);
            }
            fclose(Final);
            return 0;
        }

        int temp_length = decompress_length;
        while(decompress_char--)
        {
            fscanf(ReadFile,"%c%c%s%c",&decompress_charA,&trash1,string_temp,&trash2);
            decompress_string = string_temp;
            decompress_index.insert(std::pair<string,unsigned char>(decompress_string,decompress_charA));
        }
        int cont_length = 0;
        while(fscanf(ReadFile,"%c",&c) != EOF)
        {
            if(cont_length < temp_length)
            {
                int base[8] = {128,64,32,16,8,4,2,1};
                for(int i = 0 ; i < 8; i++)
                {
                    if((int)c/base[i]==1 && cont_length < temp_length)
                    {
                        cont_length++;
                        fprintf(Final,"1");
                    }
                    else if(cont_length < temp_length)
                    {
                        cont_length++;
                        //cout << '0';
                        fprintf(Final,"0");
                    }
                    c%=base[i];
                }
            }
        }
        cout << endl << "binary index create success" << endl;
        fclose(ReadFile);
        fclose(Final);
//=====================================================
        ReadFile = fopen("4.befor_final.txt","rb");
        Final = fopen("5.finally.txt","wb");
        unsigned char char_find[1];
        string final_find = "";
        string Final_temp;
        while(fscanf(ReadFile,"%c",&char_find[0]) != EOF)
        {
            Final_temp = char_find[0];
            final_find += Final_temp;
            decompress_it = decompress_index.find(final_find);
            if(decompress_it != decompress_index.end())
            {
                fprintf(Final,"%c",decompress_it->second);
                final_find.erase(0,final_find.length());
            }
        }
        remove("4.befor_final.txt");
        fclose(ReadFile);
        fclose(Final);
        cout << endl << "final" << endl;
        if(decompress_size == 0) cout << "The compress rate is 0" << endl;
        else
        {
            cout << endl << "The compress rate is " << 100*hfm_byte/decompress_size << "%" << endl;
        }
    }
};


int main()
{

//=====================================================
    cout << "1 to compress, 2 to decompress: ";
    for(int i = 0 ; i < MAX; i++){
    Set[i].Char = i;
    Set[i].s = 0;
    Set[i].l = NULL;
    Set[i].r = NULL;
    Set[i].data = "";
}
    while(cin >> choose)
    {
        if(choose == 1){
            compress MyCompress;
            MyCompress.com();
        }

        else
        {
            decompress MyDecompress;
            MyDecompress.decom();
        }

        return 0;
    }
}

bool cmp(node N,node M){
        if(N.s != M.s) return N.s > M.s;
        else return N.Char > M.Char;
    }

void travel(node* ptr){
        if(ptr != NULL)
        {
            travel(ptr->l);
            travel(ptr->r);
            free(ptr);
        }
    }

    void trace(node *ptr)
    {
        if(ptr != NULL)
        {
            if(ptr -> l)
                ptr -> l -> data = ptr -> data + '0';
            if(ptr -> r)
                ptr -> r -> data = ptr -> data + '1';
            trace(ptr -> l);
            if(ptr -> r == NULL && ptr -> l == NULL)
            {
                List_for_header.insert(std::pair<unsigned char,string>(ptr->Char,ptr->data));
            }
            trace(ptr -> r);
        }
    }
