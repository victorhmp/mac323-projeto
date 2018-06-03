/*
    parse_test.c
*/

#include "parser.c"
#include "buffer.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Variables to control input */
int is_over;
int chars_in_line;
char *current_line = 0;
int lineno = 1;

/* Variables for parser return and alias_table */
int parse_result;
char *errptr = 0;
Instruction *instr = 0;

// void create_alias(SymbolTable *st, InsertionResult insert_res) {
//     InsertionResult insert;
//     insert.new = -1;
//     insert.data = NULL;

//     insert = stable_insert(stable, f.label);
//     if (insert.new == 0)
//         printf("ERROR: Duplicate symbol\n");
//     else {
//         printf("New entry.\n");
//         EntryData alias;
//         alias.opd = f.opds[0];
//         *(insert.data) = alias;

//         printf("Just inserted %s, of type %s with the key %s.\n", insert.data->opd->value.str, get_type_string(insert.data->opd), f.label);
//     }
// }

char *get_type_string(Operand *operand) {
    if (operand->type == REGISTER)
        return "Register";
    if (operand->type == LABEL)
        return "Label";
    if (operand->type == BYTE1)
        return "Number";
    if (operand->type == STRING)
        return "String";
    else
        return "None";
}

int main(int argc, char **argv) {

    FILE *input_text = fopen(argv[1], "r");
    Buffer *b = buffer_create(sizeof(char));
    SymbolTable stable = stable_create();

    while (read_line(input_text, b)) {
        current_line = b->data;

        const char **errptr = malloc(sizeof(const char **));
        Instruction **instr = malloc(sizeof(Instruction **));
        parse_result = parse(current_line, stable, instr, errptr);

        Instruction f;
        if (parse_result == 1) f = **instr;

        if (!parse_result) {

            printf("line %d: %s\n", lineno, current_line);

            long int dist = *errptr-current_line;
            if (lineno < 10) dist += 7;
            else dist += 8;
            for (int i = 0; i < dist; i++) printf(" ");
            printf("^\n");
            printf("%s", get_error_msg());
            
            break;
        }
        else {

            if (parse_result == 2) {
                free(errptr);
                free(instr);
                continue;
            }

            else if (strcmp(f.op->name, "IS") == 0) {
                InsertionResult insert;
                insert.new = -1;
                insert.data = NULL;

                insert = stable_insert(stable, f.label);
                if (insert.new == 0)
                    printf("ERROR: Duplicate symbol\n");
                else {
                    EntryData alias;
                    alias.opd = f.opds[0];
                    *(insert.data) = alias;
                }
            }

            printf("line     = %s\n", current_line);
            if (f.label == NULL) {
                f.label = "n/a";
                printf("label    = n/a\n");
            }
            else {
                char line_label[strlen(f.label) + 1];
                strcpy(line_label, f.label);
                printf("label    = \"%s\"\n", line_label);
            }
            printf("operator = %s\n", f.op->name);
            printf("operands = ");

            for (int i = 0; i < 3; i++) {
                if (f.opds[i]->value.str != NULL) {
                    if (f.opds[i]->value.str[0] == '$') f.opds[i]->value.str++;
                    printf("%s(%s)", get_type_string(f.opds[i]), f.opds[i]->value.str);
                }
                if (i != 2 && f.opds[i+1]->value.str != NULL) printf(", ");
            }
            printf("\n\n");

            free(errptr);
            free(instr);
        }
        lineno++;
    }

    buffer_destroy(b);

    return 0;
}