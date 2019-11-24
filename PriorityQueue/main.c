#include <stdio.h>
#include <stdlib.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
    char* cName;
    double balance;
    int order;
} Item;

/*
 * helping functions to get index and states
 */

int getLeftChild(int index)
{
    return (2*index);
}
int getRightChild(int index)
{
    return getLeftChild(index)+1;
}
int hasLeftChild(int index,int size)
{
    return (getLeftChild(index)<=size)? 1:0;
}
int hasRightChild(int index,int size)
{
    return (getRightChild(index)<=size)? 1:0;
}
double getBalance(Item *arr,int index)
{
    return arr[index].balance;
}
int getOrder(Item *arr,int index)
{
    return arr[index].order;
}
void swap(Item* arr,int index1,int index2)
{
    Item temp=*(arr+index1);
    *(arr+index1)= *(arr+index2);
    *(arr+index2)=temp;

}
/*
 * Heapify index i in array of Items with size n
 */
void max_heapify(Item *arr, int n, int i)
{

    while(hasLeftChild(i,n))
    {
        int maxSon=getLeftChild(i);
        if(hasRightChild(i,n))
        {
            if(getBalance(arr,maxSon)<getBalance(arr,maxSon+1))
             maxSon=getRightChild(i);
           else if(getBalance(arr,maxSon)==getBalance(arr,maxSon+1)&&getOrder(arr,maxSon)>getOrder(arr,maxSon+1))
           maxSon=getRightChild(i);

        }

        if(getBalance(arr,i)>getBalance(arr,maxSon))
            break;
        else if(getBalance(arr,i)==getBalance(arr,maxSon))
        {
            if(getOrder(arr,i)<getOrder(arr,maxSon))
                break;
            else
                swap(arr,i,maxSon);

        }

        else
            swap(arr,i,maxSon);
        i=maxSon;

    }
}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{
    int size=n;
    n=n/2;
    while(n!=0)
    {
       max_heapify(arr,size,n);
       --n;
    }

}
/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum(Item*arr,int n)
{
    Item temp=*(arr+1);
    swap(arr,1,n);
    --n;
    max_heapify(arr,n,1);
    return temp;

}

void SortHeap(Item* arr,int n)
{

Item temp;

    while(n!=0)
   temp= extract_maximum(arr,n--);
}

/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
    FILE *file=fopen(fname,"r");
    int i=1;
    while(!feof(file))
    {
        arr[i].cName=(char*)malloc(sizeof(char)*20);
        fscanf(file,"%s %lf",arr[i].cName,&arr[i].balance);
        arr[i].order=i;
             ++i;
    }
    fclose(file);
    return i;
}
int counter=1;
void printItem(Item item)
{
    printf("%d  ",counter++);
      printf("%s -  %.2lf - %d\n",item.cName,item.balance,item.order);
      printf("--------------------------\n");

}
void printCustomersbyPriorityBigToSmall(Item*arr,int n)

{

    Item temp;
    while (n!=1)
       {
          temp= extract_maximum(arr,n--);
           printItem(temp);


       }

}

/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{
    Item temp;
   if(n==1)
    return;
    temp=extract_maximum(arr,n);
    printCustomersbyPriority(arr,--n);
     printItem(temp);


}



/*
 *
 */


int main(int argc, char**argv)
{

    if(argc!=2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
 //   printCustomersbyPriority(customers,arrLength);
 // printCustomersbyPriorityBigToSmall(customers,arrLength);

    SortHeap(customers,arrLength);
    for(int i=1;i<=arrLength;i++)
        printItem(customers[i]);


    return 0;
}
