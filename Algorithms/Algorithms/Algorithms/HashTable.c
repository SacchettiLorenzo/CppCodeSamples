#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct hashFrame {
    int    dim;  // dimensione della tabella
    int* array;  // puntatore alla tabella array[0..dim-1] 
    int currentIndex;
};

typedef struct hashFrame* HashTable;

// pre:  0 < m
// post: ritorna una tabella hash di dimensione m a chiavi positive,
//       inizializzata con tutti -1 che rappresenta l'assenza di chiavi
HashTable newHashTable(int m)
{
    HashTable T = (HashTable)malloc(sizeof(struct hashFrame));
    T->dim = m;
    T->array = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
        T->array[i] = -1;
    T->currentIndex = 0;
    return T;
}

// pre:  0 <= k chiave, 0 < m == dimensione della tabella
// post: ritorna k mod m
int hashFun(int k, int m)
{
    return k % m;
}

// pre:  0 <= k chiave, 0 <= i iterazione, 0 < m == dimensione della tabella
// post: ritorna (hashFun(k, m) + i) mod m
//linear probing va inserito all'interno di un ciclo che aumenta i in relazione a quanta ispezione si vuole fare
int linearProbing(int k, int i, int m)
{
    return (hashFun(k, m) + i) % m;
}

// post: stampa gli elementi di A[0..n-1]
void printarray(int A[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d  ", A[i]);
    printf("\n");
}

int insert(HashTable table, int value) {
    int index = hashFun(value, table->dim);
    table->array[index] = value;
    return index;
}

int main() {
    HashTable table = newHashTable(20);
    int index = insert(table, 10);
    index = insert(table, 21);

    for (size_t i = 0; i < table->dim; i++)
    {
        printf("%d\n", table->array[i]);
    }

    printf("\n");
    printf("%d\n", table->array[hashFun(10,table->dim)]);
}