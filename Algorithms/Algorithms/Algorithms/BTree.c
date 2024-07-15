
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//albero binario non di ricerca, non è garantito l'ordine degli elementi
struct BTreeND {
	int key;
	struct BTree* left;
	struct BTree* right;
};

typedef struct BTreeND* BTree;

struct triple {
	bool    isOrdered;
	int     min, max;
};

typedef struct triple Triple;

struct queueEl {
	BTree*          info;
	struct queueEl* next;
};

struct queueFrame {
	struct queueEl* front; // primo el. della coda
	struct queueEl* rear;  // ultimo el. della coda
};

typedef struct queueFrame* queue;

struct StackEl {
	BTree* key;
	struct StackEl* next;
};


typedef struct StackEl* stack;

stack newStack() {
	stack s = malloc(sizeof(struct StackEl));
	s->key = NULL;
	s->next = NULL;
	return s;
}

stack push(stack* old, BTree* key) {
	stack s = malloc(sizeof(struct StackEl));
	s->next = *old;
	s->key = key;
	(*old) = (s);
	return s;
}

BTree* pop(stack* s) {
	BTree* res = (*s)->key;
	if ((*s)->next != NULL) {
		(*s) = (*s)->next;
	}
	else {
		(*s) = NULL;
	}
	return res;
}

bool isStackEmpty(stack s) {
	return s->key == NULL ;
}

