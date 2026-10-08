#include <stdio.h>
#include <stdlib.h>


typedef int element_type;

typedef struct node *node_ptr;

struct node {

  element_type element;
  node_ptr previous;
  node_ptr next;

};

typedef node_ptr LIST;
typedef node_ptr position;



LIST create_list(void)
{
  LIST L;

  L = (LIST) malloc(sizeof(struct node));

  if (L == NULL) {
    fprintf(stderr, "Out of space!!!\n");
    exit(EXIT_FAILURE);
  }

  L->previous = NULL;

  L->next = NULL;

  return L;

}


int is_empty(LIST L)
{
  return L->next == NULL;
}


position find(element_type x, LIST L)
{

  position p;

  p = L->next;

  while (p != NULL && p->element != x)
    p = p->next;

  return p;
}


void insert(element_type x, LIST L, position p)
{
  position g;

  g = (position) malloc(sizeof(struct node));

  if (g == NULL) {
    fprintf(stderr, "Out of space!!!\n");
    exit(EXIT_FAILURE);
  }

  g->element = x;

  g->previous = p;
  g->next = p->next;
  
  if (g->next != NULL)
    g->next->previous = g;

  p->next = g;

}
  

void delete(element_type x, LIST L)
{

  position p;
  p = find(x, L);

  if (p == NULL)
    return;

  p->previous->next = p->next;

  if (p->next != NULL) {
    p->next->previous = p->previous;
  }
  
  free(p);
}


void delete_list(LIST L)
{
  position p;
  position dlt;

  p = L->next;

  while (p != NULL) {
    dlt = p->next;
    free(p);
    p = dlt;
  }
  L->next = NULL;
}

void print_reverse(LIST L)
{
  position p;
  p = L->next;

  if (p == NULL)
    return;

  while (p->next != NULL)
    p = p->next;

  while (p != L) {
    printf("%d\n", p->element);
    p = p->previous;
  }
}


int main(void)
{
  LIST L;
  position p;

  L = create_list();

  insert(10, L, L);

  p = find(10, L);

  insert(20, L, p);

  p = find(20, L);

  insert(30, L, p);

  print_reverse(L);

  delete(20, L);

  print_reverse(L);

  delete(30, L);

  print_reverse(L);

  delete_list(L);

  printf("is_empty: %d\n", is_empty(L));

  free(L);

  return 0;
}
