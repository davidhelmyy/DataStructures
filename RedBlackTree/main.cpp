#include <bits/stdc++.h>


using namespace std;


bool isFound=false;

typedef struct node
{

    char* val;
    bool isLeft;
    bool isBlack;
    struct node *leftChild,*rightChild,*parent;

} node;


node* newNode(char* val)
{
    node* temp=(node*)malloc(sizeof(node));
    temp->leftChild=NULL;
    temp->rightChild=NULL;
    temp->parent=NULL;
    temp->val=(char*)malloc(sizeof(char)*30);
    strcpy(temp->val,val);

    temp->isBlack=false;
    temp->isLeft=true;

    return temp;
}


node* getUncle(node *root)
{

    if(root->parent->isLeft)
        return root->parent->parent->rightChild;
    return root->parent->parent->leftChild;
}


int getHeight(node* root)
{
    return (root==nullptr)? -1: 1+max(getHeight(root->leftChild),getHeight(root->rightChild));
}


int getSize(node*root)
{
    return (root==nullptr) ? 0 : 1+getSize(root->leftChild)+getSize(root->rightChild);
}
/*
        changing colors if uncle is red

*/
void changeColor(node *son)
{
    node* parent=son->parent;
    node* grandParent=parent->parent;
    node* uncle=getUncle(son);

    parent->isBlack=true;
    uncle->isBlack=true;
    grandParent->isBlack=false;
    son->isBlack=false;

}
/*

        left rotate
        and return root node each time

*/
node* leftRotate(node *son,bool firstChange)
{
    node* parent=son->parent;
    parent->rightChild=son->leftChild;
    if(parent->rightChild!=nullptr)
    {
        parent->rightChild->isLeft=false;
        parent->rightChild->parent=parent;
    }
    son->leftChild=parent;
    son->isLeft=parent->isLeft;
    parent->isLeft=true;

    node* temp=parent->parent;
    // normalizing
    if(temp!=nullptr)
    {
        if(son->isLeft)
            temp->leftChild=son;
        else
            temp->rightChild=son;
    }


    parent->parent=son;
    son->parent=temp;

    return son;
}
/*

        right rotate

*/
node* rightRotate(node *son,bool firstChange)
{
    node* parent=son->parent;
    parent->leftChild=son->rightChild;
    if(parent->leftChild!=nullptr)
    {
        parent->leftChild->isLeft=true;
        parent->leftChild->parent=parent;
    }

    son->rightChild=parent;
    son->isLeft=parent->isLeft;
    parent->isLeft=false;


    node* temp=parent->parent;
    //normalizing
    if(temp!=nullptr)
    {
        if(son->isLeft)
            temp->leftChild=son;
        else
            temp->rightChild=son;
    }


    parent->parent=son;
    son->parent=temp;

    return son;
}
/*
        rotating if uncle is black

        return grandparent each time

*/
node* rotateNodes(node *son)
{
    node* parent=son->parent;
    node* grandParent=parent->parent;

    node* temp=nullptr;

    if(!parent->isLeft)
    {
        if(!son->isLeft)
        {
            parent->isBlack=true;
            son->isBlack=false;
            grandParent->isBlack=false;

            temp=leftRotate(parent,false);

            return temp;

        }
        else
        {

            parent->isBlack=false;
            son->isBlack=true;
            grandParent->isBlack=false;

            temp=rightRotate(son,true);
            temp= leftRotate(temp,false);

            return temp;
        }
    }
    else
    {

        if(son->isLeft)
        {

            parent->isBlack=true;
            son->isBlack=false;
            grandParent->isBlack=false;

            temp= rightRotate(parent,false);

            return temp;
        }
        else
        {
            parent->isBlack=false;
            son->isBlack=true;
            grandParent->isBlack=false;

            temp= leftRotate(son,true);
            temp= rightRotate(temp,false);

            return temp;
        }
    }

}

node* insertFix(node* root)
{
    node* son=root;
    node* parent=son->parent;
    node* temp=nullptr;


    while(parent!=nullptr && !son->isBlack && !parent->isBlack  )
    {


        if(son->parent->parent==NULL)
        {
            son->parent->isBlack=true;
            return son->parent;
        }


        node *uncle=getUncle(son);

        if(uncle==nullptr || uncle->isBlack)
        {
            temp=rotateNodes(son);
            son=temp;
        }

        else
        {
            changeColor(son);
            son=son->parent->parent;

        }
        parent=son->parent;

    }

    if(son->parent==nullptr)
    {
        son->isBlack=true;
        return son;
    }

    return nullptr;

}

/*
        Insert in tree

*/

void inserter(node*& root,node* temp)
{

    node* p=nullptr;
    node* q=nullptr;
    bool isLeft=false;

    if(root==nullptr)
    {
        root=temp;
        root->parent=nullptr;
        root->isBlack=true;
        return;
    }

    p=root;

    while(p!=nullptr)
    {
        q=p;

        if(strcmp(p->val,temp->val)>0)
        {
            p=p->leftChild;
            isLeft=true;
        }

        else if(strcmp(p->val,temp->val)==0)
          {
              isFound=true;
              return;
          }

        else if(strcmp(p->val,temp->val)<0)
        {
            p=p->rightChild;
            isLeft=false;
        }

        else
            return;
    }

    node* check=nullptr;
    temp->parent=q;
    temp->isBlack=false;
    if(isLeft)
    {
        temp->isLeft=true;
        q->leftChild=temp;
        check=insertFix(q->leftChild);

    }
    else
    {
        temp->isLeft=false;
        q->rightChild=temp;
        check= insertFix(q->rightChild);
    }

    if(check!=nullptr)
        root=check;


}

void insertInTree(node *&root,char* val)
{
    node* temp=newNode(val);
    inserter(root,temp);
}


void printInorder(node* root)
{
    if(root==NULL)
        return;

    printInorder(root->leftChild);
    cout<<root->isBlack<<"   "<<root->val<<"\n";
    printInorder(root->rightChild);


}


void readFromFile(node*& root,char* filename)
{

    FILE *f1=fopen(filename,"r");
    char * s=(char*)malloc(sizeof(char)*30);

    while(!feof(f1))
    {
        fgets(s,255,f1);
        insertInTree(root,s);

    }
        cout<< "\t\tSize= "<<getSize(root)<<"\tHeight= "<<getHeight(root);
        cout<<"\n\t\t---------File Loaded---------\n";
        fclose(f1);

}

int main(int argc,char** argv)
{

    if(argc!=2)
    {

        cout<<"File Error \n";
        exit(0);
    }

    node* tree=nullptr;
    char* searchWord=(char*)malloc(sizeof(char)*30);


    readFromFile(tree,argv[1]);



         cout<<"\n\nEnter a sentence or Press CTRl-Z to exit \n";
          puts("----------------------------------");
     while(fgets(searchWord,255,stdin)!=NULL)
   {


        isFound=false;
        insertInTree(tree,searchWord);

        if(isFound)
            cout<<"Word found!\n";
        else
            cout<<"Word is not found!\n\n"<< "Size= "<<getSize(tree)<<"\tHeight= "<<getHeight(tree)<<"\n|n" ;

        puts("Enter the word you want to search for or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
