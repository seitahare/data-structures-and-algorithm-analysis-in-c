
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 4
#define MIN_LEAF_KEYS 2
#define MIN_CHILDREN 2

typedef struct b_tree_node *BTREE_PTR;

struct b_tree_node {
    int is_leaf;

    int keys[CAPACITY];
    int key_count;

    BTREE_PTR children[CAPACITY];
    int child_count;
};

/* ---------- Node creation ---------- */

BTREE_PTR create_node(int is_leaf)
{
    BTREE_PTR node = malloc(sizeof(struct b_tree_node));

    if (node == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }

    node->is_leaf = is_leaf;
    node->key_count = 0;
    node->child_count = 0;

    for (int i = 0; i < CAPACITY; i++) {
        node->keys[i] = 0;
        node->children[i] = NULL;
    }

    return node;
}

/* ---------- Find ---------- */

int btree_find(BTREE_PTR root, int x)
{
    if (root == NULL)
        return 0;

    if (root->is_leaf) {
        for (int i = 0; i < root->key_count; i++) {
            if (root->keys[i] == x)
                return 1;
        }

        return 0;
    }

    int i = 0;

    while (i < root->key_count &&
           x >= root->keys[i]) {
        i++;
    }

    return btree_find(root->children[i], x);
}

/* ---------- Boundary keys ---------- */

/* 部分木の最小キーを取得 */
int subtree_min(BTREE_PTR node)
{
    while (!node->is_leaf) {
        node = node->children[0];
    }

    return node->keys[0];
}

/* 内部ノードの境界キーを再計算 */
void update_internal_keys(BTREE_PTR node)
{
    if (node == NULL || node->is_leaf)
        return;

    node->key_count = node->child_count - 1;

    for (int i = 1; i < node->child_count; i++) {
        node->keys[i - 1] =
            subtree_min(node->children[i]);
    }
}

/* ---------- Insert ---------- */

/* 葉にキーを昇順で挿入 */
void insert_into_leaf(BTREE_PTR leaf, int x)
{
    if (leaf == NULL || !leaf->is_leaf)
        return;

    if (leaf->key_count >= CAPACITY)
        return;

    int i = leaf->key_count - 1;

    while (i >= 0 && leaf->keys[i] > x) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }

    leaf->keys[i + 1] = x;
    leaf->key_count++;
}

/* 葉を分割 */
BTREE_PTR split_leaf(BTREE_PTR leaf)
{
    if (leaf == NULL || !leaf->is_leaf)
        return NULL;

    if (leaf->key_count != CAPACITY)
        return NULL;

    BTREE_PTR right = create_node(1);

    for (int i = 0; i < 2; i++) {
        right->keys[i] = leaf->keys[i + 2];
    }

    leaf->key_count = 2;
    right->key_count = 2;

    return right;
}

/* 分割した右ノードを親に接続 */
void insert_child_after(
    BTREE_PTR parent,
    int left_index,
    BTREE_PTR right
)
{
    if (parent == NULL || parent->is_leaf)
        return;

    if (right == NULL ||
        parent->child_count >= CAPACITY)
        return;

    if (left_index < 0 ||
        left_index >= parent->child_count)
        return;

    int insert_index = left_index + 1;

    for (int j = parent->child_count;
         j > insert_index; j--) {

        parent->children[j] =
            parent->children[j - 1];
    }

    parent->children[insert_index] = right;
    parent->child_count++;

    update_internal_keys(parent);
}

/* 内部ノードを分割 */
BTREE_PTR split_internal(BTREE_PTR node)
{
    if (node == NULL || node->is_leaf)
        return NULL;

    if (node->child_count != CAPACITY)
        return NULL;

    BTREE_PTR right = create_node(0);

    right->children[0] = node->children[2];
    right->children[1] = node->children[3];
    right->child_count = 2;

    node->children[2] = NULL;
    node->children[3] = NULL;
    node->child_count = 2;

    update_internal_keys(node);
    update_internal_keys(right);

    return right;
}

/* 再帰的に挿入し、Splitを上へ伝える */
BTREE_PTR insert_recursive(BTREE_PTR node, int x)
{
    if (node->is_leaf) {
        insert_into_leaf(node, x);

        if (node->key_count == CAPACITY)
            return split_leaf(node);

        return NULL;
    }

    int i = 0;

    while (i < node->key_count &&
           x >= node->keys[i]) {
        i++;
    }

    BTREE_PTR right =
        insert_recursive(node->children[i], x);

    if (right != NULL)
        insert_child_after(node, i, right);

    update_internal_keys(node);

    if (node->child_count == CAPACITY)
        return split_internal(node);

    return NULL;
}

