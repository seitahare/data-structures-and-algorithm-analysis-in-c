#include <stdio.h>
#include <stdlib.h>

typedef int element_type;
typedef unsigned int INDEX;

enum kind_of_entry {
  legitimate, 
  empty, 
  deleted
};

struct hash_entry {
  element_type element;

  enum kind_of_entry info;
};

typedef INDEX position;

typedef struct hash_entry cell;

struct hash_tbl {
  unsigned int table_size;

  cell *the_cells;
};

typedef struct hash_tbl *HASH_TABLE;

HASH_TABLE initialize_table(unsigned int table_size)
{
  if (table_size == 0) {
    fprintf(stderr, "invalid table size\n");
    exit(EXIT_FAILURE);
  }

  HASH_TABLE H;

  H = malloc(sizeof(struct hash_tbl));

  if (H == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(EXIT_FAILURE);
  }

  H->table_size = table_size;

  H->the_cells = malloc(table_size * sizeof(struct hash_entry));

  if (H->the_cells == NULL) {
    fprintf(stderr, "malloc failed\n");
    free(H);
    exit(EXIT_FAILURE);
  }

  for (unsigned int i = 0; i < H->table_size; i++) {

    H->the_cells[i].info = empty;

  }

  return H;
}

position find(element_type key, HASH_TABLE H)
{

  position i = 0;

  position current_pos;

  current_pos = key % H->table_size;

  while (H->the_cells[current_pos].info != empty) {

    if (H->the_cells[current_pos].info == legitimate && 
        H->the_cells[current_pos].element == key) {

      return current_pos;

    }

    i++;

    current_pos += (2 * i - 1);

    current_pos %= H->table_size;

  }

  return current_pos;
}

void insert(element_type key, HASH_TABLE H)
{
  position pos;

  pos = find(key, H);

  if (H->the_cells[pos].info != legitimate) {
    H->the_cells[pos].element = key;
    H->the_cells[pos].info = legitimate;
  }

}

int main(void)
{

  HASH_TABLE H = initialize_table(11);

  insert(27, H);
  insert(38, H);
  insert(49, H);

  printf("%u\n", find(27, H));
  printf("%u\n", find(38, H));
  printf("%u\n", find(49, H));

  free(H->the_cells);
  free(H);

  return 0;
}



