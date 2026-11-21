#include <stdio.h>
#include <stdlib.h>


typedef struct tree_node *TREE_PTR;

struct tree_node {
  int element;
  TREE_PTR first_child;
  TREE_PTR next_sibling;
};

TREE_PTR create_node(int value)
{

  TREE_PTR node = malloc(sizeof(struct tree_node));

  if (node == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  node->element = value;
  node->first_child = NULL;
  node->next_sibling = NULL;


  return node;
}

void preorder(TREE_PTR node)
{

  if (node == NULL)
    return;

  printf("%d ", node->element);

  TREE_PTR child = node->first_child;

  while (child != NULL) {
    preorder(child);

    child = child->next_sibling;
  }

}


void postorder(TREE_PTR node)
{

  if (node == NULL)
    return;

  TREE_PTR child = node->first_child;

  while (child != NULL) {
    postorder(child);

    child = child->next_sibling;
  }

  printf("%d ", node->element);
}

void free_tree(TREE_PTR node)
{

  if (node == NULL)
    return;


  TREE_PTR child = node->first_child;

  while (child != NULL) {

    TREE_PTR next = child->next_sibling;

    free_tree(child);

    child = next;
  }

  free(node);

}

int main(void)
{
  /*
              10
             /  \
            5    20
           / \
          2   7
  */

  TREE_PTR root = create_node(10);
  TREE_PTR node5 = create_node(5);
  TREE_PTR node20 = create_node(20);
  TREE_PTR node2 = create_node(2);
  TREE_PTR node7 = create_node(7);

  root->first_child = node5;
  node5->next_sibling = node20;

  node5->first_child = node2;
  node2->next_sibling = node7;

  printf("Preorder: ");
  preorder(root);
  printf("\n");


  printf("Postorder: ");
  postorder(root);
  printf("\n");

  free_tree(root);

  return 0;
}


