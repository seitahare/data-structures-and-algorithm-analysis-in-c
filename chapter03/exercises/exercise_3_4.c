#include <stdio.h>
#include <stdlib.h>

struct node {
    int element;
    struct node *next;
};

typedef struct node *POSITION;
typedef struct node *LIST;


/* 新しいLinked Listを作成 */
LIST create_list(void)
{
    LIST L = malloc(sizeof(struct node));

    if (L == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    L->next = NULL;

    return L;
}


/* リストの末尾に要素を追加 */
void append(LIST L, int x)
{
    POSITION new_node = malloc(sizeof(struct node));

    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->element = x;
    new_node->next = NULL;

    POSITION p = L;

    while (p->next != NULL) {
        p = p->next;
    }

    p->next = new_node;
}


/* 2つのリストの積集合を求める */
LIST intersection(LIST L1, LIST L2)
{
    LIST result = create_list();

    POSITION p1 = L1->next;
    POSITION p2 = L2->next;

    while (p1 != NULL && p2 != NULL) {

        if (p1->element == p2->element) {
            append(result, p1->element);

            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->element < p2->element) {
            p1 = p1->next;
        }
        else {
            p2 = p2->next;
        }
    }

    return result;
}


/* リストを表示 */
void print_list(LIST L)
{
    POSITION p = L->next;

    while (p != NULL) {
        printf("%d ", p->element);
        p = p->next;
    }

    printf("\n");
}


/* リストのメモリを解放 */
void dispose_list(LIST L)
{
    POSITION p = L;

    while (p != NULL) {
        POSITION next = p->next;

        free(p);

        p = next;
    }
}


int main(void)
{
    /* 2つのリストを作成 */
    LIST L1 = create_list();
    LIST L2 = create_list();

    /* L1 = 1, 3, 5, 7 */
    append(L1, 1);
    append(L1, 3);
    append(L1, 5);
    append(L1, 7);

    /* L2 = 2, 3, 5, 8 */
    append(L2, 2);
    append(L2, 3);
    append(L2, 5);
    append(L2, 8);

    /* 積集合を計算 */
    LIST result = intersection(L1, L2);

    /* 結果を表示 */
    printf("L1: ");
    print_list(L1);

    printf("L2: ");
    print_list(L2);

    printf("Intersection: ");
    print_list(result);

    /* メモリ解放 */
    dispose_list(L1);
    dispose_list(L2);
    dispose_list(result);

    return 0;
}
