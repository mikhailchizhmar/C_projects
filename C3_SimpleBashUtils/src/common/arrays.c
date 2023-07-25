
#include "arrays.h"

static int currentIdx = 0;
static int length = 0;
static char* buffer = NULL;

void creatBuffer() {
  currentIdx = 0;
  length = 0;
  buffer = NULL;
}

void deleteBuffer() {
  if (buffer != NULL) {
    free(buffer);
  }
}

void clearBuffer() { currentIdx = 0; }

void getBuffer(char** buf, int* sz) {
  *buf = buffer;
  *sz = currentIdx;
}

void enlarge() {
  if (length == 0) length = 1;
  while (currentIdx >= length) length <<= 1;

  buffer = (char*)realloc(buffer, length);
}

void appendToBuffer(char ch) {
  currentIdx++;
  if (currentIdx >= length) {
    enlarge();
  }
  buffer[currentIdx - 1] = ch;
}