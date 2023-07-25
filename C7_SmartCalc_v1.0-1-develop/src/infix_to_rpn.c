#include "SmartCalc.h"

struct Node *infix_to_rpn(struct Node **Input) {
  struct Node *Ready = NULL;
  struct Node *Support = NULL;

  while (*Input != NULL) {
    if ((*Input)->type == NUMBER || (*Input)->type == X) {
      push((*Input)->value, (*Input)->priority, (*Input)->type, &Ready);
    } else if ((*Input)->type >= PLUS && (*Input)->type <= LOG) {
      while (Support != NULL && Support->type >= PLUS && Support->type <= LOG &&
             Support->priority >= (*Input)->priority) {
        push(Support->value, Support->priority, Support->type, &Ready);
        pop(&Support);
      }
      push((*Input)->value, (*Input)->priority, (*Input)->type, &Support);
    } else if ((*Input)->type == OPENING_BRACKET) {
      push((*Input)->value, (*Input)->priority, (*Input)->type, &Support);
    } else if ((*Input)->type == CLOSING_BRACKET) {
      while (Support->type != OPENING_BRACKET) {
        push(Support->value, Support->priority, Support->type, &Ready);
        pop(&Support);
      }
      pop(&Support);
    }
    pop(Input);
  }

  if (Support != NULL) {
    while (Support != NULL) {
      push(Support->value, Support->priority, Support->type, &Ready);
      pop(&Support);
    }
  }

  remove_stack(&Support);
  Ready = reverse_stack(&Ready);
  return Ready;
}