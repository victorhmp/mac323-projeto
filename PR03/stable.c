#include <stdlib.h>
#include <string.h>
#include "stable.h"
#include <stdio.h>
#define  M  499

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
            // printf("ATRIBUINDO %c\n", *key);
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

        // printf("Key was inserted\n");
    }

    return insert_result;
}

EntryData *stable_find(SymbolTable table, const char *key){
    if (table->st[hash(key)] == NULL){
        return NULL;
    }

    // attempts to get key at correct index given by hash function
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

int stable_visit(SymbolTable table, 
                    int (*visit)(const char *key, EntryData *data)) {
    for (unsigned int i = 0; i < M; i++) {
        if (table->st[i] != NULL)
            visit(table->st[i]->key, table->st[i]->val);
    }

    return 1;
}
// client
// int main() {
//     SymbolTable s_table = stable_create();
//     printf("ST created.\n");
//     printf("=====================\n");

//     printf("Inserting the same element 'tchau' two times\n");
//     stable_insert(s_table, "tchau");
//     stable_insert(s_table, "tchau");
//     printf("Test 1 ok\n");
//     printf("=====================\n");

//     printf("Looking for element 'oi', which is not in the ST\n");
//     stable_find(s_table, "oi");
//     printf("Test 2 ok\n");
//     printf("=====================\n");

//     printf("Looking for element 'test', which is in the ST\n");
//     stable_insert(s_table, "test");
//     stable_insert(s_table, "test2");
//     stable_find(s_table, "test");
//     printf("Test 3 ok\n");
//     printf("=====================\n");

//     printf("Trying to print a key directly, should print 'test'\n");
//     printf("%s\n", s_table->st[hash("test")]->key);
//     printf("Test 4 ok\n");
//     printf("=====================\n");

//     printf("Test calling stable_visit to print keys in the ST, using our private visit function\n");
//     stable_visit(s_table, visit);
//     printf("=====================\n");

//     stable_destroy(s_table);
//     printf("Destroy ST\n");
//     return 0;
// }

