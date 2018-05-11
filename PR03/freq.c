#include "stable.c"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int length = 0;

int visit(const char *key, EntryData *data) {
    int actual_length = length+1;
    if (key != NULL) {
        int key_len = strlen(key);
        //printf("Key: %s, Value: \n", key);
        printf("%s", key);
        for (int i = 0; i < actual_length-strlen(key); i++)
            printf(" ");
        printf("?(Value)");
        return 1;
    }
}

int main(int argc, char** argv) {
    FILE* input_text = fopen(argv[1], "r");
    short file_end = 0;
    char* curr_word = malloc(100 * sizeof(char));
    int curr_index = 0;
    int curr_length = 0;

    SymbolTable stable = stable_create();
    while(!file_end){
        char in = (char)fgetc(input_text);
        if (in == EOF) {
            file_end = 1;
            break;
        }
        else if (!isblank(in)) {
            curr_word[curr_index++] = in;
            curr_length++;
        }
        else {
            EntryData *old_data = stable_find(stable, curr_word);
            InsertionResult ir = stable_insert(stable, curr_word);

            *(ir.data) = *(old_data);
            *(ir.data)++;

            free(curr_word);
            char* curr_word = malloc(100 * sizeof(char));
            curr_index = 0;

            if (curr_length > length) 
                length = curr_length;
            curr_length = 0;
        }
    }

    printf("Test calling stable_visit to print keys in the ST\n");
    stable_visit(stable, visit);
    printf("=====================\n");
}
