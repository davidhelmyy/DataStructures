#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node  Node;
struct Node
{
	char *word;
	struct Node *right,*left;
	int height;
};
Node *newnode(char []);
Node *Search(Node *root,char word[]);
Node *insert(Node *,  char word []);
int height( Node *N);
int size(Node *N);
void split(Node * N);//examines sentence entered by user
Node *maxValueNode(Node *node);
Node *minValueNode(Node *node);
Node *Predecessor(Node * root, Node * x);
Node *Successor(Node *root, Node *x);


int main() {

		FILE *f;
        char *x=(char*) malloc(sizeof(char)*30);
	 Node *root=NULL;
	if((f = fopen("EN-US-UNIQUE.txt","r"))){
		printf("Reading\n");
		while(!feof(f)){
			fgets(x,30,f);

			root=insert(root,x);
		}

		printf("%d\n",height(root));
		printf("%d\n",size(root));




	}
	fclose(f);
	return 0;
}
Node * newnode(char *word)
{

	Node *n;
	n=(Node*)malloc(sizeof(Node));
	n->word=(char*)malloc(sizeof(char)*30);
	strcpy(n->word,word);
	n->left=NULL;
	n->right=NULL;
//	n->height = 1;
	return n;
}
Node * Search (Node *n, char word[])
{

	if ( strcmp(n->word, word) == 0)
	{

		printf("The word is correct \n ");
        return n;
	}
	if(strcmp(n->word, word) < 0)
	{
	if(height(n->right) == 0)
		{
			printf("Word is not in the Tree\n");
			return  n;
		}
		else {
		n = n->right;
		return Search(n, word);
		}
	}
        if(height(n->left) == 0)
		{
			printf("Not Found\n");
			return  n;
		}

			n = n->left;
			return Search(n, word);


}
int height(Node *N)
{
	if (N == NULL)
		return -1;
	return 1+max(height(N->left),height(N->right));

}
int size(Node *N){
if(N==NULL)
    return 0;
else
return 1+size(N->left)+size(N->right);
}

int max(int x, int y)
{
	return(x>y)?x:y;
}

Node * insert (Node * n, char *word)
{
	if(n == NULL)
	n= newnode(word);

	else if(strcmp(n->word, word ) >0)
     n->left=insert(n->left,word);

    else if(strcmp(n->word,word)<0)
    n->right=insert(n->right,word);

return n;
	}




void  split(Node * N){
	char str[1000],*p[100];
	int i=0;

	printf("Enter Sentence to check ");
	scanf("%[^\n]s",str);

	char *token = strtok(str, " ");


	while (token != NULL)
	{

		p[i] = token;
		if(p[i][1]!='\0')
		{
			Node *s;
		s=Search (N, p[i]);
		printf("Suggestions: (%s) \t (%s)\n",Predecessor(N,s)->word, Successor(N, s)->word );
		i++;
		token = strtok(NULL, " ");
		}
	}
}
void preOrder(struct Node *root)
{
	if(root != NULL)
	{
		printf("%s ", root->word);
		preOrder(root->left);
		preOrder(root->right);
	}
}

Node * minValueNode(Node* node)
{
	if (!node)
		return NULL;
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}
Node * maxValueNode(Node *node)
{
	if (!node)
		return NULL;
	Node* current = node;
	while (current->right != NULL)
		current = current->right;
	return current;
}
Node * Predecessor(Node * root, Node * x)
{
	if (!x)
		return NULL;
		if(x->left)
			return maxValueNode(x->left);
	Node *p = NULL;
	while (root != NULL) {
		if (strcmp(x->word, root->word) >0)
		{
			p=root;
			root=root->right;
		}
		else if (strcmp(x->word, root->word) < 0)
		{
			root = root->left;
		}
		else break;

	}
	return p;
}
Node * Successor(Node *root, Node *x)
{
	if (x->right != NULL)
		return minValueNode(x->right);
	Node *s = NULL;
	while (root!= NULL)
	{
		if(strcmp(x->word,root->word) < 0)
		{
			s = root;
			root = root->left;
		}
		else if (strcmp(x->word,root->word) > 0)
			root=root->right;
		else break;

	}
	return s;
}
