
#include "queue.h"

#include <stdlib.h>

void initQueue(struct qeueue* q) {
  q->lenght = 0;
  q->qfront = NULL;
  q->qrear = NULL;
}

void appendToQueue(struct qeueue* q, char* data) {
  struct qnode* p = (struct qnode*)malloc(sizeof(struct qnode));
  q->lenght++;
  p->data = data;
  p->next = NULL;

  if (q->qrear == NULL) {
    q->qfront = q->qrear = p;
    return;
  }

  q->qrear->next = p;
  q->qrear = p;
}

void clearQueue(struct qeueue* q) {
  struct qnode* p = NULL;
  while (q->qfront) {
    p = q->qfront;
    free(p->data);
    q->qfront = q->qfront->next;
    free(p);
  }
}

void pop_front(struct qeueue* q, char** data) {
  struct qnode* p = q->qfront;
  *data = p->data;
  q->qfront = q->qfront->next;
  q->lenght--;
  free(p);
}

void pop_back(struct qeueue* q, char** data) {
  struct qnode* p = q->qrear;
  *data = p->data;
  q->qrear = NULL;
  q->lenght--;
  free(p);
}