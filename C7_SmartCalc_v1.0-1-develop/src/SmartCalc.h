#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

enum returns {
  NUMBER,
  X,
  PLUS,
  MINUS,
  MULTIPLICATION,
  DIVISION,
  MOD,
  POWER,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,
  OPENING_BRACKET,
  CLOSING_BRACKET
};

struct Node {
  double value;
  int priority;
  struct Node *next;
  int type;
};

int is_number(char c);
int is_sign(char c);
int is_start_of_function(char c);
int is_mod_before(char str[], int i);
int is_cos(char str[], int i);
int is_sin(char str[], int i);
int is_tan(char str[], int i);
int is_function(char str[], int i);
int only_one_dot(char *str);
int delete_space(char str[]);
int check_brackets(char str[]);
void check_dot(char str[], int i, int *output);
void check_sign(char str[], int i, int *output);
void check_mod(char str[], int i, int *output);
void check_x(char str[], int i, int *output);
void check_number(char str[], int i, int *output);
int validation(char str[]);

void push(double value, int priority, int type, struct Node **head);
double pop(struct Node **head);
void print_stack(struct Node *head);
void remove_stack(struct Node **head);
struct Node *reverse_stack(struct Node **Stack);
double parser_for_number(char str[], int *i);
void parser_for_sign(char c, int *priority, int *type);
void parser_for_functions(char str[], int *i, int *type);
struct Node *parser(char str[]);

struct Node *infix_to_rpn(struct Node **Input);

void one_number_check(struct Node **RPN, double *result, double x, int *flag);
void fill_support(struct Node **RPN, struct Node **Support);
void fill_rpn(struct Node **RPN, struct Node **Support);
void operands_for_signs(struct Node **Support, double *left, double *right,
                        double x);
void operand_for_functions(struct Node **Support, double *operand, double x);
void calc_for_signs(struct Node **RPN, double left, double right);
void calc_for_functions(struct Node **RPN, double operand);
double calculate(char str[], double x);
