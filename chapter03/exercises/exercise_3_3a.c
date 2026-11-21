#include <stdio.h>
#include <stdlib.h>


struct node {
  int element;
  struct node *next;

};


typedef struct node *POSITION;
typedef struct node *LIST;


LIST create_list(void)
{

  LIST L = malloc(sizeof(struct node));


  if (L == NULL)
    exit(EXIT_FAILURE);

  L->next = NULL;

  return L;

}


void append(LIST L, int x)
{

  POSITION new_node = malloc(sizeof(struct node));

  if (new_node == NULL)
    exit(EXIT_FAILURE);

  new_node->element = x;
  new_node->next = NULL;

  POSITION p = L;

  while (p->next != NULL) {
    p = p->next;
  }

  p->next = new_node;
}


void swap_adjacent(LIST L, int position)
{
  if (L == NULL || position <  1)
    return;


  POSITION prev = L;


  for (int i = 1; i < position; i++) {
    if (prev->next == NULL)
      return;


    prev = prev->next;
  }

  if (prev->next == NULL || prev->next->next == NULL)
    return;


  POSITION first = prev->next;
  POSITION second = first->next;

  first->next = second->next;
  second->next = first;
  prev->next = second;
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

