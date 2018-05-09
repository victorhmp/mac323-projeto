#include <stdlib.h>
#include <string.h>
#include "stable.h"
#include <stdio.h>
#define  M  500

// hash function
int hash(const char *key) {
    //printf("hello\n");
    int h = 0;
    for (int i = 0; i < strlen(key); i++)
      h = (31 * h + (int)key) % M;
    return h;
}

// linked list node: string (key), EntryData(val) and next node pointer
typedef struct Node {
    const char *key;
    EntryData val;
    struct Node *prev;
} Node;

/* Symbol table comprises a single array
   array elements are pointers to the last nodes of each linked list */
struct stable_s {
    Node *st[M];  
};

SymbolTable stable_create() {
    // printf("%d\n", sizeof(SymbolTable));
    // printf("%d\n", sizeof(struct stable_s));
    SymbolTable a = malloc(sizeof(struct stable_s));
    // printf("%d\n", sizeof(struct stable_s));
    *(a->st) = malloc(sizeof(M * sizeof(Node)));
    for (int i = 0 ; i < M; i++) {
        Node *insert = NULL;
        a->st[i] = insert;
    }

    return a;
}

void stable_destroy(SymbolTable table) {
    //free(table->st);      // Think this should be added, but couldn't allocate st
    free(table);
}

InsertionResult stable_insert(SymbolTable table, const char *key) {
    EntryData *find_result = stable_find(table, key);
    InsertionResult return_value;

    if (find_result != NULL) {
        return_value.new = 0;
        printf("%lu\n", sizeof(find_result));
        free(find_result);
        return_value.data = malloc(sizeof(EntryData));
    } else {
        return_value.new = 1;
        return_value.data = malloc(sizeof(EntryData));

        int h = hash(key);
        Node new_node;
        new_node.key = key;
        //new_node.val = ;      // assign value to node's val
        new_node.prev = table->st[h];
        Node *ref = &new_node;
        table->st[h] = ref;
    }

    return return_value;
}

EntryData *stable_find(SymbolTable table, const char *key){
    if (table->st[hash(key)] == NULL) printf("é nulo");
    Node *nd = table->st[hash(key)];    // attempts to get key at correct index given by hash function
    while (nd) {
        printf("achou a chave %s\n", key);
        if (strcmp(nd->key, key) == 0) {
            return &(nd->val);
        }
        nd = nd->prev;      // Is this right?
    }
    printf("não achou a chave %s\n", key);
    return NULL;
}

/*
int stable_visit(SymbolTable table, int (*visit)(const char *key, EntryData *data)) {
}*/

// client 
int main() {
    SymbolTable s_table = stable_create();
    stable_insert(s_table, "tchau");
    stable_insert(s_table, "tchau");
    //printf("1 ok");
    //stable_find(s_table, "oi");
    //printf("2 ok");
    //stable_find(s_table, "tchau");
    //printf("3 ok");
    //printf("%s\n", s_table->st[0]->key);
    //stable_destroy(s_table);
    return 0;
}