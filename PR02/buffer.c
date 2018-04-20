#include "buffer.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_MIN_SIZE 256

char in;
char *insert_pos;

Buffer *buffer_create(size_t member_size) {
  Buffer *buffer = (Buffer*)malloc(sizeof(Buffer));
  if (!buffer) fprintf(stderr, "Memória insuficiente\n");
  
  buffer->buffer_size = BUFFER_MIN_SIZE;
  buffer->member_size = member_size;
  buffer->data = malloc(member_size * BUFFER_MIN_SIZE);
  buffer->p = 0;

  return buffer;
}

void buffer_reset(Buffer *B) {
  free(B->data);
  B->data = malloc(B->member_size * BUFFER_MIN_SIZE);
  B->p = 0;
}

void buffer_destroy(Buffer *B) {
  free(B);
}

void *buffer_push_back(Buffer *B) {
  if (B->p == B->buffer_size) {
    size_t newSize = B->member_size * BUFFER_MIN_SIZE + BUFFER_MIN_SIZE;
    B->data = realloc(B->data, newSize);
  }
  
  return (B->data + B->p++ * B->member_size);
}

int read_line (FILE *input, Buffer *B) {
  buffer_reset(B);
  while((in = (char)fgetc(input)) != EOF) {
    insert_pos = buffer_push_back(B);
    *insert_pos = in;
  }
  return 0;
}

int main() {
  return 0;
}
