#include "../include/stable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define  UI  unsigned int
#define MAX_KEY_NUM 11234

int great_len = 0;
struct table_element {
    const char *key;
    EntryData *data;
};

struct table_element helper[MAX_KEY_NUM];
int num_keys = 0;

int compare(const void *s1, const void *s2) {
    struct table_element *e1 = (struct table_element *)s1;
    struct table_element *e2 = (struct table_element *)s2;

    int key_compare = strcmp(e1->key, e2->key);
    return key_compare;
}

int visit(const char *key, EntryData *data) {
    helper[num_keys].key = key;
    helper[num_keys].data = data;

    num_keys++;
    return 1;
}

void print_in_order(struct table_element *arr) {
    for (int i = 0; i < num_keys; i++) {
        printf("%s", arr[i].key);
        for (UI j = 0; j < great_len-strlen(arr[i].key)+1; j++) 
            printf(" ");
        printf("%d\n", arr[i].data->i);
    }
}

int main(int argc, char** argv) {
    FILE* input_text = fopen(argv[1], "r");
    short file_end = 0;
    char* curr_word = malloc(256 * sizeof(char));

    SymbolTable stable = stable_create();
    int curr_len = 0;

    while(!file_end) {
        char c = fgetc(input_text);
        if (isblank(c) || c == '\n' || c == EOF) {
            InsertionResult insert;
            insert.new = -1;
            insert.data = NULL;
            if (strlen(curr_word) > 0) 
                insert = stable_insert(stable, curr_word);

            if (insert.new == 0) {
                EntryData *old_data = stable_find(stable, curr_word);

                EntryData aux;
                aux = *(old_data);
                aux.i++;
                *(insert.data) = aux;
            }
            else if (insert.new == 1){
                EntryData aux;
                aux.i = 1;
                *(insert.data) = aux;
            }

            if (c == EOF) {
                file_end = 1;
                break;
            }

            free(curr_word);
            curr_word = malloc(256 * sizeof(char));
            curr_word[0] = '\0';
        }
        else {
            int len = strlen(curr_word);
            if (len > great_len)
                great_len = len;
            curr_word[len] = c;
            curr_word[len+1] = '\0';
            if (curr_len > great_len)
                great_len = curr_len;
            continue;
        }
    }
    great_len++;
    stable_visit(stable, visit);
    qsort(helper, num_keys, sizeof(struct table_element), compare);

    print_in_order(helper);

    stable_destroy(stable);
    (void)argc;
    return 0;
}
