#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>



typedef struct BSTNode
{
    char data[30];
    struct BSTNode *left,*right;
} BSTNode;


BSTNode memory[5]= {NULL};



BSTNode *CreateNode(char* d)
{
    BSTNode *temp=(BSTNode*)malloc(sizeof(BSTNode));
    strcpy(temp->data,d);
    temp->left=NULL;
    temp->right=NULL;
    return temp;

}

int Max(int x, int y)
{
    return (x>=y)? x:y;
}


int CountSize(BSTNode *root)
{
    return (root==NULL) ? 0 : 1+CountSize(root->left)+CountSize(root->right);
}


int CountHeight(BSTNode *root)
{

    return (root==NULL)? -1: 1+ Max(CountHeight(root->left),CountHeight(root->right));
}

void Insert(BSTNode** root,char *d)
{

    if((*root)==NULL)
        (*root)=CreateNode(d);

    else if(strcmp(d,(*root)->data)>0)
        Insert(&(*root)->right,d);

    else if(strcmp(d,(*root)->data)<0)
        Insert(&(*root)->left,d);

}


void Print(BSTNode *root)
{

    if(root!=NULL)
    {
        printf("%s\n",root->data);
        Print(root->left);
        Print(root->right);
    }
}

int isLeaf(BSTNode* root)
{
    return root->left==NULL & root->right==NULL;
}





BSTNode* LoadWords(char* fileName)
{
    BSTNode* root;
    char *temp=(char*)malloc(sizeof(char)*20);
    int flag=0;


    FILE *p=fopen(fileName,"r");

    if(p==NULL)
    {
        printf("Error Loading File\n");
        exit(0);
    }


    while(!feof(p))
    {
        fscanf(p,"%s",*&temp);

        if (flag==0)
        {
            root=CreateNode(temp);
            flag=1;
        }

        else
            Insert(&root,temp);

    }

    printf("File Loaded...\n");
    printf("--------------------------------\n");

    return root;


}

BSTNode* MaxNode(BSTNode* root)
{

    while(root->right!=NULL)
        root=root->right;
    return root;
}

BSTNode* MinNode(BSTNode* root)
{

    while(root->left!=NULL)
        root=root->left;
    return root;
}



void SearchBST(BSTNode* root,char *d)
{
    if(root==NULL)
    {
        BSTNode *temp=(memory+3);
         //Successor
    if(temp->right!=NULL)
     memory[2]=*MinNode(temp->right);

        //predecessor
   if(temp->left!=NULL)
    memory[1]=*MaxNode(temp->left);

    return;

    }

    if(root->left==NULL||root->right==NULL)
          memory[3]=*root;//last leaf node index

    if(strcmp(d,root->data)==0)
        memory[0]=*root;//data index

    else if(strcmp(d,root->data)>0&&!isLeaf(root))
    {
            memory[1]=*root;//predecessor index
            SearchBST(root->right,d);
    }
    else if(strcmp(d,root->data)<0&&!isLeaf(root))
    {
            memory[2]=*root; //successor index
           SearchBST(root->left,d);
    }

}


//now implemented in search function
void GetSuccesorAndPredecessor()
{
    BSTNode *temp=(memory+3);
    //Successor

    if(temp->right!=NULL)
     memory[2]=*MinNode(temp->right);

    //predecessor


   if(temp->left!=NULL)
    memory[1]=*MaxNode(temp->left);

}


void CheckLine(BSTNode* root,char *line)
{
    char* token;
    char s[4]="  \n";
int i ;

    token=strtok(line,s);

    while(token!=NULL)
    {
        for(i=0;i<4;i++)
        *memory[i].data=NULL;

        SearchBST(root,token);
        if(*memory[0].data==NULL){

             //   GetSuccesorAndPredecessor();

            printf("\n%s isn't correct \n+ %s - %s - %s \n",token,memory[3].data,memory[2].data,memory[1].data);
            }

        else
            printf("\n%s  Is correct\n",token);

        token=strtok(NULL,s);

    }
    printf("\n--------------------------------");


}




int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("Error Loading File1\n");
        exit(0);
    }

    BSTNode* root=LoadWords(argv[1]);
    char* p=(char*)malloc(sizeof(char)*255);



    int x=CountHeight(root);
    printf("    **************");
    printf("\n    *  Height=%d *",x);
    x=CountSize(root);
    printf("\n    * Size=%d *\n",x);
    printf("    **************");



    printf("\n\nEnter a sentence or Press CTRl-Z to exit \n");
    while(fgets(p,255,stdin)!=NULL)
    {

        CheckLine(root,p);
        printf("\nEnter a sentence or Press CTRl-Z to exit \n");
    }












}
