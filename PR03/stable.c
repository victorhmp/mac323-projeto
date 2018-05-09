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
typedef struct node {
    const char *key;
    EntryData val;    // for test purposes ONLY
    struct node *prev;
} node;

/* Symbol table comprises a single array
   array elements are pointers to the last nodes of each linked list */
typedef struct stable_s {
    node *st[M];    // should * be here?
} *SymbolTable;     // and here?

// How to initialize a symboltable whose node *st[] elements are set to null?
SymbolTable stable_create() {
    SymbolTable a;
    a = malloc((sizeof(node*)+sizeof(int)+sizeof(const char*))*M);     //Is this right?
    for (int i = 0 ; i < M; i++) {
        node *insert = NULL;
        a->st[i] = malloc(sizeof(node));  // Necessary?
        a->st[i] = insert;
    }
    return a;
}

void stable_destroy(SymbolTable table) {
    //free(table->st);      // Think this should be added, but couldn't allocate st
    free(table);
}

InsertionResult stable_insert(SymbolTable table, const char *key) {

    EntryData *check_existence = stable_find(table, key); 
    InsertionResult to_return;
    
    // if there is no equal key in the symbol table
    if (!check_existence) {
        to_return.new = 1;
        // Here, we must assign a value to the EntryData of to_return
    }
    
    int h = hash(key);
    node new_node;
    new_node.key = key;
    //new_node.val = ;      // assign value to node's val
    new_node.prev = table->st[h];
    node *ref = &new_node;
    table->st[h] = ref;

    return to_return;
}

EntryData *stable_find(SymbolTable table, const char *key){
    if (table->st[hash(key)] == NULL) printf("é nulo");
    node *nd = table->st[hash(key)];    // attempts to get key at correct index given by hash function
    while (nd) {
        if (strcmp(nd->key, key) == 0) {
            return &(nd->val);
        }
        nd = nd->prev;      // Is this right?
    }
    printf("não deu\n");
    return NULL;
}

/*
int stable_visit(SymbolTable table, int (*visit)(const char *key, EntryData *data)) {
}*/

// client 
int main() {
    SymbolTable s_table = stable_create();
    stable_insert(s_table, "tchau");
    //printf("1 ok");
    stable_find(s_table, "oi");
    //printf("2 ok");
    stable_find(s_table, "tchau");
    //printf("3 ok");
    //printf("%s\n", s_table->st[0]->key);
    //stable_destroy(s_table);
    return 0;
}