#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>


int solution(int A[], int N)
{
    int max,i,*son1,*son2,level=1;
    max=*(A);


    for(i=1;i<=N;i++)
       {
           if((2*i)<N-1)
           son1=(A+(2*i)+1);
           else
            son1=0;

            if((2*i)+1<N-1)
           son2=(A+(2*i)+2);
           else son2=0;


           if((*son1)+(*son2)>max)
           {
               level=i;
               max=(*son1)+(*son2);

           }

      }


    return level;
}




int main()
{
    int A[4]={-1, 7, 0, 7, -8};
    int x=solution(A,5);
    printf("%d",x);




    return 0;
}
