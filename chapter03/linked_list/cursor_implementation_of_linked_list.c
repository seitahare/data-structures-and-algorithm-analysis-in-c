#include <stdio.h>
#include <stdlib.h>

#define SPACE_SIZE 11

typedef unsigned int node_ptr;
typedef int element_type;



struct node {
  element_type element;
  node_ptr next;
};

typedef node_ptr LIST;
typedef node_ptr position;


struct node CURSOR_SPACE[SPACE_SIZE];


void initialize_cursor_space(void)
{

  unsigned int i;

  for (i = 0; i < SPACE_SIZE - 1; i++) {
    CURSOR_SPACE[i].next = i + 1;
  }

  CURSOR_SPACE[SPACE_SIZE - 1].next = 0;
}


LIST create_list(void)
{

  LIST L;

  L = cursor_alloc();

  if (L == 0)
    exit(EXIT_FAILURE);

  CURSOR_SPACE[L].next = 0;
  CURSOR_SPACE[L].element = 0;

  return L;
}


position cursor_alloc(void)
{

  position p;

  p = CURSOR_SPACE[0].next;

  CURSOR_SPACE[0].next = CURSOR_SPACE[p].next;

  return p;
}

void cursor_free(position p)
{
  CURSOR_SPACE[p].next = CURSOR_SPACE[0].next;
  CURSOR_SPACE[0].next = p;
}


int is_empty(LIST L)
{
  return CURSOR_SPACE[L].next == 0;
}


int is_last(position p, LIST L)
{
  return CURSOR_SPACE[p].next == 0;
}


position find(element_type x, LIST L)
{

  position p;

  p = CURSOR_SPACE[L].next;

  while (p != 0 && CURSOR_SPACE[p].element != x)
  {
    p = CURSOR_SPACE[p].next;
  }

  return p;

}


position find_previous(element_type x, LIST L)
{

  position p;

  p = L;

  while (CURSOR_SPACE[p].next != 0 && CURSOR_SPACE[CURSOR_SPACE[p].next].element != x)
    p = CURSOR_SPACE[p].next;

  return p;
}


void delete(element_type x, LIST L)
{

  position p;
  position tmp_cell;

  p = find_previous(x, L);

  if (is_last(p, L))
    return;

  tmp_cell = CURSOR_SPACE[p].next;

  CURSOR_SPACE[p].next = CURSOR_SPACE[tmp_cell].next;

  cursor_free(tmp_cell);

}

void insert(element_type x, LIST L, position p)
{
  position tmp_cell;

  tmp_cell = cursor_alloc();

  if (tmp_cell == 0)
    exit(EXIT_FAILURE);

  CURSOR_SPACE[tmp_cell].element = x;
  CURSOR_SPACE[tmp_cell].next = CURSOR_SPACE[p].next;
  CURSOR_SPACE[p].next = tmp_cell;

}


int main(void)
{
  position p;
  LIST L;

  initialize_cursor_space();

  L = create_list();

  insert(10, L, L);

  p = find(10, L);

  insert(20, L, p);

  p = find(20, L);

  printf("Position of 20: %u\n", p);

  delete(10, L);

  p = find(10, L);

  printf("Position of 10 after deletion: %u\n", p);

  insert(30, L, L);

  return 0;

}


