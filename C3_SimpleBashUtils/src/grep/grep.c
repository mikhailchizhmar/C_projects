
#include "grep.h"

#include <pcre.h>

#include "../common/arrays.h"
#include "../common/misc.h"

int loadPatternFromFile(s_grep_mode *mode, char *file) {
  int status = 0;
  FILE *f;

  f = fopen(file, "rb");
  if (f) {
    while (1) {
      char ch;
      size_t n = fread(&ch, sizeof(ch), 1, f);
      if (n == 0 || ch == '\n') {
        int sz;
        char *buffer;
        getBuffer(&buffer, &sz);
        char *pattern = (char *)malloc(sz + 1);
        if (pattern != NULL) {
          memcpy(pattern, buffer, sz);
          pattern[sz] = '\0';
          appendToQueue(&mode->patterns, pattern);
        }
        clearBuffer();
        if (n == 0) break;
        continue;
      }
      if (n != '\r') {
        appendToBuffer(ch);
      }
      status = 1;
    }
    fclose(f);
  }

  return status;
}

int subParseARG(s_grep_mode *mode, char *arg) {
  int status = 0;

  if (*arg && mode->flags.e) {
    char *s = getStringData(arg);
    if (s != NULL) {
      appendToQueue(&mode->patterns, s);
      mode->flags.e = 0;
      status = 1;
    }
  } else if (*arg && mode->flags.f) {
    char *s = getStringData(arg);
    if (s != NULL) {
      status = loadPatternFromFile(mode, s);
      mode->flags.f = 0;
      free(s);
    }
  } else if (*arg) {
    char *s = getStringData(arg);
    if (s != NULL) {
      appendToQueue(&mode->filenames, s);
      status = 1;
    }
  }

  return status;
}

int parseARG(s_grep_mode *mode, char *arg) {
  int status = 0;

  while (*arg && !mode->flags.e && !mode->flags.f) {
    status = 1;
    switch (*arg++) {
      case 'v':
        mode->flags.v = 1;
        break;
      case 'n':
        mode->flags.n = 1;
        break;
      case 'c':
        mode->flags.c = 1;
        break;
      case 'o':
        mode->flags.o = 1;
        break;
      case 'E':
      case 'e':
        mode->flags.e = 1;
        break;
      case 's':
        mode->flags.s = 1;
        break;
      case 'h':
        mode->flags.h = 1;
        break;
      case 'i':
        mode->flags.i = 1;
        break;
      case 'l':
        mode->flags.l = 1;
        break;
      case 'f':
        mode->flags.f = 1;
        break;
    }
  }

  if (status && *arg) {
    status = subParseARG(mode, arg);
  }

  return status;
}

int parseCMDline(int argc, char **argv, s_grep_mode *mode) {
  int status = 1;
  if (argc <= 1) {
    status = 0;
  } else {
    for (int i = 1; (i < argc) && status; i++) {
      char ch = argv[i][0];
      if (ch == '-') {
        status = parseARG(mode, &argv[i][1]);
      } else {
        subParseARG(mode, &argv[i][0]);
      }
    }
  }

  if (!mode->filenames.lenght) {
    status = 0;
  }

  if (!mode->patterns.lenght) {
    if (mode->filenames.lenght <= 1) {
      status = 0;
    } else {
      char *data;
      pop_front(&mode->filenames, &data);
      appendToQueue(&mode->patterns, data);
    }
  }

  if (mode->flags.l) {
    mode->flags.c = 0;
  }

  return status;
}

int match(s_grep_mode *mode, char *buffer, char *pattern, int sz, int offset,
          int *start, int *end) {
  int status = 0;
  const char *error;
  int erroffset;

  int len = strlen(pattern);
  if (len == 0) {
    status = 1;
  } else {
    pcre *re = pcre_compile(pattern, mode->flags.i ? PCRE_CASELESS : 0, &error,
                            &erroffset, NULL);
    if (re) {
      int ovector[MAX_MATCH_COUNT];
      int rc =
          pcre_exec(re, 0, buffer, sz, offset, 0, ovector, sizeof(ovector));
      if (rc > 0) {
        *start = ovector[0];
        *end = ovector[1];
        status = 1;
      }
      pcre_free(re);
    }
  }
  return status;
}

