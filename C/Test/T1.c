#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
    int val;
    struct _node * next;
} node;

node * list_invert(node * head);

int main(){
    node * head = malloc(sizeof (struct _node));
    head->val = 1;
    head->next = malloc(sizeof(struct _node));
    head->next->val = 2;
    head->next->next = malloc(sizeof(struct _node));
    head->next->next->val = 3;
    //head->next->next->next->val = 4;

    head = list_invert(head);
    printf("%d\n",head->val);
    printf("%d\n",head->next->val);
    printf("%d\n",head->next->next->val);
    //printf("%d\n",head->next->next->next->val);
}

node * list_invert(node * head){
    node * current = head;
    node * prev = NULL;
    node * next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}