#include <stdio.h>
#include <stdlib.h>


typedef int element_type;

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

void make_null(STACK S)
{
  if (S == NULL)
    exit(EXIT_FAILURE);

  S->top_of_stack = EMPTY_TOS;
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


void pop(STACK S)
{
  if (is_empty(S))
    exit(EXIT_FAILURE);

  --S->top_of_stack;
}

element_type pop_value(STACK S)
{
  if (is_empty(S))
    exit(EXIT_FAILURE);

  return S->stack_array[S->top_of_stack--];
}


int main(void)
{
  STACK S;

  S = create_stack(3);

  printf("Is empty: %d\n", is_empty(S));

  push(10, S);
  push(20, S);
  push(30, S);

  printf("Top: %d\n", top(S));
  printf("Is full: %d\n", is_full(S));

  printf("Popped value: %d\n", pop_value(S));
  printf("Top after pop_value: %d\n", top(S));

  pop(S);
  printf("Top after pop: %d\n", top(S));

  make_null(S);
  printf("Is empty after make_null: %d\n", is_empty(S));

  dispose_stack(S);

  return 0;
}
