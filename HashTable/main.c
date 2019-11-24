#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node{

int data;
char* key;
struct Node *next;

}Node;


typedef struct {

   Node **table;
   unsigned int size;

}HashTable;


HashTable* initHash(HashTable* hashTable, unsigned int n)
{

    hashTable=malloc(sizeof(HashTable)*1);
    hashTable->table=malloc(sizeof(Node*)*n);

    hashTable->size=n;


    unsigned int i=0;
    for(;i<n;++i)
    hashTable->table[i]=NULL;


 return hashTable;

}



unsigned int HashKey(HashTable* hash,char *key)
{
    unsigned int value=0;
    unsigned int i=0;
    unsigned int len=strlen(key);


    for(;i<len;++i)
        value+=value*37+key[i];

    value=value%(hash->size);

    return value;
}


Node* CreateNode(int data,char* key)
{
    Node *temp=(Node*)malloc(sizeof(Node)*1);
    temp->key=malloc(sizeof(key)+1);
    temp->key=key;
    temp->data=data;
    temp->next=NULL;

    return temp;

}



void InsertInHash(HashTable* hash,char* key,int data)
{
   unsigned int index=HashKey(hash,key);
    if(hash->table[index]==NULL)
        hash->table[index]=CreateNode(data,key);

    else
    {
        Node* p=hash->table[index];

        while(p->next !=NULL)
        p=p->next;

        p->next=CreateNode(data,key);

    }


}


void searchInTable(HashTable* hash,char* key)
{

    unsigned int index=HashKey(hash,key);

    if(hash->table[index]==NULL)
        printf("Not Found\n");

    else if(strcmp(hash->table[index]->key,key)==0)
        printf("%s \t %d\n",hash->table[index]->key,hash->table[index]->data);

    else
     {

         Node* p=hash->table[index]->key;

         while(strcmp(p->key,key)!=0 || p!=NULL)
            p=p->next;

         if(p==NULL)
            printf("Not Found\n");
         else
            printf("%s \t %d\n",p->key,p->data);


     }


}


void printAll(HashTable* hash)
{

    Node *p;

    for(int i=0;i<hash->size;++i)
    {

        if(hash->table[i]!=NULL)
        {
             printf("%s \t  \t %d\n",hash->table[i]->key,i);

            if(hash->table[i]->next!=NULL)
            {
                p=hash->table[i]->next;
                while(p!=NULL)
                {
                      printf("%s \ \t %d\n",p->key,i);
                      p=p->next;

                }


            }
        }
    }
}





void printIndex(HashTable* hash)
{

    Node *p;

    for(int i=0;i<hash->size;++i)
    {

        if(hash->table[i]!=NULL)
        {
             printf("%d\n",i);

            if(hash->table[i]->next!=NULL)
            {
                p=hash->table[i]->next;
                while(p!=NULL)
                {
                      printf("%d\n",i);
                      p=p->next;

                }


            }
        }
    }
}







int main()
{

    HashTable *hash;
    hash=initHash(hash,100);
    InsertInHash(hash,"david",5);
    InsertInHash(hash,"ahmed",12);
    InsertInHash(hash,"aly",34);
    InsertInHash(hash,"youssef",76);
    InsertInHash(hash,"mina",21);
    InsertInHash(hash,"dany",3);
    InsertInHash(hash,"mostafa",12);
    InsertInHash(hash,"dave",89);
    InsertInHash(hash,"rich",42);

printIndex(hash);

    return 0;
}
