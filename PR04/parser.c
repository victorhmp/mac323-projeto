/*
    parser.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"
#include "optable.c"

int parse(const char *s /*, SymbolTable alias_table, Instruction **instr,
          const char **errptr*/) {

    char *curr_word = malloc(sizeof(char));
    char *word_pointer = curr_word;
    int keep = 1;
    
    do {
        if (!isblank(*s) && *s != '\0') { 
            *word_pointer++ = *s++;
            continue;
        } 
        else {
            *word_pointer++ = '\0';
            s++;
        }

        if (!(*curr_word)) continue;

        if (!optable_find(curr_word)) {
            printf("%s NÃO está em optable\n", curr_word);
        } 
        else {
            printf("%s está em optable\n", curr_word);
        }

        curr_word = word_pointer;
    } while (*(s-1));

    return 0;
}

int main() {
    parse("MUL hello ADD cu cu RET   ");
    return 0;
}