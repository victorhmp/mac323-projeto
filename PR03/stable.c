#include <stdlib.h>
#include <string.h>
#include "stable.h"
#include <stdio.h>
#define  M  2

// hash function
int hash(const char *key) {
    int h = 0;
    for (unsigned int i = 0; i < strlen(key); i++)
      h = (31 * h + (int)key[i]) % M;
    return h;
}

// linked list node: string (key), EntryData(val) and next node pointer
typedef struct Node {
    const char *key;
    EntryData *val;
    struct Node *prev;
} Node;

/* Symbol table comprises a single array
   array elements are pointers to the last nodes of each linked list */
struct stable_s {
    Node *st[M];  
};

SymbolTable stable_create() {
    SymbolTable a = malloc(sizeof(struct stable_s));
    *(a->st) = malloc(sizeof(M * sizeof(Node)));
    for (int i = 0 ; i < M; i++) {
        Node *insert = NULL;
        a->st[i] = insert;
    }

    return a;
}

void stable_destroy(SymbolTable table) {
    free(table);
}

InsertionResult stable_insert(SymbolTable table, const char *key) {
    EntryData *find_result = stable_find(table, key);
    InsertionResult insert_result;

    if (find_result != NULL) {
        insert_result.new = 0;
        insert_result.data = find_result;
    } 
    else {
        insert_result.new = 1;
        
        int h = hash(key);
        Node *new_node = table->st[h];
        new_node = malloc(sizeof(Node));

        char *store = malloc((strlen(key)+1)*sizeof(char));
        int i = 0;
        while(*key != '\0') {
            *store = *key;
            key++;
            store++;
            i++;
        }
        store -= i;
        key -= i;
        new_node->key = store;

        new_node->prev = table->st[h];
        new_node->val = malloc(sizeof(EntryData));
        table->st[h] = new_node;

        insert_result.data = new_node->val;
    }

    return insert_result;
}

EntryData *stable_find(SymbolTable table, const char *key){
    if (table->st[hash(key)] == NULL){
        return NULL;
    }

    Node *nd = table->st[hash(key)];
    while (nd) {
        if (strcmp(nd->key, key) == 0) {
            EntryData *return_pointer = nd->val;
            return return_pointer;
        }
        nd = nd->prev;
    }
    return NULL;
}

void recurs_visit(Node *node, int (*visit)(const char *key, EntryData *data)) {
    visit(node->key, node->val);
    if (node->prev) recurs_visit(node->prev, visit);
}

int stable_visit(SymbolTable table, 
                    int (*visit)(const char *key, EntryData *data)) {
    for (unsigned int i = 0; i < M; i++) {
        /*if (table->st[i] != NULL)
            visit(table->st[i]->key, table->st[i]->val);*/
        if (table->st[i] != NULL) recurs_visit(table->st[i], visit);
    }

    return 1;
}