/* 挿入の入口 */
void btree_insert(BTREE_PTR *root, int x)
{
    if (root == NULL)
        return;

    if (*root == NULL) {
        *root = create_node(1);
        insert_into_leaf(*root, x);
        return;
    }

    if (btree_find(*root, x))
        return;

    BTREE_PTR right = insert_recursive(*root, x);

    if (right != NULL) {
        BTREE_PTR new_root = create_node(0);

        new_root->children[0] = *root;
        new_root->children[1] = right;
        new_root->child_count = 2;

        update_internal_keys(new_root);

        *root = new_root;
    }
}

/* ---------- Delete ---------- */

/* キーや子が不足しているか */
int is_underfull(BTREE_PTR node)
{
    if (node->is_leaf)
        return node->key_count < MIN_LEAF_KEYS;

    return node->child_count < MIN_CHILDREN;
}

/* 兄弟が1つ貸せるか */
int can_lend(BTREE_PTR node)
{
    if (node->is_leaf)
        return node->key_count > MIN_LEAF_KEYS;

    return node->child_count > MIN_CHILDREN;
}

/* 左の兄弟から借りる */
void borrow_from_left(BTREE_PTR parent, int index)
{
    BTREE_PTR left = parent->children[index - 1];
    BTREE_PTR node = parent->children[index];

    if (node->is_leaf) {

        /* 自分のキーを右へずらす */
        for (int i = node->key_count; i > 0; i--) {
            node->keys[i] = node->keys[i - 1];
        }

        /* 左の兄弟の最大キーを受け取る */
        node->keys[0] = left->keys[left->key_count - 1];

        node->key_count++;
        left->key_count--;
    }
    else {

        /* 自分の子ポインタを右へずらす */
        for (int i = node->child_count; i > 0; i--) {
            node->children[i] = node->children[i - 1];
        }

        /* 左の兄弟の最後の子を受け取る */
        node->children[0] =
            left->children[left->child_count - 1];

        node->child_count++;

        left->child_count--;
        left->children[left->child_count] = NULL;

        update_internal_keys(left);
        update_internal_keys(node);
    }

    update_internal_keys(parent);
}

/* 右の兄弟から借りる */
void borrow_from_right(BTREE_PTR parent, int index)
{
    BTREE_PTR node = parent->children[index];
    BTREE_PTR right = parent->children[index + 1];

    if (node->is_leaf) {

        /* 右の兄弟の最小キーを受け取る */
        node->keys[node->key_count++] = right->keys[0];

        /* 右の兄弟のキーを左へずらす */
        for (int i = 1; i < right->key_count; i++) {
            right->keys[i - 1] = right->keys[i];
        }

        right->key_count--;
    }
    else {

        /* 右の兄弟の最初の子を受け取る */
        node->children[node->child_count++] =
            right->children[0];

        /* 右の兄弟の子を左へずらす */
        for (int i = 1; i < right->child_count; i++) {
            right->children[i - 1] = right->children[i];
        }

        right->child_count--;
        right->children[right->child_count] = NULL;

        update_internal_keys(node);
        update_internal_keys(right);
    }

    update_internal_keys(parent);
}

/* 隣り合う2つの子ノードを統合 */
void merge_children(BTREE_PTR parent, int left_index)
{
    BTREE_PTR left = parent->children[left_index];
    BTREE_PTR right = parent->children[left_index + 1];

    if (left->is_leaf) {

        /* 右のキーを左へ移す */
        for (int i = 0; i < right->key_count; i++) {
            left->keys[left->key_count++] = right->keys[i];
        }
    }
    else {

        /* 右の子ポインタを左へ移す */
        for (int i = 0; i < right->child_count; i++) {
            left->children[left->child_count++] =
                right->children[i];
        }

        update_internal_keys(left);
    }

    /* 右ノード自身を解放 */
    free(right);

    /* 親のchildren[]を詰める */
    for (int i = left_index + 1;
         i < parent->child_count - 1; i++) {

        parent->children[i] = parent->children[i + 1];
    }

    parent->child_count--;
    parent->children[parent->child_count] = NULL;

    update_internal_keys(parent);
}

