#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
	int key;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
};

struct Node* Search_Rec(int key, struct Node* bt) {
	if (bt == NULL) {
		return NULL;
	}
	else {
		if (key == bt->key) {
			return bt;
		}
		else {
			if (key < bt->key) {
				Search_Rec(key, bt->left);
			}
			else {
				Search_Rec(key, bt->right);
			}
		}
	}

}

struct Node* Search_It(int key, struct Node* bt) {
	if (bt == NULL) {
		return NULL;
	}
	struct Node* tmp = bt;
	while (tmp != NULL && key != tmp->key)
	{
		if (key < tmp->key) {
			tmp = tmp->left;
		}
		else {
			tmp = tmp->right;
		}
	}
	return tmp;
}

struct Node*  Max(struct Node* bt) {
	struct Node* tmp = bt;
	while (tmp->right != NULL)
	{
		tmp = tmp->right;
	}
	return tmp;
}

struct Node*  Min(struct Node* bt) {
	struct Node* tmp = bt;
	while (tmp->left != NULL)
	{
		tmp = tmp->left;
	}
	return tmp;
}

struct Node* Successor(struct Node* node) {
	struct Node* tmp = node;
	if (tmp->right != NULL) {
		return Min(tmp->right);
	}
	else {
		//right ancestor (ancestor that has node as right child)
		struct Node* P = tmp->parent;
		while (P != NULL && node == P->right)
		{
			tmp = P;
			P = tmp->parent;
		}
		return P;
	}
}

struct Node* Predecessor(struct Node* node) {
	struct Node* tmp = node;
	if (tmp->left != NULL) {
		return Max(tmp->left);
	}
	else {
		//left ancestor (ancestor that has node as left child)
		struct Node* P = tmp->parent;
		while (P != NULL && node == P->left)
		{
			tmp = P;
			P = tmp->parent;
		}
		if (P->key < node->key) {
			return P;
		}
		else {
			return NULL;

		}
	}
}

struct Node* newNode(int key) {
	struct Node* new_node = malloc(sizeof(struct Node));
	new_node->key = key;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	return new_node;
}

void TreeInsert(struct Node* node, struct Node* bt) {
	struct Node* P = NULL;
	struct Node* S = bt;
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
	node->parent = P;
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
}

//delete a node with only one descendant
void NodeDelete(struct Node* node, struct Node* bt) {
	if (node == bt) {
		//if the root node shold be deleted, rise the nearest one up
		if (node->left != NULL) {
			(*bt) = (*node->left);
		}
		else {
			(*bt) = (*node->right);
		}
	}
	else {
		if (node->left != NULL) {
			(*node->left).parent = (*node).parent;
			(*node->parent).left = (*node).left;
		}
		else {
			(*node->right).parent = (*node).parent;
			(*node->parent).right = (*node).right; //complete this
		}
	}
}

void TreeDelete(struct Node* node, struct Node* bt) {
	//check if right
	if (node->left == NULL && node->right == NULL) {
		if ((*node->parent).left == node) {
			(*node->parent).left = NULL;
		}
		else {
			(*node->parent).right = NULL;
		}
	}
	else {
		if (node->left == NULL || node->right == NULL) {
			NodeDelete(node, bt);
		}
		else {
			struct Node* Y = Successor(node);
			node->key = Y->key;
			free(Y);
		}
	}
}

void leftRotate(struct Node* node, struct Node* bt) {
	struct Node* Y = node->right; 
	node->right = Y->left;
	if (Y->left != NULL) {
		(*Y->left).parent = node;
	}
	Y->parent = node->parent;
	if (node->parent == NULL) {
		bt = Y;
	}
	else {
		if (node == (*node->parent).left) {
			(*node->parent).left = Y;
		}
		else {
			(*node->parent).right = Y;
		}
	}
	Y->left = node;
	node->parent = Y;
	
}

void rightRotate(struct Node* node, struct Node* bt) {
	struct Node* Y = node->left;
	node->left = Y->right;
	if (Y->right != NULL) {
		(*Y->right).parent = node;
	}
	Y->parent = node->parent;
	if (node->parent == NULL) {
		bt = Y;
	}
	else {
		if (node == (*node->parent).right) {
			(*node->parent).right = Y;
		}
		else {
			(*node->parent).left = Y;
		}
	}
	Y->right = node;
	node->parent = Y;
	
}

struct Node* rightAncestor(struct Node* nd)
{
	if (nd->parent == NULL)
		return NULL;
	else if (nd == nd->parent->left)
		return nd->parent;
	else // nd == nd->parent->right
		return rightAncestor(nd->parent);
}


int main() {
	
	/*struct Node* tree = malloc(sizeof(struct Node));
	tree->key = 45;
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;

	
	TreeInsert(newNode(2), tree);
	TreeInsert(newNode(9), tree);
	TreeInsert(newNode(1), tree);
	TreeInsert(newNode(3), tree);
	TreeInsert(newNode(8), tree);
	TreeInsert(newNode(10), tree);*/
	//TreeInsert(newNode(11), tree);

	/*printf("min: %d\n", Min(tree)->key);
	printf("max: %d\n", Max(tree)->key);
	
	struct Node* res = Search_Rec(2, tree);
	res = Search_It(8, tree);
	res = Successor(Search_It(5, tree));*/

	//NodeDelete(Search_It(10, tree), tree);
	//TreeDelete(Search_It(2, tree), tree);
	/*leftRotate(Search_It(5, tree), tree);
	while (tree->parent != NULL) {
		tree = tree->parent;
	}*/
	//rightRotate(Search_It(5, tree), tree);


	struct Node* tree = malloc(sizeof(struct Node));
	tree->key = 45;
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;


	TreeInsert(newNode(23), tree);
	TreeInsert(newNode(52), tree);
	TreeInsert(newNode(12), tree);
	TreeInsert(newNode(48), tree);
	TreeInsert(newNode(1), tree);
	TreeInsert(newNode(7), tree); 
	
	struct Node* res = Search_Rec(52, tree);

	printf("%d ", Successor(res)->key);
}