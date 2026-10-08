#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_ptr;


typedef node_ptr LIST;
typedef node_ptr position;


struct node {
  element_type element;
  node_ptr previous;
  node_ptr next;
};

LIST create_list(void)
{
  LIST L;

  L = (LIST) malloc(sizeof(struct node));

  if (L == NULL)
    exit(EXIT_FAILURE);

  L->next = L;
  L->previous = L;

  return L;
}

int is_empty(LIST L)
{
  return L->next == L;
}

position find(element_type x, LIST L)
{
  position p;

  p = L->next;

  while (p != L && p->element != x)
  {
    p = p->next;
  }

  return p;
}


void insert(element_type x, LIST L, position p)
{
  position new_node;

  new_node = (position) malloc(sizeof(struct node));

  if (new_node == NULL)
    exit(EXIT_FAILURE);

  new_node->element = x;

  new_node->previous = p;
  new_node->next = p->next;

  p->next->previous = new_node;
  p->next = new_node;
}

void delete(element_type x, LIST L)
{
    position p;

    p = find(x, L);

    if (p == L)
      return;

    p->previous->next = p->next;
    p->next->previous = p->previous;

    free(p);
}

void print_reverse(LIST L)
{
  position p;

  p = L->previous;

  while (p != L)
  {
    printf("%d\n", p->element);
    p = p->previous;
  }
}


void delete_list(LIST L)
{
  position p;
  p = L->next;

  position next_node;

  while (p != L)
  {
    next_node = p->next;
    free(p);
    p = next_node;
  }

  L->next = L;
  L->previous = L;
}


int main(void)
{
    LIST L = create_list();

    printf("=== Empty list ===\n");
    printf("is_empty: %d\n", is_empty(L));

    // Insert
    insert(10, L, L);
    insert(20, L, find(10, L));
    insert(30, L, find(20, L));

    printf("\n=== After insertion ===\n");
    print_reverse(L);

    // Delete 20
    delete(20, L);

    printf("\n=== After deleting 20 ===\n");
    print_reverse(L);

    // Delete 30
    delete(30, L);

    printf("\n=== After deleting 30 ===\n");
    print_reverse(L);

    // Delete all elements
    delete_list(L);

    printf("\n=== After delete_list ===\n");
    printf("is_empty: %d\n", is_empty(L));

    // Free header
    free(L);

    return 0;
}
