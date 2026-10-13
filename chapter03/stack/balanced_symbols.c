#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


element_type pop_value(STACK S)
{
    if (is_empty(S))
        exit(EXIT_FAILURE);

    return S->stack_array[S->top_of_stack--];
}




int is_balanced(const char *str)
{

  int i;
  STACK S = create_stack(strlen(str) + 1);

  for (i = 0; str[i] != '\0'; i++) {
    char c = str[i];

    if (c == '(' || c == '[' || c == '{') {
      push(c, S);
    }
    else if (c == ')' || c == ']' || c == '}') {
      if (is_empty(S)) {
        dispose_stack(S);
        return 0;
      }

      char opening = pop_value(S);

      if (c == ')' && opening != '(') {
        dispose_stack(S);
        return 0;
      }

      if (c == ']' && opening != '[') {
        dispose_stack(S);
        return 0;
      }

      if (c == '}' && opening != '{') {
        dispose_stack(S);
        return 0;
      }
    }
  }

  int result = is_empty(S);
  dispose_stack(S);
  return result;

}

int main(void)
{
  printf("[()] : %d\n", is_balanced("[()]"));
  printf("[(]) : %d\n", is_balanced("[(])"));
  printf("((() : %d\n", is_balanced("((()"));
  
  return 0;
}
