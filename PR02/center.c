#include "buffer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* variables used at main() */
char *current_line;
int is_over = 0;
int chars_in_line = 0;
int line_count = 1;

/* prints error at stderr when line_length is bigger than col_limit */
void printerror(char* file_name, int error_line) {
  fprintf(stderr, "center: %s: line %d: line too long.\n", file_name, error_line);
}

/* verifies if current_line is completely blank */
int allblank(char *current_line) { 
  char a = (unsigned char) *current_line;
  while(1) {
    a = (unsigned char) *current_line;
    if (a == '\n' || a == EOF || *current_line == 0) break;
    if (!isspace(a)) return 0;
    current_line++;
  }

  return 1;
}

char *trimwhitespace(char *str) {
  char *end;

  /* trim leading spaces */
  while(isspace((unsigned char)*str)) str++;

  if (*str == 0)
    return str;

  /* trim trailing spaces */
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  /* new null terminator */
  *(end + 1) = 0;

  return str; 
}

int main (int argc, char** argv) {
  Buffer *b = buffer_create(sizeof(char));
  FILE* input_text = fopen(argv[1], "r");
  FILE* output_file = fopen(argv[2], "w");
  int col_limit = atoi(argv[3]);

  int line_length = 0;
  int greater_half = 0;

  /* boolean that check if current and last lines are blank */
  int curr_blank = 0;
  int last_blank = 0;

  while(!is_over) {
    chars_in_line = read_line(input_text, b);
    if (chars_in_line == 0) is_over = 1;

    current_line = b->data;
    current_line = trimwhitespace(current_line); /* trims whitespaces at beggining and end of the line */

    line_length = strlen(current_line);

    /* print error when line_length > col_limit */
    if (line_length > col_limit) printerror(argv[1], line_count);
    
    /* calculates the longer half so it centers the line with one extra space to the left if col_limit is odd */
    if (col_limit % 2 == 1) greater_half = 1 + (col_limit/2);
    else greater_half = col_limit/2;

    /* 
      checks for blank lines
      if two lines following lines are blank, does not print a second blank line
     */
    curr_blank = allblank(current_line);
    if (curr_blank == 0 || last_blank == 0) {
      if (curr_blank == 1 && is_over) break;
      fprintf (output_file,"%*s\n", greater_half + line_length / 2, current_line);
    }

    last_blank = curr_blank;
    line_count++;
  }

  (void)argc; /* to avoid warning because of unused argument */
  return 0;
}