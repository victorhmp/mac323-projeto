#include "stable.c"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define  UL  unsigned long 

int great_len = 0;

int cmpfunc(const void *a1, const void *b1) {
    Node *a = (Node*)a1, *b = (Node*)b1;
    int c = strcmp(a->key, b->key);
    return c;
    if (c <= 0) return 0;
    else return 1;
}

int visit(const char *key, EntryData *data) {
    printf("%s", key);
    for (UL i = 0; i < great_len-strlen(key)+1; i++) 
        printf(" ");
    printf("%d\n", data->i);
    return 1;
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
    //qsort(a, M, sizeof(Node*), cmpfunc);
    stable_visit(stable, visit);

    (void)argc;
    return 0;
}
