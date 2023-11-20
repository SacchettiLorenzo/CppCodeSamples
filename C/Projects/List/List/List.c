#include <stdio.h>
#include <stdlib.h>
#include "Generic.h"

typedef struct Node Node;
struct Node
{
	void *content;
	Node *next; /* pointer to the same structure */
};

/*allocation of memory for a new nodes*/
void *nodeCalloc(int sizeOfContent)
{
	return calloc(1, sizeOfContent + sizeof(Node));
}

/*create a node with a given content*/
Node *newNode(Generic *content)
{
	Node *n = nodeCalloc(sizeof(Generic));
	n->content = content;
	n->next = NULL;
	return n;
}

/*add element at the end of the list*/
void push_back(Node *parent, Generic *content)
{
	while (parent->next != NULL)
	{
		parent = parent->next;
	}
	parent->next = nodeCalloc(sizeof(Generic));
	parent->next->content = content;
}

/*add element at the bottom of the list*/
void emplace_front(Node **current, Generic *content)
{
	Node *newElement = nodeCalloc(sizeof(Generic));
	newElement->content = content;
	newElement->next = *current;
	*current = newElement;
}

/*insert element in the order specified by the comparative function provided in Generic*/
void insertOrdered(Node *head, Generic *content, bool (*comparativeFunction)(Generic *first, Generic *second))
{
	int inserted = false;
	while (head->next != NULL)
	{
		if (comparativeFunction(content, head->content) && !comparativeFunction(content, head->next->content))
		{

			Node *newElement = nodeCalloc(sizeof(Generic));
			newElement->content = content;
			newElement->next = head->next;
			head->next = newElement;
			inserted = true;
			break;
		}
		head = head->next;
	}
	if (!inserted)
	{
		push_back(head, content);
	}
}

/*count nodes*/
int getNodesNumber(Node *node)
{
	int NodesNumber = 0;
	if (node != NULL)
		NodesNumber++;
	while (node->next != NULL)
	{
		node = node->next;
		NodesNumber++;
	}
	return NodesNumber;
}

/*print all the element using the function form Generic*/
void printList(Node *node)
{
	if (node == NULL)
	{
		printf("list is empty");
	}
	else
	{
		printAllParams(((Generic *)node->content));
		while (node->next != NULL)
		{
			node = node->next;
			printAllParams(((Generic *)node->content));
		}
	}
}

/*swap two elements*/
Node *swap(Node *ptr1, Node *ptr2)
{
	struct Node *tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return ptr2;
}

/*sort element(bubblesort)*/
void *sort(Node **head, bool (*comparativeFunction)(Generic *first, Generic *second))
{

	int numberOfElement = getNodesNumber(*head);

	Node **h;
	int i, j;
	bool swapped;

	for (i = 0; i <= numberOfElement; i++)
	{

		h = head;
		swapped = false;

		for (j = 0; j < numberOfElement - i - 1; j++)
		{

			Node *p1 = *h;
			Node *p2 = p1->next;

			if (comparativeFunction(p1->content, p2->content))
			{
				*h = swap(p1, p2);
				swapped = true;
			}

			h = &(*h)->next;
		}

		if (swapped == 0)
			break;
	}
}

/*assign a new content to a node*/
void assign(Node *ptr, Generic *content)
{
	ptr->content = content;
}

/*remove last elemet*/
void pop_back(Node *head)
{
	while (head->next->next != NULL)
	{
		head = head->next;
	}

	Node *dealloc = head->next;
	head->next = NULL;

	free(dealloc);
}

/*dealloc all the nodes*/
void erase(Node *head)
{
	if (head->next != NULL)
	{
		erase(head->next);
		free(head);
	}
}

/*delete the content of all the nodes*/
void clear(Node * head){
	if(head->next != NULL){
		clear(head->next);
	}
		head->content = calloc(1,sizeof(Generic));
}

/*delete the content of the nodes*/
void clear(Node * head){
		head->content = calloc(1,sizeof(Generic));
}

/*TODO -
 clear(){} // delete the content of a node allocationg an empty new generic pointer
*/

int main()
{
	Generic t0 = {0, 'a', 91};
	Generic t1 = {1, 'b', 100};
	Generic t2 = {2, 'c', 282};
	Generic t3 = {3, 'd', 973};
	Generic t4 = {4, 'e', 164};
	Generic t5 = {5, 'f', 55};
	Generic t6 = {6, 'g', 46};
	Generic t7 = {7, 'h', 337};
	Generic t8 = {8, 'i', 628};
	Generic t9 = {9, 'j', 19};

	Generic t10 = {10, 'k', 645};
	Generic t11 = {11, 'k', 70};

	Node *list = newNode(&t1);
	push_back(list, &t2);
	push_back(list, &t6);
	push_back(list, &t3);
	push_back(list, &t4);
	push_back(list, &t5);
	push_back(list, &t7);
	push_back(list, &t8);
	push_back(list, &t0);
	push_back(list, &t9);
	emplace_front(&list, &t10);

	clear(list);
	assign(list,&t10);
	
	printList(list);
	
}
