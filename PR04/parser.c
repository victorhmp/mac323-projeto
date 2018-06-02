/*
    parser.c

    LINES 66, 67
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"
#include "optable.c"
#include "stable.c"
#include "error.c"

#define  OPTABLE     optable_find(curr_word)
#define  FOR_ASSIGN  for (int i = 0; i < 3; i++)

// auxiliary function
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

// check if required and found types match
static int equal_types(OperandType required[], OperandType found[]) {

    if (required[0] == (REGISTER | TETRABYTE | NEG_NUMBER)) {
        if (type_cmp(required[1], found[1]) && type_cmp(required[2], found[2])) {
            if (type_cmp(REGISTER, found[0]) || type_cmp(TETRABYTE, found[0]) || type_cmp(NEG_NUMBER, found[0]))
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

// returns input's type or zero if it has no type
static OperandType find_type(const char *w, SymbolTable al_table) {

    EntryData *data = stable_find(al_table, w);

    if (data) {
        // não funciona porque não manipulou a EntryData
        if (data->opd == NULL) return LABEL;
        else if (*(data->opd->value.str) == '\"') return STRING;
        else return data->opd->type;
    }

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
            //printf("%s is register\n", s);
            return REGISTER;
        }
    }
    else if (isdigit(*w) || *w == '-') {
        int is_number = 1;
        while (!*w) {
            if (!isdigit(*w)) {
                is_number = 0;
                break;
            }
            w++;
        }
        if (is_number) {
            //printf("%s is number\n", s);
            return BYTE1;
        }
    }
    return 0;
}

// check if label matches required standards 
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

int parse(const char *s, SymbolTable al_table, Instruction **instr,
          const char **errptr) {

    char *curr_word = malloc(sizeof(char*)),
         *word_pointer = curr_word;

    int word_count = 1,                 
        label = 0,                  // 1 if instruction contains a label
        operator = 0,               // 1 if operator is found
        op_on_first = 0,            // 1 if first string is operator, not label  
        comment = 0,                // 1 if remaining characters are a comment (marked by *)
        str = 0;                    // 1 if operand is a string

    OperandType operands_required[3], 
                operands_found[] =
                {OP_NONE, OP_NONE, OP_NONE};

    // Instruction struct to be returned at the end of the function
    Instruction a;
    a.label = NULL;
    a.opds[0] = malloc(sizeof(Operand));
    a.opds[1] = malloc(sizeof(Operand));
    a.opds[2] = malloc(sizeof(Operand));
    
    do {

        // Simply works the current character (checks end, comment, etc.)
        if (!(isblank(*s) || *s == ',' || *s == '\0') || comment) { 
            if (*s == '*')
                comment = 1;
            *word_pointer++ = *s++;
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

        // parsing depends on the word count.
        // OPTABLE == true means that current word is an operator 
        switch (word_count) {

            // first word: either a label or an operator
            case 1:
                if (OPTABLE) {

                    operator = 1;

                    // assigns required operands for later check
                    FOR_ASSIGN operands_required[i] = OPTABLE->opd_types[i]; 
                    op_on_first = 1;

                    // instr operator is the one returned by optable_find()
                    a.op = OPTABLE;                                       
                }
                else {

                    // check if label matches required standards
                    // if it doesn't, then the instruction is invalid
                    if (!check_label(curr_word)) {  
                        set_error_msg("wrong label format\n");
                        *errptr = s-strlen(curr_word);
                        return 0;
                    }
                    label = 1;
                          
                    // char label_to_instr[strlen(curr_word)+1];                
                    a.label = curr_word;
                    *instr = &a;
                }
                break;

            // second word: either an operator (if) or an operand (else)
            case 2:

                if (OPTABLE) {

                    // if second word is an operator, than the first one must be a label
                    if (label != 1) {
                        *errptr = s-strlen(curr_word); // ERROR here
                        set_error_msg("misplaced operator\n");
                        return 0;
                    }

                    // assigns required operands for later check
                    FOR_ASSIGN operands_required[i] = OPTABLE->opd_types[i];
                    a.op = OPTABLE;
                }
                else {

                    // if first and second words are not operators, instruction is invalid
                    if (operator != 1) {
                        set_error_msg("no operator found\n");
                        *errptr = s-strlen(curr_word); // ERROR here
                        return 0;
                    }

                    // find_type() returns 0 if word has no type (error)
                    if (!(operands_found[0] = find_type(curr_word, al_table))) {
                        set_error_msg("operand has no type\n");
                        *errptr = s-strlen(curr_word);
                        return 0; // ERROR here;
                    }

                    Operand op = {operands_found[0], };
                    op.value.str = curr_word;
                    *a.opds[0] = op;
                }
                break;

            /* from third word on: if it's an operator, instruction is invalid */

            // if operator was given in the first word, third word is the second operand
            // otherwise, it is the first one
            case 3:
                if (OPTABLE) {
                    set_error_msg("misplaced operator\n");
                    *errptr = s-strlen(curr_word);
                    return 0;// ERROR here;
                }
                else if (op_on_first) {

                    if (!(operands_found[1] = find_type(curr_word, al_table))) {
                        set_error_msg("operand has no type\n");
                        *errptr = s-strlen(curr_word);
                        return 0; // ERROR here;
                    }

                    Operand op = {operands_found[1], };
                    op.value.str = curr_word;
                    *a.opds[1] = op;
                }
                else {
                    if (!(operands_found[0] = find_type(curr_word, al_table))) {
                        set_error_msg("operand has no type\n");
                        *errptr = s-strlen(curr_word);
                        return 0; // ERROR here; 
                    }

                    Operand op = {operands_found[0], };
                    op.value.str = curr_word;
                    *a.opds[0] = op;
                }
                break;

            // if operator was given in the first word, third word is the third operand
            // otherwise, it is the second one
            case 4:
                if (OPTABLE) {
                    set_error_msg("misplaced operator\n");
                    *errptr = s-strlen(curr_word);
                    return 0;// ERROR here;
                }
                else if (op_on_first) {

                    if (!(operands_found[2] = find_type(curr_word, al_table))) {
                        set_error_msg("operand has no type\n");
                        *errptr = s-strlen(curr_word);
                        return 0; // ERROR here;
                    }
   
                    Operand op = {operands_found[2], };
                    op.value.str = curr_word;
                    *a.opds[2] = op;
                }
                else {

                    if (!(operands_found[1] = find_type(curr_word, al_table))) {
                        set_error_msg("operand has no type\n");
                        *errptr = s-strlen(curr_word);
                        return 0; // ERROR here; 
                    }
  
                    Operand op = {operands_found[1], };
                    op.value.str = curr_word;
                    *a.opds[1] = op;
                }
                break;

            // if operator was given in the first word, there is an error
            // otherwise, it is the third operand
            case 5:
                 if (OPTABLE) {
                    set_error_msg("misplaced operator\n");
                    *errptr = s-strlen(curr_word);
                    return 0;// ERROR here;
                }
                else if (op_on_first) {   // forth operand: error
                    set_error_msg("number of elements exceded\n");
                    *errptr = s-strlen(curr_word);
                    return 0; // ERROR here;
                }
                else {

                    if (!(operands_found[2] = find_type(curr_word, al_table))) {
                        set_error_msg("operand has no type\n");
                        *errptr = s-strlen(curr_word);
                        return 0; // ERROR here;
                    }
           
                    Operand op = {operands_found[2], };
                    op.value.str = curr_word;
                    *a.opds[2] = op;
                }
                break;

            // instruction longer than 6 words is invalid (exception: strings)
            default:
                set_error_msg("number of elements exceded\n");
                *errptr = s-strlen(curr_word);
                break;
        }

        // sets variables to a new word
        curr_word = word_pointer;
        word_count++;
        
    } while (*(s-1));

    // check if operands found match the types required by the operator
    int correct_operands;

    if (word_count == 1) {
        return 2;
    }

    if ((correct_operands = equal_types(operands_required, operands_found))) {
        *instr = &a;
        return 1;
    }
    else {
        set_error_msg("expected operand or wrong operand type\n");
        *errptr = s-strlen(curr_word);
        return 0;
    }
}

// int main() {

//     SymbolTable al_table = stable_create();
//     const char** errptr = malloc(sizeof(const char**));

//     Instruction **instr = malloc(sizeof(Instruction**));
//     printf("line     = hey MUL $3 $4 $7\n");
//     parse("hey MUL $3 $4 $7", al_table, instr, errptr);

//     Instruction f = **instr;

//     char attempt4[strlen(f.label)+1];
//     strcpy(attempt4, f.label);

//     char attempt1[strlen(f.opds[0]->value.str)+1];
//     strcpy(attempt1, f.opds[0]->value.str);

//     char attempt2[strlen(f.opds[1]->value.str)+1];
//     strcpy(attempt2, f.opds[1]->value.str);

//     char attempt3[strlen(f.opds[2]->value.str)+1];
//     strcpy(attempt3, f.opds[2]->value.str);

//     printf("label    = \"%s\"\n", attempt4);
//     printf("operando 1: %s\n", attempt1);
//     printf("operando 2: %s\n", attempt2);
//     printf("operando 3: %s\n", attempt3);

//     return 0;
// }