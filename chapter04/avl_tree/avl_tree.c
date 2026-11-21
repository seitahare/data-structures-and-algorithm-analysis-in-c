#include <stdio.h>
#include <stdlib.h>

typedef struct avl_node *AVL_PTR;

struct avl_node {
  int element;
  AVL_PTR left;
  AVL_PTR right;
  int height;
};

int height(AVL_PTR p)
{

  if (p == NULL)
    return -1;

  return p->height;

}

int max(int a, int b)
{

  return a > b ? a : b;

}


AVL_PTR rotate_left(AVL_PTR a)
{
  AVL_PTR b = a->right;

  a->right = b->left;
  b->left = a;

  a->height = max(height(a->left), height(a->right)) + 1;
  b->height = max(height(b->left), height(b->right)) + 1;

  return b;

}

AVL_PTR rotate_right(AVL_PTR a)
{
  AVL_PTR b = a->left;

  a->left = b->right;
  b->right = a;

  a->height = max(height(a->left), height(a->right)) + 1;
  b->height = max(height(b->left), height(b->right)) + 1;

  return b;
}

AVL_PTR avl_insert(int x, AVL_PTR T)
{

  if (T == NULL) {
    T = malloc(sizeof(struct avl_node));

    if (T == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }

    T->element = x;
    T->left = NULL;
    T->right = NULL;
    T->height = 0;

    return T;
  }

  if (x < T->element) {
    T->left = avl_insert(x, T->left);
  }
  else if (x > T->element) {
    T->right = avl_insert(x, T->right);
  }
  else {
    return T;
  }

  T->height = max(height(T->left), height(T->right)) + 1;
  
  int balance = height(T->left) - height(T->right);

  if (balance > 1 && x < T->left->element)
    return rotate_right(T);

  if (balance < -1 && x > T->right->element)
    return rotate_left(T);

  if (balance > 1 && x > T->left->element) {
    T->left = rotate_left(T->left);
    return rotate_right(T);
  }

  if (balance < -1 && x < T->right->element) {
    T->right = rotate_right(T->right);
    return rotate_left(T);
  }

  return T;
}

void preorder(AVL_PTR T)
{

  if (T == NULL)
    return;

  printf("%d ", T->element);

  preorder(T->left);
  preorder(T->right);
}

void free_tree(AVL_PTR T)
{
  if (T == NULL)
    return;

  free_tree(T->left);
  free_tree(T->right);
  free(T);
}

int main(void)
{

  AVL_PTR root = NULL;

  root = avl_insert(10, root);
  root = avl_insert(20, root);
  root = avl_insert(30, root);

  printf("Root: %d\n", root->element);

  printf("Preorder: ");
  preorder(root);
  printf("\n");

  free_tree(root);

  return 0;
}
