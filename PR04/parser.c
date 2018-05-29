/*
    parser.c

    WHAT'S MISSING:
        - Managing strings and labels correctly (M)
        - Errors (M)
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"
#include "optable.c"

#define  OPTABLE     optable_find(curr_word)
#define  FOR_ASSIGN  for (int i = 0; i < 3; i++)

static int type_cmp(OperandType required, OperandType found) {

    int equal = 1;

    if (required == IMMEDIATE) {
        if (found != REGISTER && found != BYTE1) equal = 0;
    } else if (required == ADDR2) {
        if (found != LABEL && found != BYTE2 && found != NEG_NUMBER) equal = 0;
    } else if (required == ADDR3) {
        if (found != LABEL && found != BYTE3 && found != NEG_NUMBER) equal = 0;
    } else if (required != found) equal = 0;

    return equal;
}

static int equal_types(OperandType required[], OperandType found[]) {

    if (required[0] == (REGISTER | TETRABYTE | NEG_NUMBER)) {
        if (type_cmp(required[1], found[1]) && type_cmp(required[2], found[2])) {
            if (type_cmp(REGISTER, found[0])|| type_cmp(TETRABYTE, found[0]) || type_cmp(NEG_NUMBER, found[0]))
                return 1;
            else return 0;
        } else return 0;
    } else if (required[0] == (TETRABYTE | NEG_NUMBER)) {
        if (type_cmp(required[1], found[1]) && type_cmp(required[2], found[2])) {
            if (type_cmp(TETRABYTE, found[0]) || type_cmp(NEG_NUMBER, found[0]))
                return 1;
            else return 0;
        } else return 0;
    } else {
        int equal = 1;
        for (int i = 0; i < 3; i++) {
            if (!type_cmp(required[i], found[i])) return 0;
        }
        return 1;
    }
}

static OperandType find_type(const char *w) {
    const char *s = w;
    if (*w == '$') {
        w++;
        int is_register = 1;
        while (!*w) {
            if (!isdigit(*w)) {
                is_register = 0;
                break;
            }
        }
        if (is_register) {
            printf("%s is register\n", s);
            return REGISTER;
        }
    }
    else if (isdigit(*w) || *w == '_') {
        int is_number = 1;
        while (!*w) {
            if (!isdigit(*w)) {
                is_number = 0;
                break;
            }
            w++;
        }
        if (is_number) {
            printf("%s is number\n", s);
            return BYTE1;
        } else {
            printf("%s is NOT number\n", s);
        }
    }
    return 0;
}

int check_label(const char *w) {

    if (!(*w == '_' || isalpha(*w)))
        return 0;
    w++;

    while (*w != '\0') {
        if (!(*w == '_' || isalpha(*w) || isdigit(*w)))
            return 0;
        w++;
    }
    return 1;
}

int parse(const char *s /*, SymbolTable al_table, Instruction **instr,
          const char **errptr*/) {
    
    printf("%s\n\n", s);
    char *curr_word = malloc(sizeof(char));
    char *word_pointer = curr_word;
    int word_count = 1, label = 0, operator = 0;
    OperandType operands_required[3],
                operands_found[] = {OP_NONE, OP_NONE, OP_NONE};
    int op_on_first = 0;
    int comment = 0;
    
    do {
        // this block works the current character
        if (!(isblank(*s) || *s == ',' || *s == '\0') || comment) { 
            *word_pointer++ = *s++;
            continue;
        } 
        else if (*s == '*') {
            comment = 1;
            continue;
        }
        else {
            *word_pointer++ = '\0';
            s++;
        }

        // avoids empty string corner case
        if (!(*curr_word)) {
            curr_word = word_pointer;
            continue;
        }

        switch (word_count) {
            case 1:
                if (OPTABLE) {
                    printf("%s está em optable\n", curr_word);
                    operator = 1;
                    FOR_ASSIGN operands_required[i] = OPTABLE->opd_types[i];
                    op_on_first = 1;
                }
                else {
                    printf("%s NÃO está em optable\n", curr_word);
                    if (!check_label(curr_word))
                    printf("nao pode esse label\n"); // ERROR here
                    label = 1; // if first word is no operator, we assume it is a label
                }
                break;
            case 2:
                if (OPTABLE) {
                    printf("%s está em optable\n", curr_word);
                    if (label != 1) printf("erro: 2 operadores\n"); // ERROR here
                    FOR_ASSIGN operands_required[i] = OPTABLE->opd_types[i];
                }
                else {
                    printf("%s NÃO está em optable\n", curr_word);
                    if (operator != 1) printf("ERRO: nenhum operador\n");; // ERROR here
                    if (op_on_first) {
                        if (!(operands_found[0] = find_type(curr_word)))
                        ; // ERROR here;
                    }
                }
                break;
            case 3:
                if (OPTABLE) {
                    // printf("%s está em optable\n", curr_word);
                    // ERROR here;
                }
                else if (op_on_first) {
                    if (!(operands_found[1] = find_type(curr_word)))
                    ; // ERROR here;
                }
                else if (!(operands_found[0] = find_type(curr_word)))
                ; // ERROR here; 
                break;
            case 4:
                if (OPTABLE) {
                    // printf("%s está em optable\n", curr_word);
                    // ERROR here;
                }
                else if (op_on_first) {
                    if (!(operands_found[2] = find_type(curr_word)))
                    ; // ERROR here;
                }
                else if (!(operands_found[1] = find_type(curr_word)))
                ; // ERROR here; 
                break;
            case 5:
                 if (OPTABLE) {
                    // printf("%s está em optable\n", curr_word);
                    // ERROR here;
                }
                else if (op_on_first)
                ; // ERROR here;
                else if (!(operands_found[2] = find_type(curr_word)))
                ; // ERROR here; 
                break;
            default:
                printf("erro: número excessivo de elementos\n");
                break;
        }

        curr_word = word_pointer;
        word_count++;
        
    } while (*(s-1));

    int correct_operands;

    if ((correct_operands = equal_types(operands_required, operands_found))) {
        printf("operands are of correct type\n");
        return 1;
    }
    else {
        printf("operands are NOT of correct type\n");
        return 0;
    }
}

int main() {
    parse("3hello PUSH $4 *sbcwoic");
    printf("\n\n");
    /*parse("MUL $0,$2,$3");
    printf("\n\n");
    parse("DIV $0, 2");*/
    return 0;
}