/* 子ノードの不足を修正 */
void fix_underflow(BTREE_PTR parent, int index)
{
    BTREE_PTR node = parent->children[index];

    if (!is_underfull(node))
        return;

    /* 左の兄弟から借りる */
    if (index > 0 &&
        can_lend(parent->children[index - 1])) {

        borrow_from_left(parent, index);
        return;
    }

    /* 右の兄弟から借りる */
    if (index + 1 < parent->child_count &&
        can_lend(parent->children[index + 1])) {

        borrow_from_right(parent, index);
        return;
    }

    /* 借りられなければ統合 */
    if (index > 0)
        merge_children(parent, index - 1);
    else
        merge_children(parent, index);
}

/* 再帰的な削除 */
int delete_recursive(BTREE_PTR node, int x)
{
    if (node->is_leaf) {

        int i = 0;

        /* 削除対象を探す */
        while (i < node->key_count &&
               node->keys[i] != x) {
            i++;
        }

        if (i == node->key_count)
            return 0;

        /* 削除した位置を詰める */
        for (int j = i + 1; j < node->key_count; j++) {
            node->keys[j - 1] = node->keys[j];
        }

        node->key_count--;

        return 1;
    }

    /* 削除対象がある子を探す */
    int i = 0;

    while (i < node->key_count &&
           x >= node->keys[i]) {
        i++;
    }

    int deleted = delete_recursive(node->children[i], x);

    if (!deleted)
        return 0;

    /* 子が不足したらBorrowまたはMerge */
    fix_underflow(node, i);

    update_internal_keys(node);

    return 1;
}

/* 削除の入口 */
int btree_delete(BTREE_PTR *root, int x)
{
    if (root == NULL || *root == NULL)
        return 0;

    int deleted = delete_recursive(*root, x);

    if (!deleted)
        return 0;

    BTREE_PTR old_root = *root;

    /* Rootが葉で、最後のキーを削除した場合 */
    if (old_root->is_leaf) {
        if (old_root->key_count == 0) {
            free(old_root);
            *root = NULL;
        }
    }

    /* Rootの子が1つになった場合 */
    else if (old_root->child_count == 1) {
        *root = old_root->children[0];
        free(old_root);
    }

    return 1;
}

/* ---------- Display and cleanup ---------- */

void print_tree(BTREE_PTR root, int depth)
{
    if (root == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("    ");

    printf("%s [",
           root->is_leaf ? "Leaf" : "Internal");

    for (int i = 0; i < root->key_count; i++) {
        if (i > 0)
            printf(", ");

        printf("%d", root->keys[i]);
    }

    printf("]\n");

    if (!root->is_leaf) {
        for (int i = 0; i < root->child_count; i++) {
            print_tree(root->children[i], depth + 1);
        }
    }
}

void free_tree(BTREE_PTR root)
{
    if (root == NULL)
        return;

    if (!root->is_leaf) {
        for (int i = 0; i < root->child_count; i++) {
            free_tree(root->children[i]);
        }
    }

    free(root);
}

/* ---------- Main ---------- */

int main(void)
{
    BTREE_PTR root = NULL;

    int values[] = {
        30, 10, 20, 40, 50,
        60, 70, 80, 90, 100,
        110, 120, 5, 25, 65,
        15, 35, 45
    };

    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        btree_insert(&root, values[i]);
    }

    printf("=== Initial Tree ===\n");
    print_tree(root, 0);

    printf("\n=== Find ===\n");
    printf("Find 30: %d\n", btree_find(root, 30));
    printf("Find 65: %d\n", btree_find(root, 65));
    printf("Find 99: %d\n", btree_find(root, 99));

    printf("\n=== Delete ===\n");
    printf("Delete 30: %d\n", btree_delete(&root, 30));
    printf("Delete 65: %d\n", btree_delete(&root, 65));
    printf("Delete 99: %d\n", btree_delete(&root, 99));

    printf("\n=== Tree After Deletion ===\n");
    print_tree(root, 0);

    printf("\n=== Find After Deletion ===\n");
    printf("Find 30: %d\n", btree_find(root, 30));
    printf("Find 65: %d\n", btree_find(root, 65));
    printf("Find 40: %d\n", btree_find(root, 40));

    /* 残りのキーも削除する */
    for (int i = 0; i < n; i++) {
        if (values[i] != 30 && values[i] != 65) {
            btree_delete(&root, values[i]);
        }
    }

    printf("\n=== After Deleting All Keys ===\n");
    printf("Tree empty: %s\n",
           root == NULL ? "yes" : "no");

    free_tree(root);

    return 0;
}

