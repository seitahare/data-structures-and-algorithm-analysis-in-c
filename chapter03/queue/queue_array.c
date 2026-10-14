#include <stdio.h>
#include <stdlib.h>

typedef int element_type;

struct queue_record {

  unsigned int q_max_size;
  unsigned int q_front;
  unsigned int q_rear;
  unsigned int q_size;
  element_type *q_array;
};

typedef struct queue_record *QUEUE;


int is_empty(QUEUE Q)
{
  return Q->q_size == 0;
}


void make_null(QUEUE Q)
{
  Q->q_size = 0;
  Q->q_front = 1;
  Q->q_rear = 0;
}

unsigned int succ(unsigned int value, QUEUE Q)
{

  if (++value == Q->q_max_size)
    value = 0;

  return value;

}


int is_full(QUEUE Q)
{

  return Q->q_size == Q->q_max_size;

}


void enqueue(element_type x, QUEUE Q)
{
  if (is_full(Q)) {

    exit(EXIT_FAILURE);

  }
  
  else {

    Q->q_size++;
    Q->q_rear = succ(Q->q_rear, Q);
    Q->q_array[Q->q_rear] = x;
  }
}


QUEUE create_queue(unsigned int max_elements)
{

  QUEUE Q;
  Q = malloc(sizeof(struct queue_record));
  
  if (Q == NULL)
    exit(EXIT_FAILURE);

  Q->q_array = malloc(sizeof(element_type) * max_elements);

  if (Q->q_array == NULL) {
    free(Q);
    exit(EXIT_FAILURE);
  }

  Q->q_max_size = max_elements;
  make_null(Q);
  if (max_elements < 2)
    exit(EXIT_FAILURE);

  return Q;
}


void dispose_queue(QUEUE Q)
{

  free(Q->q_array);

  free(Q);
}


element_type dequeue(QUEUE Q)
{

  int deq;

  if (is_empty(Q))
    exit(EXIT_FAILURE);

  deq = Q->q_array[Q->q_front];

  Q->q_size--;

  Q->q_front = succ(Q->q_front, Q);

  return deq;

}


int main(void)
{
    QUEUE Q = create_queue(5);

    enqueue(10, Q);
    enqueue(20, Q);
    enqueue(30, Q);

    printf("%d\n", dequeue(Q));
    printf("%d\n", dequeue(Q));
    printf("%d\n", dequeue(Q));

    dispose_queue(Q);

    return 0;
}
