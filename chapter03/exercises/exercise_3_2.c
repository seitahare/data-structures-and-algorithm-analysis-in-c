#include <stdio.h>
#include <stdlib.h>

/* Linked Listの構造体 */
struct node {
    int element;
    struct node *next;
};

/* 型定義 */
typedef struct node *POSITION;
typedef struct node *LIST;


/* Linked Listの作成 */
LIST create_list(void)
{
    LIST L = malloc(sizeof(struct node));

    if (L == NULL)
        exit(EXIT_FAILURE);

    L->next = NULL;

    return L;
}


/* Linked Listの末尾に要素を追加 */
void append(LIST L, int x)
{
    POSITION new_node = malloc(sizeof(struct node));

    if (new_node == NULL)
        exit(EXIT_FAILURE);

    new_node->element = x;
    new_node->next = NULL;

    POSITION p = L;

    while (p->next != NULL) {
        p = p->next;
    }

    p->next = new_node;
}


/* Exercise 3.2 */
void print_lots(LIST L, LIST P)
{
    POSITION pL;
    POSITION pP;
    int position = 1;

    pL = L->next;
    pP = P->next;

    while (pP != NULL && pL != NULL) {

        while (pL != NULL && position < pP->element) {
            pL = pL->next;
            position++;
        }

        if (pL != NULL && position == pP->element) {
            printf("%d ", pL->element);
            pP = pP->next;
        }
    }
}


/* Linked Listのメモリ解放 */
void dispose_list(LIST L)
{
    POSITION p = L;

    while (p != NULL) {
        POSITION next = p->next;
        free(p);
        p = next;
    }
}


/* 動作確認 */
int main(void)
{
    LIST L = create_list();
    LIST P = create_list();

    /* L = [10, 20, 30, 40, 50, 60] */
    append(L, 10);
    append(L, 20);
    append(L, 30);
    append(L, 40);
    append(L, 50);
    append(L, 60);

    /* P = [1, 3, 4, 6] */
    append(P, 1);
    append(P, 3);
    append(P, 4);
    append(P, 6);

    /* Exercise 3.2を実行 */
    print_lots(L, P);
    printf("\n");

    /* メモリ解放 */
    dispose_list(L);
    dispose_list(P);

    return 0;
}
