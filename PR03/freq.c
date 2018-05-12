#include "stable.c"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int visit(const char *key, EntryData *data) {
    printf("Key: %s, Value: %d\n", key, data->i);
    return 1;
}

int main(int argc, char** argv) {
    FILE* input_text = fopen(argv[1], "r");
    short file_end = 0;
    char* curr_word = malloc(256 * sizeof(char));

    SymbolTable stable = stable_create();

    while(!file_end) {
        char c = fgetc(input_text);
        if (isblank(c) || c == '\n' || c == EOF) {
            InsertionResult insert = stable_insert(stable, curr_word);
            insert.new ? printf("New key\n") : printf("Duplicate\n");

            if (!insert.new) {
                EntryData *old_data = stable_find(stable, curr_word);

                EntryData aux;
                aux = *(old_data);
                aux.i++;
                *(insert.data) = aux;
            }
            else {
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
            curr_word[len] = c;
            curr_word[len+1] = '\0';
            continue;
        }
    }

    printf("Test calling stable_visit to print keys in the ST\n");
    stable_visit(stable, visit);
    printf("=====================\n");

    (void)argc;
    return 0;
}
