/*========================
學號:B013040028
姓名:張力偉
目的:學會二元搜尋樹
=========================*/
#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode
{
    int data;
    struct treeNode *left;
    struct treeNode *right;

}treeNode;

treeNode* FindMin(treeNode*);
treeNode * Insert(treeNode*,int);
treeNode * Delete(treeNode*,int);
treeNode * Find(treeNode*,int);
void PrintPreorder(treeNode*);
void PrintPreorderLeftLeaf(treeNode*);
void PrintPreorderRightLeaf(treeNode*);

int main()
{
    int data;
    treeNode *root = NULL;
    treeNode *temp;
    while(scanf("%d",&data)){
        if(data == -1){
            printf("  ans:");
            PrintPreorder(root);
            printf("\n");
            while(root != NULL){
                root = Delete(root,root->data);
            }
            PrintPreorder(root);
            return 0;
        }
        temp = Find(root,data);
        if(temp == NULL){
            root = Insert(root,data);
        }
        else{
            root = Delete(root,data);
        }
        printf(" node: ");
        PrintPreorder(root);
        printf("\n");
        printf(" left: ");
        PrintPreorderLeftLeaf(root);
        printf("\n");
        printf("right: ");
        PrintPreorderRightLeaf(root);
        printf("\n");
    }
}

treeNode* FindMin(treeNode *node)
{
    if(node==NULL){
        return NULL;
    }
    if(node->left)
        return FindMin(node->left);
    else
        return node;
}

treeNode * Insert(treeNode *node,int data)
{
    if(node==NULL){
        treeNode *temp;
        temp = (treeNode *)malloc(sizeof(treeNode));
        temp -> data = data;
        temp -> left = temp -> right = NULL;
        return temp;
    }

    if(data >(node->data)){
        node->right = Insert(node->right,data);
    }
    else if(data < (node->data)){
        node->left = Insert(node->left,data);
    }
    return node;

}

treeNode * Delete(treeNode *node, int data)
{
    treeNode *temp;
    if(node==NULL){
        printf("Element Not Found");
    }
    else if(data < node->data){
        node->left = Delete(node->left, data);
    }
    else if(data > node->data){
        node->right = Delete(node->right, data);
    }
    else{
        if(node->right && node->left){
            temp = FindMin(node->right);
            node -> data = temp->data;
            node -> right = Delete(node->right,temp->data);
        }
        else{
            temp = node;
            if(node->left == NULL)
                    node = node->right;
            else if(node->right == NULL)
                    node = node->left;
            free(temp);
        }
    }
    return node;
}

treeNode * Find(treeNode *node, int data)
{
    if(node==NULL){
        return NULL;
    }
    if(data > node->data){
        return Find(node->right,data);
    }
    else if(data < node->data){
        return Find(node->left,data);
    }
    else{
        return node;
    }
}

void PrintPreorder(treeNode *node)
{
    if(node==NULL){
        return;
    }
    printf("%3d",node->data);
    PrintPreorder(node->left);
    PrintPreorder(node->right);
}

void PrintPreorderLeftLeaf(treeNode *node)
{
    if(node==NULL){
        return;
    }
    if(node -> left == NULL)
        printf(" -1");
    else
        printf("%3d",node->left->data);
    PrintPreorderLeftLeaf(node->left);
    PrintPreorderLeftLeaf(node->right);
}

void PrintPreorderRightLeaf(treeNode *node)
{
    if(node==NULL){
        return;
    }
    if(node -> right == NULL)
        printf(" -1");
    else
        printf("%3d",node->right->data);
    PrintPreorderRightLeaf(node->left);
    PrintPreorderRightLeaf(node->right);
}
