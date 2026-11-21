#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node *TREE_PTR;
typedef TREE_PTR SEARCH_TREE;


struct tree_node {
  int element;
  TREE_PTR left;
  TREE_PTR right;
};


SEARCH_TREE make_null(void)
{

  return NULL;

}



TREE_PTR find(int x, SEARCH_TREE T)
{

  if (T == NULL)
    return NULL;

  if (x < T->element)
    return find(x, T->left);
  else if (x > T->element)
    return find(x, T->right);

  else
    return T;
}

TREE_PTR find_min(SEARCH_TREE T)
{
  if (T == NULL)
    return NULL;

  if (T->left == NULL)
    return T;

  return find_min(T->left);
}

TREE_PTR find_max(SEARCH_TREE T)
{
  if (T != NULL) {
    while (T->right != NULL)
      T = T->right;
  }

  return T;

}


TREE_PTR insert(int x, SEARCH_TREE T)
{

  if (T == NULL) {
    T = malloc(sizeof(struct tree_node));

    if (T == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }

    T->element = x;
    T->left = NULL;
    T->right = NULL;
  }

  else if (x < T->element) {
    T->left = insert(x, T->left);
  }
  else if (x > T->element) {
    T->right = insert(x, T->right);
  }

  return T;

}

void free_tree(TREE_PTR node)
{

  if (node == NULL)
    return;

  free_tree(node->left);
  free_tree(node->right);

  free(node);

}

int main(void)
{

  SEARCH_TREE root = make_null();

  root = insert(10, root);
  root = insert(5, root);
  root = insert(20, root);
  root = insert(7, root);
  root = insert(15, root);

  TREE_PTR result = find(7, root);

  if (result != NULL)
    printf("Found: %d\n", result->element);
  else
    printf("Not found\n");

  TREE_PTR min = find_min(root);
  TREE_PTR max = find_max(root);


  if (min != NULL)
    printf("Minimum: %d\n", min->element);

  if (max != NULL)
    printf("Maximum: %d\n", max->element);

  free_tree(root);


  return 0;

}


SEARCH_TREE delete_node(int x, SEARCH_TREE T)
{

  if (T == NULL)
    return NULL;

  if (x < T->element) {
    T->left = delete_node(x, T->left);
  }

  else if (x > T->element) {
    T->right = delete_node(x, T->right);
  }

  else {

    if (T->left != NULL && T->right != NULL) {

      TREE_PTR min = find_min(T->right);

      T->element = min->element;

      T->right = delete_node(min->element, T->right);
    }
    else {

      TREE_PTR child;

      if (T->left != NULL)
        child = T->left;
      else
        child = T->right;

      free(T);

      return child;
    }
  }

  return T;
}
