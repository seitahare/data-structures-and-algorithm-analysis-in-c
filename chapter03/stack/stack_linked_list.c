#include <stdio.h>
#include <stdlib.h>

typedef int element_type;
typedef struct node *node_ptr;

struct node {
  element_type element;
  node_ptr next;
};

typedef node_ptr STACK;


int is_empty(STACK S)
{
  return S->next == NULL;
}


STACK create_stack(void)
{
  STACK S;

  S = (STACK) malloc(sizeof(struct node));

  if (S == NULL)
    exit(EXIT_FAILURE);

  return S;
}


void make_null(STACK S)
{
  if (S == NULL)
    exit(EXIT_FAILURE);

  S->next = NULL;
}


void push(element_type x, STACK S)
{
  node_ptr tmp_cell;

  tmp_cell = malloc(sizeof(struct node));

  if (tmp_cell == NULL)
    exit(EXIT_FAILURE);

  tmp_cell->element = x;
  tmp_cell->next = S->next;
  S->next = tmp_cell;
}


element_type top(STACK S)
{
  if (is_empty(S))
    exit(EXIT_FAILURE);


  return S->next->element;
}


void pop(STACK S)
{
  node_ptr first_cell;

  if (is_empty(S))
    exit(EXIT_FAILURE);

  first_cell = S->next;

  S->next = first_cell->next;

  free(first_cell);
}


int main(void)
{
    STACK S;

    S = create_stack();
    make_null(S);

    /* Push elements */
    push(10, S);
    push(20, S);
    push(30, S);

    printf("Top: %d\n", top(S));

    /* Pop 30 */
    pop(S);
    printf("Top after pop: %d\n", top(S));

    /* Pop 20 */
    pop(S);
    printf("Top after second pop: %d\n", top(S));

    /* Pop 10 */
    pop(S);
    printf("Is empty: %d\n", is_empty(S));

    /* Release the header node */
    free(S);

    return 0;
}
