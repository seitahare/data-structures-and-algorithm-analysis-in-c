#include <stdio.h>
#include <stdlib.h>


typedef struct tree_node *TREE_PTR;

struct tree_node {
  int element;
  TREE_PTR left;
  TREE_PTR right;
};

TREE_PTR create_node(int value)
{

  TREE_PTR node = malloc(sizeof(struct tree_node));

  if (node == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }


  node->element = value;

  node->left = NULL;

  node->right = NULL;


  return node;
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

  TREE_PTR root = create_node(10);
  TREE_PTR node5 = create_node(5);
  TREE_PTR node20 = create_node(20);
  TREE_PTR node2 = create_node(2);
  TREE_PTR node7 = create_node(7);


  root->left = node5;
  root->right = node20;

  node5->left = node2;
  node5->right = node7;

  printf("Root: %d\n", root->element);
  printf("Left child: %d\n", root->left->element);
  printf("Right child: %d\n", root->right->element);

  free_tree(root);

  return 0;
}
