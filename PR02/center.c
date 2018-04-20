#include "buffer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXTEXTSIZE 1000

char *current_line;
int line_counter = 0;
int is_over = 0;
int chars_in_line = 0;

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

  while(!is_over) {
    chars_in_line =  read_line(input_text, b);
    if (chars_in_line == 0) is_over = 1;
    printf("%d\n", chars_in_line);

    current_line = b->data;
    current_line = trimwhitespace(current_line);
    printf("%s\n", current_line);
  }

  return 0;
}