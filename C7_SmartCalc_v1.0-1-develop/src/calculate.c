#include "SmartCalc.h"

void one_number_check(struct Node **RPN, double *result, double x, int *flag) {
  if (*RPN != NULL && (*RPN)->next == NULL) {
    if ((*RPN)->type == X) {
      *result = x;
    } else {
      *result = (*RPN)->value;
    }
    remove_stack(RPN);
    *flag = 0;
  }  // если введено одно число или x, его и выводим
}

void fill_support(struct Node **RPN, struct Node **Support) {
  while (*RPN != NULL && (*RPN)->type < PLUS) {
    push((*RPN)->value, (*RPN)->priority, (*RPN)->type, Support);
    pop(RPN);
  }  // Пока не встретили оператор, заполняем Support числами и x
}

void fill_rpn(struct Node **RPN, struct Node **Support) {
  while ((*Support) != NULL) {
    push((*Support)->value, (*Support)->priority, (*Support)->type, RPN);
    pop(Support);
  }  // переносим числа и х обратно в RPN
}

void operands_for_signs(struct Node **Support, double *left, double *right,
                        double x) {
  if ((*Support)->type == X) {
    *right = x;
  } else {
    *right = (*Support)->value;
  }
  pop(Support);

  if ((*Support)->type == X) {
    *left = x;
  } else {
    *left = (*Support)->value;
  }
  pop(Support);
}

void operand_for_functions(struct Node **Support, double *operand, double x) {
  if ((*Support)->type == X) {
    *operand = x;
  } else {
    *operand = (*Support)->value;
  }
  pop(Support);
}

void calc_for_signs(struct Node **RPN, double left, double right) {
  if ((*RPN)->type == PLUS) {
    pop(RPN);
    push(left + right, 0, NUMBER, RPN);
  } else if ((*RPN)->type == MINUS) {
    pop(RPN);
    push(left - right, 0, NUMBER, RPN);
  } else if ((*RPN)->type == MULTIPLICATION) {
    pop(RPN);
    push(left * right, 0, NUMBER, RPN);
  } else if ((*RPN)->type == DIVISION) {
    pop(RPN);
    push(left / right, 0, NUMBER, RPN);
  } else if ((*RPN)->type == MOD) {
    pop(RPN);
    push(fmod(left, right), 0, NUMBER, RPN);
  } else if ((*RPN)->type == POWER) {
    pop(RPN);
    push(pow(left, right), 0, NUMBER, RPN);
  }
}

void calc_for_functions(struct Node **RPN, double operand) {
  if ((*RPN)->type == COS) {
    pop(RPN);
    push(cos(operand), 0, NUMBER, RPN);
  } else if ((*RPN)->type == SIN) {
    pop(RPN);
    push(sin(operand), 0, NUMBER, RPN);
  } else if ((*RPN)->type == TAN) {
    pop(RPN);
    push(tan(operand), 0, NUMBER, RPN);
  } else if ((*RPN)->type == ACOS) {
    pop(RPN);
    push(acos(operand), 0, NUMBER, RPN);
  } else if ((*RPN)->type == ASIN) {
    pop(RPN);
    push(asin(operand), 0, NUMBER, RPN);
  } else if ((*RPN)->type == ATAN) {
    pop(RPN);
    push(atan(operand), 0, NUMBER, RPN);
  } else if ((*RPN)->type == SQRT) {
    pop(RPN);
    push(sqrt(operand), 0, NUMBER, RPN);
  } else if ((*RPN)->type == LN) {
    pop(RPN);
    push(log(operand), 0, NUMBER, RPN);
  } else if ((*RPN)->type == LOG) {
    pop(RPN);
    push(log10(operand), 0, NUMBER, RPN);
  }
}

double calculate(char str[], double x) {
  double result = 0, left_operand = 0, right_operand = 0, operand = 0;
  struct Node *Support = NULL, *Input = NULL, *RPN = NULL;
  int flag = 1;

  Input = parser(str);
  RPN = infix_to_rpn(&Input);
  one_number_check(&RPN, &result, x, &flag);

  while (RPN != NULL && flag) {
    fill_support(&RPN, &Support);

    if (RPN->type >= PLUS && RPN->type <= POWER) {
      operands_for_signs(&Support, &left_operand, &right_operand, x);
      calc_for_signs(&RPN, left_operand, right_operand);
    } else {
      operand_for_functions(&Support, &operand, x);
      calc_for_functions(&RPN, operand);
    }

    fill_rpn(&RPN, &Support);
    one_number_check(&RPN, &result, x, &flag);
  }

  return result;
}