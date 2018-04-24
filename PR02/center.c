#include "buffer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXTEXTSIZE 1000

char *current_line;
int line_counter = 0;
int is_over = 0;
int chars_in_line = 0;
int error_line[10];
int error_count = 0;
int line_count = 1;

void printerror(char** argv) {
  int i = 0;
  while (error_line[i] != 0) {
    fprintf(stderr, "center: %s: line %d: line too long.\n", argv[1], error_line[i++]);
  }
}

char *trimwhitespace(char *str) {
  char *end;

  // Trim leading spaces
  while(isspace((unsigned char)*str)) str++;

  if (*str == 0)
    return str;

  // Trim trailing spaces
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // new null terminator
  *(end + 1) = 0;

  return str; 
}

int main (int argc, char** argv) {
  Buffer *b = buffer_create(sizeof(char));
  FILE* input_text = fopen(argv[1], "r");
  FILE* output_file = fopen(argv[2], "w");
  int col_limit = atoi(argv[3]);

  while(!is_over) {
    chars_in_line =  read_line(input_text, b);
    if (chars_in_line == 0) is_over = 1;
    // printf("%d\n", chars_in_line);

    current_line = b->data;
    current_line = trimwhitespace(current_line);

    int line_length = strlen(current_line);

    // printf("%d\n", line_length);
    int greaterHalf;
    if (col_limit % 2 == 1) greaterHalf = 1+col_limit/2;
    else greaterHalf = col_limit/2;
    fprintf (output_file,"%*s\n", greaterHalf + line_length / 2, current_line);
    if (line_length > col_limit) {
      error_line[error_count] = line_count;
      error_count++;
    }
    line_count++;
  }

  printerror(argv);
  return 0;
}