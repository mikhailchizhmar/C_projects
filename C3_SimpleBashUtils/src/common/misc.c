
#include "misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isFileExists(char* name) {
  int status;
  FILE* f = fopen(name, "rb");
  if (!f) {
    status = 0;
  } else {
    status = 1;
    fclose(f);
  }
  return status;
}

char* getStringData(char* arg) {
  size_t len = strlen(arg) + 1;
  char* s = (char*)malloc(len + 1);

  if (s != NULL) {
    if (arg[0] == '\'') {
      char* p = strchr(&arg[1], '\'');
      if (p != NULL) {
        *p = '\0';
        strcpy(s, &arg[1]);
      } else {
        free(s);
        s = NULL;
      }
    } else if (arg[0] == '"') {
      char* p = strchr(&arg[1], '"');
      if (p != NULL) {
        *p = '\0';
        strcpy(s, &arg[1]);
      } else {
        free(s);
        s = NULL;
      }
    } else {
      strcpy(s, arg);
    }
  }
  return s;
}
