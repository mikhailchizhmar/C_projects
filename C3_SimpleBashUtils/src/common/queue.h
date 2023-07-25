
#pragma once

struct qnode {
  struct qnode* next;
  char* data;
};

struct qeueue {
  int lenght;
  struct qnode *qfront, *qrear;
};

void initQueue(struct qeueue* q);
void appendToQueue(struct qeueue* q, char* data);
void pop_front(struct qeueue* q, char** data);
void pop_back(struct qeueue* q, char** data);
void clearQueue(struct qeueue* q);