#include "../include/buffer.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_MIN_SIZE 256

/* variables used at read_line() */
char in;
char *insert_pos;

Buffer *buffer_create(size_t member_size) {
  Buffer *buffer = (Buffer*)malloc(sizeof(Buffer));
  if (!buffer) fprintf(stderr, "Memória insuficiente\n");
  
  buffer->buffer_size = BUFFER_MIN_SIZE; /* default size of 256 */
  buffer->member_size = member_size;
  buffer->data = malloc(member_size * BUFFER_MIN_SIZE);
  buffer->p = 0;

  return buffer;
}

void buffer_reset(Buffer *B) {
  free(B);
  B = buffer_create(B->member_size); /* maintains member_size */
  B->data = malloc(B->member_size * BUFFER_MIN_SIZE);
  B->p = 0;
}

void buffer_destroy(Buffer *B) {
  free(B);
}

void *buffer_push_back(Buffer *B) {
  /* increases the buffer_size by 256 if necessary */
  if (B->p == B->buffer_size) {
    size_t newSize = B->member_size * (B->buffer_size + BUFFER_MIN_SIZE);
    B->data = realloc(B->data, newSize);
  }
  
  /* pointer arithmetic to return next free position at buffer */
  return ((char*) B->data + B->p++ * B->member_size); /* casts void* to char* to avoid warning */
}

int read_line (FILE *input, Buffer *B) {
  int read_count = 0; /* number of chars read */
  int end_line = 0; /* boolean to check if reached end line */
  buffer_reset(B); /* calls buffer_reset at every read_line call */

  while(!end_line) {
    /* reads next char of input and verifies if it's \n or EOF */
    in = (char)fgetc(input);
    if (in == '\n') {
      end_line = 1;
    }
    if (in == EOF) break;

    /* calls buffer_push_back and inserts char read */
    insert_pos = buffer_push_back(B);
    *insert_pos = in;
    read_count++;
  }

  return read_count;
}
