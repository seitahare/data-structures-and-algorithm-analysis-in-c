
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 100

typedef struct tree_node *TREE_PTR;

struct tree_node {
    int element;
    TREE_PTR left;
    TREE_PTR right;
};

/* ノード作成 */
TREE_PTR create_node(int x)
{
    TREE_PTR node = malloc(sizeof(struct tree_node));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->element = x;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/* BSTへの挿入 */
TREE_PTR insert(TREE_PTR root, int x)
{
    if (root == NULL)
        return create_node(x);

    if (x < root->element)
        root->left = insert(root->left, x);

    else if (x > root->element)
        root->right = insert(root->right, x);

    return root;
}

/* Preorder: Root -> Left -> Right */
void preorder(TREE_PTR root)
{
    if (root == NULL)
        return;

    printf("%d ", root->element);
    preorder(root->left);
    preorder(root->right);
}

/* Inorder: Left -> Root -> Right */
void inorder(TREE_PTR root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->element);
    inorder(root->right);
}

/* Postorder: Left -> Right -> Root */
void postorder(TREE_PTR root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->element);
}

/* Treeの高さ */
int tree_height(TREE_PTR root)
{
    if (root == NULL)
        return -1;

    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);

    return (left_height > right_height
            ? left_height : right_height) + 1;
}

/* Level-order: Queueを使用 */
void level_order(TREE_PTR root)
{
    if (root == NULL)
        return;

    TREE_PTR queue[QUEUE_SIZE];

    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {

        TREE_PTR current = queue[front++];

        printf("%d ", current->element);

        if (current->left != NULL) {
            if (rear >= QUEUE_SIZE) {
                fprintf(stderr, "Queue capacity exceeded\n");
                exit(EXIT_FAILURE);
            }

            queue[rear++] = current->left;
        }

        if (current->right != NULL) {
            if (rear >= QUEUE_SIZE) {
                fprintf(stderr, "Queue capacity exceeded\n");
                exit(EXIT_FAILURE);
            }

            queue[rear++] = current->right;
        }
    }
}

/* メモリ解放 */
void free_tree(TREE_PTR root)
{
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}

int main(void)
{
    TREE_PTR root = NULL;

    int values[] = {40, 20, 60, 10, 30, 50, 70};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    printf("Preorder:   ");
    preorder(root);
    printf("\n");

    printf("Inorder:    ");
    inorder(root);
    printf("\n");

    printf("Postorder:  ");
    postorder(root);
    printf("\n");

    printf("Level-order:");
    printf(" ");
    level_order(root);
    printf("\n");

    printf("Height: %d\n", tree_height(root));

    free_tree(root);

    return 0;
}

