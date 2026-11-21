#include <stdio.h>
#include <stdlib.h>

typedef struct splay_node *splay_ptr;

typedef int element_type;

struct splay_node {
  element_type element;
  splay_ptr left;
  splay_ptr right;
  splay_ptr parent;
};

typedef splay_ptr SPLAY_PTR;

void rotate_right(SPLAY_PTR *root, SPLAY_PTR p)
{

  SPLAY_PTR x = p->left;

  p->left = x->right;

  if (x->right != NULL)
    x->right->parent = p;

  x->parent = p->parent;

  if (p->parent == NULL)
    *root = x;
  else if (p == p->parent->left)
    p->parent->left = x;
  else
    p->parent->right = x;

  x->right = p;
  p->parent = x;
}

void rotate_left(SPLAY_PTR *root, SPLAY_PTR p)
{
  SPLAY_PTR x = p->right;

  p->right = x->left;

  if (x->left != NULL)
    x->left->parent = p;

  x->parent = p->parent;

  if (p->parent == NULL)
    *root = x;
  else if (p == p->parent->left)
    p->parent->left = x;
  else
    p->parent->right = x;

  x->left = p;
  p->parent = x;
}

void splay(SPLAY_PTR *root, SPLAY_PTR x)
{

  while (x->parent != NULL) {

    SPLAY_PTR p = x->parent;
    SPLAY_PTR g = p->parent;

    if (g == NULL) {
      if (p->left == x)
        rotate_right(root, p);
      else
        rotate_left(root, p);
    }

    else if (g->left == p && p->left == x) {
      rotate_right(root, g);
      rotate_right(root, p);
    }

    else if (g->right == p && p->right == x) {
      rotate_left(root, g);
      rotate_left(root, p);
    }

    else if (g->left == p && p->right == x) {
      rotate_left(root, p);
      rotate_right(root, g);
    }

    else {
      rotate_right(root, p);
      rotate_left(root, g);

    }
  }
}


SPLAY_PTR splay_find(SPLAY_PTR *root, int x)
{

  SPLAY_PTR current = *root;

  while (current != NULL) {

    if (x < current->element)
      current = current->left;

    else if (x > current->element)
      current = current->right;

    else {
      splay(root, current);
      return current;
    }
  }

  return NULL;
}

SPLAY_PTR create_node(int x)
{

  SPLAY_PTR node = malloc(sizeof(struct splay_node));

  if (node == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  node->element = x;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;


  return node;
}

void bst_insert_for_test(SPLAY_PTR *root, int x)
{

  SPLAY_PTR parent = NULL;
  SPLAY_PTR current = *root;

  while (current != NULL) {
    parent = current;

    if (x < current->element)
      current = current->left;
    else if (x > current->element)
      current = current->right;
    else 
      return;
  }

  SPLAY_PTR node = create_node(x);
  node->parent = parent;

  if (parent == NULL)
    *root = node;
  else if (x < parent->element)
    parent->left = node;
  else
    parent->right = node;
}


int splay_delete(SPLAY_PTR *root, int x)
{
  SPLAY_PTR target = splay_find(root, x);

  if (target == NULL)
    return 0;

  SPLAY_PTR p = target->left;
  SPLAY_PTR q = target->right;

  if (p != NULL)
    p->parent = NULL;

  if (q != NULL)
    q->parent = NULL;

  free(target);

  if (p == NULL)
    *root = q;

  else {
    *root = p;
    SPLAY_PTR max_node = p;
    while (max_node->right != NULL) {
      max_node = max_node->right;
    }
    splay(root, max_node);
  }

  (*root)->right = q;

  if (q != NULL)
    q->parent = *root;

  return 1;
}






int main(void)
{

  SPLAY_PTR root = NULL;

  bst_insert_for_test(&root, 30);
  bst_insert_for_test(&root, 10);
  bst_insert_for_test(&root, 20);

  printf("Before: Root = %d\n", root->element);

  SPLAY_PTR result = splay_find(&root, 20);

  if (result != NULL) {
    printf("Found: %d\n", result->element);
    printf("After: Root = %d\n", root->element);
    printf("Left = %d\n", root->left->element);
    printf("Right = %d\n", root->right->element);
  }

  return 0;

}