queue NewQueue() {
	queue q = malloc(sizeof(struct queueFrame));
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void EnQueue(BTree* t, queue q) {
	struct queueEl* newEl = malloc(sizeof(struct queueEl));
	newEl->info = t;
	newEl->next = NULL;
	if (q->front == NULL)
		q->front = q->rear = newEl;
	else // q->front != NULL implica q->rear != NULL
	{
		q->rear->next = newEl;
		q->rear = newEl;
	}
}

BTree* DeQueue(queue q) {
	BTree* t = q->front->info;
	struct queueEl* oldFirst = q->front;
	if (q->front == q->rear) // la coda ha un solo el.
		q->front = q->rear = NULL;
	else
		q->front = q->front->next;
	free(oldFirst);
	return t;
}

bool isEmptyQueue(queue q) {
	return q->front == NULL;
}

BTree ConsTree(int key, BTree left, BTree right) {
	BTree root = malloc(sizeof(struct BTreeND));
	root->key = key;
	root->left = left;
	root->right = right;
	return root;
}

BTree insert(int key, BTree bt) {
	
	BTree node = ConsTree(key, NULL, NULL);
	BTree P = NULL;
	BTree S = bt;
	while (S != NULL)
	{
		P = S;
		if (node->key == S->key) {
			return;
		}
		else {
			if (node->key < S->key) {
				S = S->left;
			}
			else {
				S = S->right;
			}
		}
	}
	
	if (P == NULL) {
		bt = node;
	}
	else {
		if (node->key < P->key) {
			P->left = node;
		}
		else {
			P->right = node;
		}
	}
	free(S);
	return bt;
}

//since this is not sorted the search will take O(n)
bool search(BTree tree, int k) {
	if(tree == NULL) return false;
	if (tree->key == k)return true;
		search(tree->left, k);
		return search(tree->left, k) || search(tree->right, k);
}

void PrintTree(BTree tree, int margin) {
	if (tree == NULL) return;
	for (size_t i = 0; i < margin; i++)
	{
		printf("   ");
	}
	printf("%d\n", tree->key);
	PrintTree(tree->left, margin + 1);
	PrintTree(tree->right, margin + 1);
}

void PrintTreeWNil(BTree bt, int n) {
	for (int i = 0; i < n; i++)
		printf("   ");
	if (bt == NULL)
		printf("nil\n");
	else {
		printf("%d\n", bt->key);
		PrintTreeWNil(bt->left, n + 1);
		PrintTreeWNil(bt->right, n + 1);
	}
}



void BFS(BTree tree) {
	queue Q = NewQueue();
	EnQueue(&tree, Q);
	while (!isEmptyQueue(Q))
	{
		BTree* t = DeQueue(Q);
		printf("%d ", (*t)->key);
		if ((*t)->left != NULL) {
			EnQueue(&(*t)->left,Q);
		}

		if ((*t)->right != NULL) {
			EnQueue(&(*t)->right, Q);
		}
	}
}

void DFS(BTree tree) {
	stack S = newStack();
	push(S, &tree);
	while (!isStackEmpty(S))
	{
		BTree* t = pop(S);
		printf("%d ", (*t)->key);
		if ((*t)->left != NULL) {
			push(S,&(*t)->left);
		}

		if ((*t)->right != NULL) {
			push(S,&(*t)->right);
		}
	}
}


//use the same technique of BFS to fins the first null element
bool addKey(BTree tree, int key) {
	if (tree == NULL) {
		tree = ConsTree(key, NULL, NULL);
		return true;
	}

	queue Q = NewQueue();
	EnQueue(&tree, Q);

	while (!isEmptyQueue(Q))
	{
		BTree* t = DeQueue(Q);
		if ((*t)->left != NULL) {
			EnQueue(&(*t)->left, Q);
		}
		else {
			(*t)->left = ConsTree(key, NULL, NULL);
			return true;
		}

		if ((*t)->right != NULL) {
			EnQueue(&(*t)->right, Q);
		}
		else {
			(*t)->right = ConsTree(key, NULL, NULL);
			return true;
		}
	}
	
	//to complete
}



int Min(BTree bt) {
	int res = bt->key;
	int l, r;
	if (bt->left != NULL) {
		l = Min(bt->left);
		if (l < res) res = l;
	}
	
	if (bt->right != NULL) {
		r = Min(bt->right);
		if (r < res) res = r;
	}
	
	return res;
}

int Max(BTree bt) {
	int res = bt->key;
	int l, r;
	if (bt->left != NULL) {
		l = Max(bt->left);
		if (l > res) res = l;
	}

	if (bt->right != NULL) {
		r = Max(bt->right);
		if (r > res) res = r;
	}

	return res;
}

Triple isOrderedBTreeAux(BTree bt) {
	Triple res;
	res.isOrdered = true;
	int biggestLeft;
	int smallestRight;
	if (bt->left != NULL) {
		biggestLeft = Max(bt->left);
	}
	if (bt->right != NULL) {
		smallestRight = Min(bt->right);
	}

	if (smallestRight < bt->key || biggestLeft > bt->key) {
		res.isOrdered = false;
	}

	if (smallestRight < biggestLeft) {
		res.isOrdered = false;
	}


	return res;
}

// post: true se bt è di ricerca, false altrimenti
bool isOrdered(BTree bt) {
	return isOrderedBTreeAux(bt).isOrdered;
}

// pre:  nd != NULL è un nodo di un albero binario di ricerca
// post: ritorna l'avo destro più prossimo a nd se esiste; NULL altrimenti
//per avo destro si intende il primo nodo che ha come figlio sinistro (anche molto lontano) il nodo nd



int main() {

	/*BTree bt =
		ConsTree(20,
			ConsTree(35,
				ConsTree(9, NULL, NULL),
				ConsTree(1, NULL, NULL)
			),
			ConsTree(5, 
				NULL, 
				ConsTree(3, NULL, NULL))
		);*/
	//PrintTree(bt, 0);

	/*BTree bt = ConsTree(20,
		ConsTree(15, NULL, NULL),
		ConsTree(25,
			ConsTree(19, NULL, NULL),
			ConsTree(30, NULL, NULL)
		)
	);*/
	//PrintTree(bt, 0);
	
	BTree bt1 = insert(45, NULL);
	bt1 = insert(23, bt1);
	bt1 = insert(52, bt1);
	bt1 = insert(12, bt1);
	bt1 = insert(48, bt1);
	bt1 = insert(1, bt1);
	bt1 = insert(7, bt1);
	PrintTree(bt1, 0);
	printf("is ordered: %d", isOrderedBTreeAux(bt1).isOrdered);
	printf("\n\n\n");
	
	int min = Min(bt1);
	int max = Max(bt1);

	BTree bt2 = insert(28, NULL);
	bt2 = insert(34, bt2);
	bt2 = insert(67, bt2);
	bt2 = insert(12, bt2);
	bt2 = insert(51, bt2);
	bt2 = insert(4, bt2);
	PrintTree(bt2, 0);
	printf("is ordered: %d", isOrderedBTreeAux(bt2).isOrdered);
	printf("\n\n\n");

	BTree bt3 =
		ConsTree(20,
			ConsTree(15, NULL, NULL),
			ConsTree(25,
				ConsTree(19, NULL, NULL),
				ConsTree(30, NULL, NULL)
			)
		);
	PrintTree(bt3, 0);
	printf("is ordered: %d", isOrderedBTreeAux(bt3).isOrdered);
	printf("\n\n\n");

	BTree bt4 =
		ConsTree(20,
			ConsTree(15,
				ConsTree(9, NULL, NULL),
				ConsTree(22, NULL, NULL)
			),
			ConsTree(27, NULL, NULL)
		);
	PrintTree(bt4, 0);
	printf("is ordered: %d", isOrderedBTreeAux(bt4).isOrdered);
	printf("\n\n\n");
	//PrintTreeWNil(bt, 0);
	//printf("%d\n", search(bt,1));

	
	printf("\n");
	
}