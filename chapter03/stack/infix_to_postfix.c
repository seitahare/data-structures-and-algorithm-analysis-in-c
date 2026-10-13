#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element_type;

struct stack_record {
    unsigned int stack_size;
    int top_of_stack;
    element_type *stack_array;
};

typedef struct stack_record *STACK;

#define EMPTY_TOS (-1)


STACK create_stack(unsigned int max_elements)
{
    STACK S;

    if (max_elements == 0)
        exit(EXIT_FAILURE);

    S = malloc(sizeof(struct stack_record));

    if (S == NULL)
        exit(EXIT_FAILURE);

    S->stack_array = malloc(sizeof(element_type) * max_elements);

    if (S->stack_array == NULL) {
        free(S);
        exit(EXIT_FAILURE);
    }

    S->top_of_stack = EMPTY_TOS;
    S->stack_size = max_elements;

    return S;
}


void dispose_stack(STACK S)
{
    if (S == NULL)
        exit(EXIT_FAILURE);

    free(S->stack_array);
    free(S);
}


int is_empty(STACK S)
{
    return S->top_of_stack == EMPTY_TOS;
}


int is_full(STACK S)
{
    return S->top_of_stack == (int)S->stack_size - 1;
}


void push(element_type x, STACK S)
{
    if (is_full(S))
        exit(EXIT_FAILURE);

    S->stack_array[++S->top_of_stack] = x;
}


element_type top(STACK S)
{
    if (is_empty(S))
        exit(EXIT_FAILURE);

    return S->stack_array[S->top_of_stack];
}


element_type pop_value(STACK S)
{
    if (is_empty(S))
        exit(EXIT_FAILURE);

    return S->stack_array[S->top_of_stack--];
}


void infix_to_postfix(const char *expr)
{

  STACK S = create_stack(strlen(expr) + 1);

  for (int i = 0; expr[i] != '\0'; i++) {
    char c = expr[i];

    if (c >= 'a' && c <= 'z') {
      printf("%c ", c);
    }

    else if (c == '(') {
      push(c, S);
    }

    else if (c == ')') {
    

      while (!is_empty(S) && top(S) != '(') {
        printf("%c", pop_value(S));
      }

      pop_value(S);
    }

    else if (c == '+' || c == '*') {

       
      while (!is_empty(S) &&
             top(S) != '(' &&
             (c == '+' || top(S) == '*')) {

        printf("%c ", pop_value(S));
      }

      push(c, S);
    }
  }

  while (!is_empty(S)) {
    printf("%c ", pop_value(S));
  }

  dispose_stack(S);
}


int main(void)
{
    infix_to_postfix("a*b+c");
    printf("\n");

    infix_to_postfix("a+b+c");
    printf("\n");

    infix_to_postfix("(a+b)*c");
    printf("\n");

    return 0;
}
