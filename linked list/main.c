#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int x;
    struct node *next;
} node;

node *createlist(int n)
{
    int i;
    node *head=NULL;
    node *temp=NULL;
    node *p=NULL;
    for(i=0; i<n; i++)

    {
        temp=(node*)malloc((sizeof(node)));
            printf("enter data %d\n",i+1);
            scanf("%d",&(temp->x));
            temp->next=NULL;



            if(head==NULL)
                head=temp;

            else
            {
                p=head;

                while(p->next!=NULL)
                    p=p->next;


                p->next=temp;
            }
        }
           return head;
    }





void printlist(node *head)
{
    node *p=head;
    printf("\n................................\n");
    while(p!=NULL)
    {

        printf("%d\n",(p->x));
        p=p->next;

    }

}

int main()
{
    node *head=NULL;
    int n;
    printf("how many nodes\n");
    scanf("%d",&n);
    head=createlist(n);




    printlist(head);











    return 0;
}
