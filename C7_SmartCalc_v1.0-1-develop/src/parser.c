#include "SmartCalc.h"

//  priority:
//  0 - digits, x
//  1 - +, -
//  2 - *, /, mod
//  3 - ^
//  4 - functions
//  5 - ()

void push(double value, int priority, int type, struct Node **head) {
  struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));

  if (*head == NULL) {
    ptr->value = value;
    ptr->priority = priority;
    ptr->type = type;
    ptr->next = NULL;
    *head = ptr;
  } else {
    ptr->value = value;
    ptr->priority = priority;
    ptr->type = type;
    ptr->next = *head;
    *head = ptr;
  }
}

double pop(struct Node **head) {
  struct Node *ptr;
  int output = 0;
  if (*head == NULL)
    output = -1;
  else {
    output = (*head)->value;
    ptr = *head;
    *head = (*head)->next;
    free(ptr);
  }
  return output;
}

/* void print_stack(struct Node *head) {
  char operators[19][17] = {"NUMBER",
                            "X",
                            "PLUS",
                            "MINUS",
                            "MULTIPLICATION",
                            "DIVISION",
                            "MOD",
                            "POWER",
                            "COS",
                            "SIN",
                            "TAN",
                            "ACOS",
                            "ASIN",
                            "ATAN",
                            "SQRT",
                            "LN",
                            "LOG",
                            "OPENING_BRACKET",
                            "CLOSING_BRACKET"};
  if (head != NULL) {
    struct Node *current = head;

    while (current != NULL) {
      printf("value = %lf, priority = %d, type = %s\n|\n|\nV\n", current->value,
             current->priority, operators[current->type]);

      current = current->next;
    }
  }
} */

void remove_stack(struct Node **head) {
  while (pop(head) != -1) {
    continue;
  }
}

struct Node *reverse_stack(struct Node **Stack) {
  struct Node *Temp = NULL;
  while (*Stack != NULL) {
    push((*Stack)->value, (*Stack)->priority, (*Stack)->type, &Temp);
    pop(Stack);
  }
  return Temp;
}

double parser_for_number(char str[], int *i) {
  char number_str[256] = "";
  strcpy(number_str, "");
  while (*i < (int)strlen(str) && (is_number(str[*i]) || str[*i] == '.')) {
    char temp[2] = {str[*i], '\0'};
    strcat(number_str, temp);
    (*i)++;
  }
  (*i)--;
  return atof(number_str);
}

void parser_for_sign(char c, int *priority, int *type) {
  if (c == '+') {
    *type = PLUS;
    *priority = 1;
  } else if (c == '-') {
    *type = MINUS;
    *priority = 1;
  } else if (c == '*') {
    *type = MULTIPLICATION;
    *priority = 2;
  } else if (c == '/') {
    *type = DIVISION;
    *priority = 2;
  } else {
    *type = POWER;
    *priority = 3;
  }
}

void parser_for_functions(char str[], int *i, int *type) {
  if (str[*i] == 'c') {
    if (is_cos(str, *i)) {
      (*i) += 2;
      *type = COS;
    }
  } else if (str[*i] == 's') {
    if (is_sin(str, *i)) {
      (*i) += 2;
      *type = SIN;
    } else if (*i < (int)strlen(str) - 6 && str[*i + 1] == 'q' &&
               str[*i + 2] == 'r' && str[*i + 3] == 't' && str[*i + 4] == '(') {
      (*i) += 3;
      *type = SQRT;
    }
  } else if (str[*i] == 't') {
    if (is_tan(str, *i)) {
      (*i) += 2;
      *type = TAN;
    }
  } else if (str[*i] == 'a') {
    if (is_cos(str, *i + 1)) {
      *type = ACOS;
    } else if (is_sin(str, *i + 1)) {
      *type = ASIN;
    } else {
      *type = ATAN;
    }
    (*i) += 3;
  } else if (str[*i] == 'l') {
    if (*i < (int)strlen(str) - 4 && str[*i + 1] == 'n' && str[*i + 2] == '(') {
      (*i) += 1;
      *type = LN;
    } else if (*i < (int)strlen(str) - 5 && str[*i + 1] == 'o' &&
               str[*i + 2] == 'g' && str[*i + 3] == '(') {
      (*i) += 2;
      *type = LOG;
    }
  }
}

struct Node *parser(char str[]) {
  struct Node *Stack = NULL;
  int priority = 0;
  int type = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (is_number(str[i])) {
      push(parser_for_number(str, &i), 0, NUMBER, &Stack);
    } else if (str[i] == 'x') {
      push(0, 0, X, &Stack);
    } else if (is_sign(str[i])) {
      if ((str[i] == '+' || str[i] == '-') &&
          (i == 0 || (i > 0 && !is_number(str[i - 1]) && str[i - 1] != 'x' &&
                      str[i - 1] != ')'))) {  // unary sign
        push(0, 0, NUMBER, &Stack);
      }  // возможно стоит упростить условие :
      // (i == 0 || (i > 0 && str[i - 1] == '(')
      parser_for_sign(str[i], &priority, &type);
      push(0, priority, type, &Stack);
    } else if (str[i] == '(') {
      push(0, 5, OPENING_BRACKET, &Stack);
    } else if (str[i] == ')') {
      push(0, 5, CLOSING_BRACKET, &Stack);
    } else if (str[i] == 'm') {
      push(0, 2, MOD, &Stack);
      i += 2;
    } else {
      parser_for_functions(str, &i, &type);
      push(0, 4, type, &Stack);
    }
  }

  Stack = reverse_stack(&Stack);
  return Stack;
}
