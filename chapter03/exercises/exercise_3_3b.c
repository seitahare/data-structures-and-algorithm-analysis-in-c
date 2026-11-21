#include <stdio.h>
#include <stdlib.h>


struct node {
  int element;
  struct node *prev;
  struct node *next;
};


typedef struct node *POSITION;
typedef struct node *LIST;


LIST create_list(void)
{

  LIST L = malloc(sizeof(struct node));

  if (L == NULL)
    exit(EXIT_FAILURE);


  L->prev = NULL;
  L->next = NULL;

  return L;
}


void append(LIST L, int x)
{

  POSITION new_node = malloc(sizeof(struct node));

  if (new_node == NULL)
    exit(EXIT_FAILURE);


  POSITION p = L;

  while (p->next != NULL) {
    p = p->next;
  }

  new_node->element = x;
  new_node->prev = p;
  new_node->next = NULL;

  p->next = new_node;

}

void swap_adjacent(LIST L, int position) 
{

  if (L == NULL || position < 1)
    return;


  POSITION first = L->next;

  for (int i = 1; i < position; i++) {
    if (first == NULL)
      return;

    first = first->next;
  }

  if (first == NULL || first->next == NULL)
    return;

  POSITION second = first->next;

  POSITION before = first->prev;
  POSITION after = second->next;

  before->next = second;
  second->prev = before;
 
  second->next = first;
  first->prev = second;

  first->next = after;

  if (after != NULL)
    after->prev = first;
}

void print_list(LIST L)
{

  POSITION p = L->next;

  while (p != NULL) {
    printf("%d ", p->element);
    p = p->next;
  }

  printf("\n");

}


void dispose_list(LIST L)
{
  POSITION p = L;

  while (p != NULL) {
    POSITION next = p->next;
    free(p);
    p = next;
  }
}

int main(void)
{

  LIST L = create_list();

  append(L, 10);
  append(L, 20);
  append(L, 30);
  append(L, 40);

  printf("Before: ");
  print_list(L);

  swap_adjacent(L, 2);

  printf("After: ");
  print_list(L);

  dispose_list(L);

  return 0;
}
