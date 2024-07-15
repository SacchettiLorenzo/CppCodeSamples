

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct kTreeVertex {
	int                  key;
	struct kTreeVertex* child;
	struct kTreeVertex* sibling;
};

typedef struct kTreeVertex* kTree;

struct queueEl {
	kTree* info;
	struct queueEl* next;
};

struct queueFrame {
	struct queueEl* front; // primo el. della coda
	struct queueEl* rear;  // ultimo el. della coda
};

typedef struct queueFrame* queue;

struct StackEl {
	kTree* key;
	struct StackEl* next;
};

typedef struct StackEl* stack;

struct listEl {
	int            info;
	struct listEl* next;
};

typedef struct listEl* list;

list Cons(int x, list xs) {
	list newlist = malloc(sizeof(struct listEl));
	newlist->info = x;
	newlist->next = xs;
	return newlist;
}

void printlist(list l) {
	while (l != NULL) {
		printf("%d ", l->info);
		l = l->next;
	}
	printf("\n");
}


stack newStack() {
	stack s = malloc(sizeof(struct StackEl));
	s->key = NULL;
	s->next = NULL;
	return s;
}

stack push(stack* old, kTree* key) {
	stack s = malloc(sizeof(struct StackEl));
	s->next = *old;
	s->key = key;
	(*old) = (s);
	return s;
}

kTree* pop(stack* s) {
	kTree* res = (*s)->key;
	if ((*s)->next != NULL) {
		(*s) = (*s)->next;
	}
	else {
		(*s) = NULL;
	}
	return res;
}

bool isStackEmpty(stack s) {
	return s->key == NULL;
}

queue NewQueue() {
	queue q = malloc(sizeof(struct queueFrame));
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void EnQueue(kTree* t, queue q) {
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

kTree* DeQueue(queue q) {
	kTree* t = q->front->info;
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

kTree consTree(int k, kTree c, kTree s) {
	kTree t = malloc(sizeof(struct kTreeVertex));
	t->key = k;
	t->child = c;
	t->sibling = s;
	return t;
}

kTree leaf(int k, kTree s) {
	return consTree(k, NULL, s);
}

kTree root(int k, kTree c) {
	return consTree(k, c, NULL);
}

void printTree(kTree t, int d) {
	if (t != NULL)
		for (int i = 0; i < d; ++i)
			printf("   ");
	printf("%d\n", t->key);
	kTree cl = t->child;
	while (cl != NULL) {
		printTree(cl, d + 1);
		cl = cl->sibling;
	}
}



//controlla se tutti gli elementi sono dispari
bool isDispari(kTree t) {
	if (t == NULL) {
		return false;
	}
	else {
		bool res = t->key % 2 == 1;
		kTree c = t->child;
		while (c != NULL)
		{
			res = res && isDispari(c);
			c = c->sibling;
		}
		return res;
	}
	
}

int height(kTree t) {
	if (t->child == NULL)
		return 0;
	else {
		int ht = 0;
		kTree c = t->child;
		while (c != NULL) {
			ht = max(ht, height(c));
			c = c->sibling;
		}
		return ht + 1;
	}
}

int sumLeaf(kTree t) {
	if (t == NULL)return 0;
	else {
		if (t->child == NULL) {
			return t->key;
		}
		else {
			int res = 0;
			kTree c = t->child;
			while (c != NULL) {
				res = res + sumLeaf(c);
				c = c->sibling;
			}
			return res;
		}
	}

}

list fastReverse(list l,list m) {
	if (l == NULL) {
		return m;
	}
	return fastReverse(l->next, Cons(l->info, m));
}

list BFS(kTree t) {
	queue q = NewQueue();
	EnQueue(t, q);
	list res = NULL;
	
	while (!isEmptyQueue(q))
	{
		kTree current = DeQueue(q); //si aggiunge quello appena tirato fuori dall coda
		res = Cons(current->key, res);
		current = current->child;//si lavora sul child e sui sibling del child
		while (current != NULL) {
			EnQueue(current, q);
			current = current->sibling;
		}
		
	}

	res = fastReverse(res, NULL);
	return res;
}

list DFS(kTree t) {
	stack s = newStack();
	push(s, t);
	list res = NULL;
	res = Cons(t->key, res);
	while (!isStackEmpty(s))
	{
		kTree current = pop(s);
		if (current->child != NULL) {//si esegue il DFS sul child dell'elemento in cima allo stack
			res->next =  DFS(current->child);
			
		}
		
		//dopo aver eseguito il dfs su tutti i child possibili
		if (current->sibling != NULL) {
			//si va al fondo della lista
			list tmp = res;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}
			//si aggiungono i DFS di tutti i sibling possibili
			tmp->next = DFS(current->sibling);
		}
		
	}
	return res;
}

void DFS_(kTree t) {
	printf("%d ", t->key);
	while (t->child != NULL) {
		//DFS sul child e poi sui sibling di child
		DFS_(t->child);
		t->child = t->child->sibling;
	}
}


int main() {

	// test 1
	kTree t =
		root(11, consTree(23, leaf(1, NULL), leaf(4, root(31, leaf(3, leaf(5, NULL))))));

	//printf("Albero dato:\n");
	printTree(t, 0);
	printf("dispari %d\n", isDispari(t));
	printf("altezza %d\n", height(t));
	printf("sum leaf %d\n", sumLeaf(t));
	printlist(BFS(t));
	printlist(DFS(t));
	DFS_(t);
}