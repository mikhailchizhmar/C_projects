
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/queue.h"

#define MAX_MATCH_COUNT 120

typedef struct {
  union {
    struct {
      int v : 1;
      int n : 1;
      int c : 1;
      int o : 1;
      int h : 1;
      int i : 1;
      int l : 1;
      int e : 1;
      int s : 1;
      int f : 1;
      int last : 1;
    };
    int all;
  } flags;

  struct qeueue patterns;
  struct qeueue filenames;
} s_grep_mode;