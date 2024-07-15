/*****************************************
*  Struttura dati per le liste semplici
*  di interi
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct listEl {
    int            info;
    struct listEl* next;
};

typedef struct listEl* list;

list head(list l) {
    list res = NULL;
    res->info = l->info;
    res->next = NULL;
    return res;
}

list tail(list l) {
    return l->next;
}

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

list deleteAll(int key, list l) {
    if (l == NULL) {
        return NULL;
    }
    else {
        if (l->info == key) {
            list t = tail(l);
            free(l);
            return deleteAll(key, t);
        }
        else {
            l->next = deleteAll(key, tail(l));
            return l;
        }
        
    }
}

list insert(int key, list l) {
    if (l == NULL) {
        list res = Cons(key,NULL);
        return res;
    }
    else {
        l->next = insert(key, l->next);
        return l;
    }
}

list insertAfter(int key, list l, int n) {
    if (l == NULL) {
        list res = Cons(key, NULL);
        return res;
    }
    else {
        if (n == 0) {
            l->next = Cons(key, tail(l));
        }
        else {
            l->next = insertAfter(key, l->next, n - 1);
        }
        
        return l;
    }
}

list fastReverse(list l, list m) {
    if (l == NULL) {
        return m;
    }
    else {
        return fastReverse(l->next, Cons(l->info, m));
        //man mano che fast reverse viene chiamato m accumula l->info mettendoli in testa alla nuova lista
    }
    
}

void corank_inner(list l, int i) {
    l->info = l->info + i;
    if (l->next != NULL) {
        corank_inner(l->next, l->info);
    }
}

//il co-rango di un elemento è la somma di tale elemento e di tutti gli elementi precedenti
int corank(list l) {
    corank_inner(l, 0);
    return 0;
}

//cerca se la lista l è contenuta nella lista m (gli elementi non devono necessariamente essere vicini)
bool subset(list l, list m) {
    if (l == NULL) {
        return true;
    }
    if (m == NULL) {
        return false;
    }
    if (l->info == m->info) {
        return subset(l->next, m->next);
    }
    else {
        return subset(l, m->next);
    }
}

list split(list l) {
    list slow = l;
    list fast = l->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    list half = slow->next;
    slow->next = NULL;
    return half;
}

int main() {

    /*list test1 = Cons(1, Cons(2, Cons(3, Cons(4, Cons(5, Cons(6, Cons(7, NULL)))))));
    printlist(test1);
    deleteAll(4, test1);
    printf("\n");
    printlist(test1);
    list test2 = Cons(1, Cons(2, Cons(3, Cons(4, Cons(5, Cons(6, Cons(7, Cons(4, NULL))))))));
    printlist(test2);
    deleteAll(4, test2);
    printlist(test2);*/

    /*list test3 = NULL;
    test3 = insert(1, test3);
    test3 = insert(3, test3);
    test3 = insert(5, test3);
    test3 = insert(7, test3);
    test3 = insert(9, test3);
    printlist(test3);*/

    /*list test4 = NULL;
    test4 = insert(1, test4);
    test4 = insert(3, test4);
    test4 = insert(5, test4);
    test4 = insert(7, test4);
    test4 = insert(9, test4);
    printlist(test4);
    test4 = insertAfter(100, test4,0);
    printlist(test4);*/

    /*list test5 = NULL;
    test5 = insert(1, test5);
    test5 = insert(3, test5);
    test5 = insert(5, test5);
    test5 = insert(7, test5);
    test5 = insert(9, test5);
    printlist(test5);
    test5 = fastReverse(test5,NULL);
    printlist(test5);*/

    list test6 = Cons(4, Cons(1, Cons(3, Cons(9, Cons(1, Cons(5,NULL))))));
    list half = split(test6);
    printlist(test6);
    printlist(half);

    

    /*list test1 = Cons(3, Cons(-1, Cons(8, Cons(4, Cons(2, Cons(-2, Cons(5, NULL)))))));
    corank(test1);
    printlist(test1);
    printf("\n\n\n");*/

    /*list test2 = Cons(1, Cons(2, Cons(3, Cons(4, Cons(5, Cons(6, Cons(7, NULL)))))));
    list test3 = Cons(4, Cons(5, Cons(6, NULL)));
    printlist(test2);
    printlist(test3);
    printf("%d", subset(test3, test2));*/
    return 0;
}

