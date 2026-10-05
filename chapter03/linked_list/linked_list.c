#include <stdio.h>
#include <stdlib.h>

typedef int element_type;


typedef struct node *node_ptr;

struct node {
  element_type element;
  node_ptr next;
};


typedef node_ptr LIST;
typedef node_ptr position;


static void fatal_error(const char *message);
LIST create_list(void);
void print_list(LIST L);

int is_empty(LIST L);
int is_last(position p, LIST L);
position find(element_type x, LIST L);
position find_previous(element_type x, LIST L);
void delete(element_type x, LIST L);
void insert(element_type x, LIST L, position p);
void delete_list(LIST L);


static void fatal_error(const char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}


int is_empty(LIST L)
{
  return L->next == NULL;
}

int is_last(position p, LIST L)
{
  return p->next == NULL;
}


position find(element_type x, LIST L)
{
  position p;

  p = L->next;

  while ((p != NULL) && (p->element != x))
    p = p->next;

  return p;
}


position find_previous(element_type x, LIST L)
{

  position p;

  p = L;

  while ((p->next != NULL) && (p->next->element != x))
    p = p->next;


  return p;
}


void delete(element_type x, LIST L)
{

  position p;
  position tmp_cell;

  p = find_previous(x, L);

  if (p->next != NULL) {
    
    tmp_cell = p->next;

    p->next = tmp_cell->next;

    free(tmp_cell);

  }
}


void insert(element_type x, LIST L, position p)
{
  
  position tmp_cell;

  tmp_cell = (position) malloc(sizeof(struct node));

  if (tmp_cell == NULL) {
    fatal_error("Out of space!!!");
  } else {
    tmp_cell->element = x;

    tmp_cell->next = p->next;

    p->next = tmp_cell;
  }
}


void delete_list(LIST L)
{
  position p;
  position tmp;

  p = L->next;
  L->next = NULL;

  while (p != NULL) {
    tmp = p->next;
    free(p);
    p = tmp;
  }
}


LIST create_list(void)
{
  LIST L;

  L = (LIST) malloc(sizeof(struct node));

  if (L == NULL)
    fatal_error("Out of space!!!");

  L->next = NULL;

  return L;
}


void print_list(LIST L)
{

  position p;

  p = L->next;

  while (p != NULL) {
    printf("%d", p->element);

    if (p->next != NULL)
      printf(" -> ");

    p = p->next;
  }

  printf("\n");

}


int main(void)
{

  LIST L;

  position p;

  L = create_list();

  printf("empty: %d\n", is_empty(L));

  insert(10, L, L);

  p = find(10, L);
  insert(20, L, p);

  p = find(20, L);
  insert(30, L, p);

  printf("list: ");
  print_list(L);

  p = find(20, L);

  if (p != NULL)
    printf("found: %d\n", p->element);


  delete(20, L);

  printf("after delete 20: ");
  print_list(L);

  p = find(30, L);


  if (p != NULL)
    printf("30 is last: %d\n", is_last(p, L));


  delete_list(L);

  printf("empty after delete_list: %d\n", is_empty(L));

  free(L);

  return 0;
}

