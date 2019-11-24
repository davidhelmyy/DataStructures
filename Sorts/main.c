#include <stdio.h>
#include <stdlib.h>



/* this is a sample code for the following sorting algorithms

   -head sort
   -insertion sort
   -selection sort
   -bubble sort

*/



int getLeftChild(int index)
{
    return (2*index)+1;
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




void swap(int *arr,int index1,int index2){

int temp=*(arr+index1);
*(arr+index1)=*(arr+index2);
*(arr+index2)=temp;

}

void maxHeapify(int*arr,int size,int index)
{
    int max=0;

    while(hasLeftChild(index,size))
    {
       max=getLeftChild(index);


        if(hasRightChild(index,size)&&arr[getLeftChild(index)]<arr[getRightChild(index)])
            max=getRightChild(index);

            if(arr[index]<arr[max])
            {
                swap(arr,index,max);
                index=max;
            }else
            break;

    }


}

void constructHeap(int*arr,int size)
{
    int n=size/2;
    while(n>0)
        maxHeapify(arr,size,n--);

}

void SortHeap(int*arr ,int size)
{
    while(size>0){
   swap(arr,0,size);
   size--;
   maxHeapify(arr,size,0);}
}







void insertByInsertionSort(int *arr,int data,int *size)
{
    arr[*size]=data;

    int i;
    for(i=*size;i>0;i--)
    {
        if(arr[i]<arr[i-1])
            swap(arr,i,i-1);
        else
            break;

    }
      (*size)++;
}

void InsertionSort(int*arr,int n)
{

    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=i;j>0;j--)
        {
             if(arr[j]<arr[j-1])
            swap(arr,j,j-1);
              else
             break;
        }

    }
}



void BubbleSort(int*arr,int size)
{
    int i,j;
    for(i=0;i<size;i++)
    {
        for(j=size-1;j>i;j--)
        {
            if(arr[j]<arr[j-1])
                swap(arr,j,j-1);
        }

    }

}







void selectionSort(int *arr,int n)
{
    int i,j,min;

    for(i=0;i<n-1;i++)
    {
        min=i;
        for(j=i+1;j<n;j++)
        {
            if(*(arr+j)<*(arr+min))
           // if(arr[j]<arr[min])
                  min=j;

        }
           swap(arr,i,min);

    }

}



int readfile(char** filename,int *arr)
{
    FILE *p=fopen(filename,"r");
    int i=0;
    while(!feof(p))
        fscanf(p,"%d",&arr[i++]);

    return i;
}



int readfileAndSort(char** filename,int *arr)
{
    FILE *p=fopen(filename,"r");
    int i=0;
    int temp;
    while(!feof(p))
      {
           fscanf(p,"%d",&temp);
           insertByInsertionSort(arr,temp,&i);

      }

    return i;
}






int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("Error Loading File1\n");
        exit(0);
    }
    int *arr=(int*)malloc(sizeof(int)*10000);
    int size=readfile(argv[1],arr);

  // selectionSort(arr,size);
 // InsertionSort(arr,size);
 // insertByInsertionSort(arr,15,&size);
  // insertByInsertionSort(arr,24,&size);
  //  insertByInsertionSort(arr,21,&size);
    // BubbleSort(arr,size);
    constructHeap(arr,size);
    SortHeap(arr,size);

  //arr[size++]=22;
 //  arr[size++]=21;
    int i;

    for(i=0;i<size;i++)
     printf("%d\n",arr[i]);

    // printf("%d",i);


    return 0;
}
