#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string.h>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#define MAX 256
using namespace std;

/* node  */
struct node
{
    int tmp_tol;
    unsigned char index;
    node *left;
    node *right;
    bool isleft;
    string data;
};

class hfmzip
{
public:
    void bi_read();
    void bi_write();
    hfmzip();
    void sorting();
    void show();
    /* tree */
    void mktree();
    void trace( node *);


private:
    vector<node>vec_sort;
    char t[200];
    node table[MAX];
    int real_byte;
    unsigned char bit[8];
    /* for tree */
    node *rootptr;
    vector<string>header_table[MAX];
};

/* main */
int main( )
{
    hfmzip evil_hw7;
    evil_hw7.bi_read();
    evil_hw7.sorting();
    evil_hw7.mktree();
    evil_hw7.show();
    evil_hw7.bi_write();
}

/*  µ¹sort§PÂ_ªºfunction  */

bool to_sort( node tbi1 , node tbi2)
{
    if( tbi1.tmp_tol > tbi2.tmp_tol )
        return true;
    else if( tbi1.tmp_tol == tbi2.tmp_tol )
        return tbi1.index > tbi2.index;

    return false;
}

/* construe */
hfmzip::hfmzip()
{

    rootptr = NULL;
    real_byte = 0;
    for( int i = 0 ; i < MAX ; i++ )
    {
        table[i].index = i;
        table[i].tmp_tol = 0;
        table[i].left = NULL;
        table[i].right = NULL;
        table[i].isleft = false;
        table[i].data = "";
    }
    memset(bit,0,8);
}

/* read the file */
void hfmzip::bi_read()
{
    cin >> t;                                               // Input the file path
    unsigned char c;
    fstream fsin,fsout;
    fsin.open( t , fstream::in | fstream::binary  );

    while( fsin >> c )
    {
        table[c].tmp_tol++;
        real_byte++;
    }
}

/* write the file */
void hfmzip::bi_write()
{
    unsigned char c;
    vector<char>input;
    string aft_hfm = "";
    int hfm_byte = 0;
    fstream fsin,fsout,fscodein,fscodeout;
    fsin.open( t , fstream::in | fstream::binary  );
    fsout.open( "Q.txt" , fstream::binary | fstream::out );
    //fscodein.open( "tmp.txt"  , fstream::in | fstream::binary );
    //fscodeout.open( "Q.txt" , fstream::binary | fstream::out );
    while( fsin >> noskipws >> c )
        aft_hfm += header_table[c].front();

    string ans="";
    int counter = 0;
    char bit=0;

    for( unsigned int i = 0 ; i < aft_hfm.length() ; i++)
    {
        counter++;
        c = aft_hfm.at(i);
        if(counter < 8)
        {
            bit = bit | c;
            bit = bit << 1;
        }
        else
        {
            ans += bit;
            hfm_byte++;
            counter = 0;
            bit = 0;
        }

    }
    if(counter!=0)
    {
        hfm_byte++;
        ans += bit;
    }

    fsout << hfm_byte << "  ";

    for( unsigned int i = 0 ; i < ans.length() ; i++ )
        fsout << ans.at(i);

}

/* sort the array */
void hfmzip::sorting()
{
    for( int i = 0 ; i < MAX ; i++)
        if( table[i].tmp_tol )
            vec_sort.push_back( table[i] );

    sort( vec_sort.begin() , vec_sort.begin()+vec_sort.size() , to_sort);
}

void hfmzip::show()
{
    //printf("%d\n",real_byte);
    /*for(int i = 0 ; i < vec_sort.size() ; i++ )
    {
        cout << vec_sort[i].index << " " << vec_sort[i].tmp_tol << endl;
    }*/

    trace(rootptr);
}


/* for tree */
void hfmzip::mktree()
{
    while( !vec_sort.empty() )
    {
        /*for(int i = 0 ; i < vec_sort.size() ; i++ )
        {
            cout << vec_sort[i].index << " " << vec_sort[i].tmp_tol << endl;
        }*/

        //cout << "123XD \n";
        node *root = new node;
        node *n1 = new node;
        node *n2 = new node;
        *n1 = vec_sort.back();
        n1->isleft = true;
        vec_sort.pop_back();
        *n2 = vec_sort.back();
        vec_sort.pop_back();
        //cout << n1->tmp_tol + n2->tmp_tol << endl;
        root->left = n1;
        root->right = n2;
        root->index = n2->index;
        root->tmp_tol = n1->tmp_tol + n2->tmp_tol;
        //cout << root->tmp_tol;
        if( root->tmp_tol == real_byte)
            rootptr = root;
        else
            vec_sort.push_back( *root );

        sort( vec_sort.begin() , vec_sort.begin()+vec_sort.size() , to_sort);
    }
}

/* inorder traversal*/
void hfmzip::trace( node *tree )
{

    if( tree != NULL)
    {
        //cout << "QAQ ¦³bug \n" ;
        if(tree->left)
            tree->left->data = tree->data + "0";
        if(tree->right)
            tree->right->data = tree->data + "1";
        trace(tree->left);
        if(tree->right == NULL && tree->left == NULL)
        {
            int tmp;
            cout << tree->index << "  " << tree->tmp_tol << " " << tree->data << endl;
            tmp = tree->index;
            header_table[tmp].push_back(tree->data);
        }
        trace(tree->right);
    }
}
