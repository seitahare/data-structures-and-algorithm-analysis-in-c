#include <stdio.h>
#include <stdlib.h>

typedef struct list_node *NODE_PTR;

struct list_node {
  int element;
  NODE_PTR next;
};

typedef NODE_PTR LIST;

struct hash_tbl {
  unsigned int table_size;
  LIST *the_lists;
};

typedef struct hash_tbl *HASH_TABLE;


HASH_TABLE initialize_table(unsigned int table_size)
{
  HASH_TABLE H;

  H = malloc(sizeof(struct hash_tbl));

  if (H == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(EXIT_FAILURE);
  }

  H->table_size = table_size;

  H->the_lists = malloc(sizeof(LIST) * table_size);

  if (H->the_lists == NULL) {
    fprintf(stderr, "malloc failed\n");
    free(H);
    exit(EXIT_FAILURE);
  }

  for (unsigned int i = 0; i < table_size; i++) {
    H->the_lists[i] = malloc(sizeof(struct list_node));

    if (H->the_lists[i] == NULL) {
      fprintf(stderr, "malloc failed\n");
      exit(EXIT_FAILURE);
    }

    H->the_lists[i]->next = NULL;
  }

  return H;

}

NODE_PTR find(int x, HASH_TABLE H)
{
  unsigned int index = (unsigned int)x % H->table_size;

  NODE_PTR current = H->the_lists[index]->next;

  while (current != NULL) {

    if (current->element == x) {
      return current;
    }

    current = current->next;
  }

  return NULL;
}

void insert(int x, HASH_TABLE H)
{
  if (find(x, H) != NULL) {
    return;
  }

  unsigned int index = (unsigned int)x % H->table_size;

  NODE_PTR new_node = malloc(sizeof(struct list_node));

  if (new_node == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(EXIT_FAILURE);
  }

  new_node->element = x;

  new_node->next = H->the_lists[index]->next;

  H->the_lists[index]->next = new_node;

}


void destroy_table(HASH_TABLE H)
{
  if (H == NULL)
    return;

  for (unsigned int i = 0; i < H->table_size; i++) {

    NODE_PTR current = H->the_lists[i];

    while (current != NULL) {

      NODE_PTR save = current->next;

      free(current);

      current = save;
    }
  }

  free(H->the_lists);

  free(H);
}





int main(void)
{

  HASH_TABLE H = initialize_table(10);

  insert(11, H);
  insert(21, H);
  insert(31, H);
  insert(42, H);

  printf("Find 21: %d\n", find(21, H) != NULL);
  printf("Find 31: %d\n", find(31, H) != NULL);
  printf("Find 99: %d\n", find(99, H) != NULL);

  destroy_table(H);

  return 0;
}

