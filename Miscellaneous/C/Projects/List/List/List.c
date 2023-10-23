#include <stdio.h>
#include <stdlib.h>
#include "Generic.h"

typedef struct Node Node;
struct Node {
	void* content;
	Node* next;   /* pointer to the same structure */
};

void* nodeCalloc(int sizeOfContent) {
	return calloc(1, sizeOfContent + sizeof(Node));
}

Node * newNode(Generic* content) {
	Node* n = nodeCalloc(sizeof(Generic));
	n->content = content;
	n->next = NULL;
	return n;
}

void emplaceBack(Node * parent, Generic* content) {
	while (parent->next != NULL) {
		parent = parent->next;
	}
	parent->next = nodeCalloc(sizeof(Generic));
	parent->next->content = content;
}

void emplaceFront(Node** current, Generic* content){

	Node* newElement = nodeCalloc(sizeof(Generic));
	newElement->content = content;
	newElement->next = *current;
	*current = newElement; 
}

void insertOrdered(Node* head, Generic* content, bool(*comparativeFunction)(Generic* first, Generic* second)){
	int inserted = false;
	while (head->next != NULL)
	{
		if (comparativeFunction(content, head->content) && !comparativeFunction(content, head->next->content)) {

			Node* newElement = nodeCalloc(sizeof(Generic));
			newElement->content = content;
			newElement->next = head->next;
			head->next = newElement;
			inserted = true;
			break;
		}
		head = head->next;
	}
	if (!inserted) {
		emplaceBack(head, content);
	}
}

int getNodesNumber(Node* node) {
	int NodesNumber = 0;
	if (node != NULL)NodesNumber++;
	while (node->next != NULL) {
		node = node->next;
		NodesNumber++;
	}
	return NodesNumber;
}

void printList(Node* node) {
	if (node != NULL)printAllParams(((Generic*)node->content));
	while (node->next != NULL) {
		node = node->next;
		printAllParams(((Generic*)node->content));
	}
}

Node* swap(Node* ptr1, Node* ptr2){
	struct Node* tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return ptr2;
}

void* sort(Node** head, bool(*comparativeFunction)(Generic* first, Generic* second)) {

	int bumberOfElement = getNodesNumber(*head);

	Node** h;
	int i, j;
	bool swapped;

	for (i = 0; i <= bumberOfElement; i++) {

		h = head;
		swapped = false;

		for (j = 0; j < bumberOfElement - i - 1; j++) {

			Node* p1 = *h;
			Node* p2 = p1->next;

			if (comparativeFunction(p1->content, p2->content)) {
				*h = swap(p1, p2);
				swapped = true;
			}

			h = &(*h)->next;
		}


		if (swapped == 0)
			break;
	}
}





int main()
{
	Generic t0 = { 0,'a',91 };
	Generic t1 = { 1,'b',100 };
	Generic t2 = { 2,'c',282 };
	Generic t3 = { 3,'d',973 };
	Generic t4 = { 4,'e',164 };
	Generic t5 = { 5,'f',55 };
	Generic t6 = { 6,'g',46 };
	Generic t7 = { 7,'h',337 };
	Generic t8 = { 8,'i',628 };
	Generic t9 = { 9,'j',19 };

	Generic t10 = {10,'k',645 };
	Generic t11 = { 11,'k',70 };

	/*Node* list = newNode(&t1);
	emplaceBack(list, &t0);
	emplaceBack(list, &t2);
	emplaceBack(list, &t3);
	emplaceBack(list, &t4);
	emplaceBack(list, &t5);
	emplaceBack(list, &t6);
	emplaceBack(list, &t7);
	emplaceBack(list, &t8);
	emplaceBack(list, &t9);*/

	Node* list = newNode(&t1);
	emplaceBack(list, &t2);
	emplaceBack(list, &t6);
	emplaceBack(list, &t3);
	emplaceBack(list, &t4);
	emplaceBack(list, &t5);
	emplaceBack(list, &t7);
	emplaceBack(list, &t8);
	emplaceBack(list, &t0);
	emplaceBack(list, &t9);
	emplaceFront(&list, &t10);

	printList(list);


	sort(&list, isGreaterThen);
	printf("\n");
	printList(list);

	insertOrdered(list, &t11, isGreaterThen);
	printf("\n");
	printList(list);

	//printf("%d, %c, %d", );
}

