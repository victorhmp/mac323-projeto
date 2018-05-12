#include "stable.c"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int length = 0;

// int visit(const char *key, EntryData *data) {
//     int actual_length = length+1;
//     if (key != NULL) {
//         int key_len = strlen(key);
//         printf("%s", key);
//         for (int i = 0; i < actual_length-strlen(key); i++)
//             printf(" ");
//         printf("%d\n", data);
//         return 1;
//     }
// }
int visit(const char *key, EntryData *data) {
    // if (key != NULL) {
        printf("Key: %s, Value: %d\n", key, data->i);
        return 1;
    // }
    return 0;
}

int main(int argc, char** argv) {
    FILE* input_text = fopen(argv[1], "r");
    short file_end = 0;
    char* curr_word = malloc(256 * sizeof(char));
    // int curr_index = 0;
    // int str_length = 0;

    SymbolTable stable = stable_create();

    while(!file_end) {
        char c = fgetc(input_text);
        if (c == EOF) {
            file_end = 1;
            break;
        }
        if (isblank(c) || c == '\n') {
            InsertionResult insert = stable_insert(stable, curr_word);
            // EntryData *data_position = insert.data;
            insert.new ? printf("New key\n") : printf("Duplicate\n");

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

        // stable_visit(stable, visit);
    }

    printf("Test calling stable_visit to print keys in the ST\n");
    stable_visit(stable, visit);
    printf("=====================\n");

    (void)argc;
    return 0;
}
