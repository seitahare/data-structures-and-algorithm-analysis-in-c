#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node *TREE_PTR;

struct tree_node {
  char element;
  TREE_PTR left;
  TREE_PTR right;
};

TREE_PTR create_node(char value)
{

  TREE_PTR p = malloc(sizeof(struct tree_node));

  if (p == NULL)
    exit(EXIT_FAILURE);

  p->element = value;
  p->left = NULL;
  p->right = NULL;


  return p;
}


#define MAX_SIZE 100

TREE_PTR stack[MAX_SIZE];
int top = -1;


void push(TREE_PTR node)
{
   
  if (top == MAX_SIZE - 1) {
    fprintf(stderr, "Stack overflow\n");
    exit(EXIT_FAILURE);
  }

  stack[++top] = node;

}

TREE_PTR pop(void)
{

  if (top == -1) {
    fprintf(stderr, "Stack undefflow\n");
    exit(EXIT_FAILURE);
  }

  return stack[top--];
}


TREE_PTR build_expression_tree(const char *postfix)
{
  for (int i = 0; postfix[i] != '\0'; i++) {
    char c = postfix[i];


    if (c >= 'a' && c <= 'z') {
      push(create_node(c));
    }

    else if (c == '+' || c == '-' || c == '*' || c == '/') {
      TREE_PTR right = pop();
      TREE_PTR left = pop();

      TREE_PTR op = create_node(c);

      op->left = left;
      op->right = right;

      push(op);

    }
  }

  return pop();
}



void inorder(TREE_PTR node)
{

  if (node == NULL)
    return;

  inorder(node->left);
  printf("%c ", node->element);
  inorder(node->right);
}

void preorder(TREE_PTR node)
{

  if (node == NULL)
    return;

  printf("%c ", node->element);
  preorder(node->left);
  preorder(node->right);

}

void postorder(TREE_PTR node)
{

  if (node == NULL)
    return;

  postorder(node->left);
  postorder(node->right);
  printf("%c ", node->element);

}


void free_tree(TREE_PTR node)
{

  if (node == NULL)
    return;

  free_tree(node->left);
  free_tree(node->right);

  free(node);

}


void inorder_parenthesized(TREE_PTR node)
{

  if (node == NULL)
    return;

  if (node->left == NULL && node->right == NULL) {
    printf("%c", node->element);
    return;
  }

  printf("(");

  inorder_parenthesized(node->left);

  printf(" %c ", node->element);

  inorder_parenthesized(node->right);

  printf(")");

}


int main(void)
{

  const char *postfix = "ab+cde+**";

  TREE_PTR root = build_expression_tree(postfix);

  printf("Inorder: ");
  inorder(root);
  printf("\n");


  printf("Preorder: ");
  preorder(root);
  printf("\n");


  printf("Postorder: ");
  postorder(root);
  printf("\n");


  printf("Parenthesized: ");
  inorder_parenthesized(root);
  printf("\n");


  free_tree(root);

  return 0;

}
