#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct
{
    char *name;
    int remaining_time;
} Process, *Item;
/*
 * Process, *Item;
 */
typedef struct Node
{
    Item data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node *head,*tail;
} Queue;
/*
 *
 */
void init(Queue *q)
{
    q->head=NULL;
    q->tail=NULL;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(q->head==NULL)
        return 1;
    return 0;
}
/*
 *
 */
Item dequeue(Queue *q)
{

    if(isEmpty(q))
        return NULL;

    Node *p=q->head;
    Item temp=(Item)malloc(sizeof(Process));
    temp=q->head->data;
    q->head=q->head->next;
    free(p);
    return temp;



}
/*
 *
 */
void enqueue(Queue *q, Item val)
{
    Node *temp;
    temp=(Node*)malloc(sizeof(Node));
    temp->data=val;
    temp->next=NULL;
    if(q->head==NULL)
    {
        q->head=temp;
        q->tail=temp;

    }
    else
    {
        q->tail->next=temp;
        q->tail=temp;
    }


}
/*
 *
 */
void destroy(Queue *q)
{

    Node *p=q->head;
    while (q->head!=q->tail)
    {
        q->head=q->head->next;
        free(p);
        p=q->head;
    }
    q->head=NULL;
    free(q->tail);

}
/*
 * RoundRobin Scheduling
*/





void RoundRobin(char* filename)
{
    FILE *p;
    p=fopen(filename,"r");
    Queue q;
    init(&q);
    Item temp,poped;
    int time=0,flag=0,flag2=0,initialT,i;
    int entertime;


    if(p==NULL)
    {
        printf("Error opening the file\n");
        exit(0);

    }

    while(!feof(p))
    {
        temp=(Item)malloc(sizeof(Process));
        temp->name=(char*)malloc(5*sizeof(char));

        fscanf(p,"%s %d %d",&*(temp->name),&entertime,&temp->remaining_time);

            if (flag2==0)
            {
               time=entertime;
               initialT=time;
               for(i=0;i<time;i++)
                printf("Idle  ( %d --> %d )\n",(i),(i+1));
                flag2=1;

            }



      while(entertime>time)
        {

            if(time+1==entertime)
             {
                 if(isEmpty(&q))
                 {
                     flag=1;
                     printf("Idle  ( %d --> %d )\n",(time),(time+1));
                 }
               enqueue(&q,temp);

               }


            if(isEmpty(&q))
                  printf("Idle  ( %d --> %d )\n",(time),(time+1));


            else if(flag==0)
            {
                poped=(Item)malloc(sizeof(Process));
                poped->name=(char*)malloc(5*sizeof(char));
                poped=dequeue(&q);
                if(poped->remaining_time>0)
                {
                    printf("%s    ( %d --> %d )",poped->name,(time),(time+1));
                    poped->remaining_time--;
                    if(poped->remaining_time==0)
                        printf("   %s Halts",poped->name);
                    else
                            enqueue(&q,poped);
                    printf("\n");

                }

            }



            time++;
        }

        if(time==initialT)
            enqueue(&q,temp);
            flag=0;


    }

    while(!isEmpty(&q))
    {

        poped=(Item)malloc(sizeof(Process));
        poped->name=(char*)malloc(5*sizeof(char));
        poped=dequeue(&q);
        if(poped->remaining_time>0)
        {
            printf("%s    ( %d --> %d )",poped->name,(time),(time+1));
            poped->remaining_time--;
            if(poped->remaining_time==0)
                printf("   %s Halts",poped->name);

            else
                enqueue(&q,poped);
            printf("\n");

        }
        time++;
    }


    printf("EOF\n");



    fclose(p);

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


    RoundRobin(argv[1]);

   // RoundRobin("Example.txt");


    return 0;
}