int printRow_mode_O(s_grep_mode *mode, char *fileName, int row, char *buffer,
                    int sz) {
  int start;
  int end;
  int status = 0;
  int matched = 0;
  int offset = 0;

  while (1) {
    int minoffset = sz;
    int from = 0, to = 0;
    for (struct qnode *q = mode->patterns.qfront; q != NULL; q = q->next) {
      int s = match(mode, buffer, q->data, sz, offset, &start, &end);
      if (s && end <= minoffset) {
        minoffset = end;
        from = start;
        to = end;
      }
    }
    if (from != to) {
      if (mode->flags.v) break;
      if (!mode->flags.c && !mode->flags.l) {
        if (!mode->flags.h && mode->filenames.lenght > 1) {
          printf("%s:", fileName);
        }
        if (mode->flags.n) {
          printf("%d:", row);
        }
        for (int i = from; i < to; i++) {
          fputc(buffer[i], stdout);
        }
        fputc('\n', stdout);
      }
      offset = minoffset;
      matched = 1;
    } else {
      if (matched) {
        status = 1;
      } else {
        status = mode->flags.v != 0;
      }
      break;
    }
  }
  return status;
}

int printRow_mode_default(s_grep_mode *mode, char *fileName, int row,
                          char *buffer, int sz) {
  int status = 0;
  int matched = 0;

  for (struct qnode *q = mode->patterns.qfront; q != NULL; q = q->next) {
    int start, end;
    matched |= match(mode, buffer, q->data, sz, 0, &start, &end);
  }
  if ((matched && !mode->flags.v) || (!matched && mode->flags.v)) {
    if (mode->flags.c == 0 && mode->flags.l == 0) {
      if (!mode->flags.h && mode->filenames.lenght > 1) {
        printf("%s:", fileName);
      }
      if (mode->flags.n) {
        printf("%d:", row);
      }
      for (int i = 0; i < sz; i++) {
        fputc(buffer[i], stdout);
      }
      fputc('\n', stdout);
    }
    status = 1;
  }
  return status;
}

int printRow(s_grep_mode *mode, char *fileName, int row) {
  int sz;
  char *buffer;
  int status = 0;
  getBuffer(&buffer, &sz);
  sz--;

  if (!mode->flags.last || sz > 0) {
    if (mode->flags.o) {
      status = printRow_mode_O(mode, fileName, row, buffer, sz);
    } else {
      status = printRow_mode_default(mode, fileName, row, buffer, sz);
    }
  }
  return status;
}

int grep(s_grep_mode *mode) {
  int status = 1;

  for (struct qnode *q = mode->filenames.qfront; q != NULL; q = q->next) {
    char *fileName = q->data;
    FILE *f = fopen(fileName, "rb");
    if (f) {
      int row = 0;
      int count = 0;
      while (1) {
        char ch;
        size_t n = fread(&ch, sizeof(ch), 1, f);
        if (n == 0 || ch == '\n') {
          appendToBuffer('\0');
          mode->flags.last = n == 0;
          count += printRow(mode, fileName, ++row);
          clearBuffer();
          if (n == 0) break;
          if (count && mode->flags.l) {
            printf("%s\n", fileName);
            break;
          }
          continue;
        }
        appendToBuffer(ch);
      }
      if (mode->flags.c) {
        if (!mode->flags.h && mode->filenames.lenght > 1) {
          printf("%s:%d\n", fileName, count);
        } else {
          printf("%d\n", count);
        }
      }
      fclose(f);
    } else {
      if (!mode->flags.s) {
        // printf("grep: %s: Нет такого файла или каталога\n", fileName);
      }
    }
  }

  return status;
}

int main(int argc, char **argv) {
  s_grep_mode mode;
  mode.flags.all = 0;
  initQueue(&mode.filenames);
  initQueue(&mode.patterns);
  creatBuffer();
  int status = parseCMDline(argc, argv, &mode);
  if (status) {
    status = grep(&mode);
  }

  if (!status) {
    printf("incorrect cmd line\n");
  }

  clearQueue(&mode.filenames);
  clearQueue(&mode.patterns);
  deleteBuffer();

  return 0;
}
