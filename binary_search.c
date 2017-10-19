#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct vertex {
    int data;
    struct vertex *l, *r;
};

struct vertex *newv();
struct vertex *create();
int member(struct vertex *p, int x);
struct vertex *search1(struct vertex *p, int x);
struct vertex **search2(struct vertex *p, int x);
void insert(struct vertex *p, int x);
void delete(struct vertex *p, int x);
void printTree(struct vertex *p);
void printTree1(struct vertex *p, int depth, bool isLeft);

struct vertex *newv()
{
    return ((struct vertex *) malloc(sizeof(struct vertex)));
}

struct vertex *create()
{
    struct vertex *p;

    p = newv();
    p->data = 0;
    p->r = NULL;
    p->l = NULL;
    return(p);
}

int member(struct vertex *p, int x)
{
    while (p != NULL) {
        if (p->data == x) return 1;
        else if (p->data > x) {
            p = p->l;
        } else {
            p = p->r;
        }
    }
    return 0;
}

struct vertex *search1(struct vertex *p, int x)
{
    while (p != NULL) {
        // データ一致
        if (p->data == x) return p;
        // データ不一致 左子へ
        else if (p->data > x) p = p->l;
        // データ不一致 右子へ
        else p = p->r;
    }
    return NULL;
}

struct vertex **search2(struct vertex *p, int x)
{
    struct vertex **pp = NULL;

    while (p != NULL && p->data != x) {
        if (p->data > x) {
            // データ不一致 左子へ
            pp = &(p->l);
            p = p->l;
        } else if (p->data < x) {
            // データ不一致 右子へ
            pp = &(p->r);
            p = p->r;
        }
    }
    return pp;
}

void insert(struct vertex *p, int x)
{
    struct vertex **pp;
    struct vertex *pt;

    if (search1(p, x) != NULL) return;
    pp = search2(p, x);
    // 新しいノードを作成
    pt = newv();
    pt->data = x;
    pt->l = pt->r = NULL;
    *pp = pt;

}

void delete(struct vertex *p, int x)
{
    struct vertex **pp;
    struct vertex *f, *q;
    char exists;
    if (search1(p, x) == NULL) return;
    pp = search2(p, x);
    p = *pp;
    if (p->l == NULL || p->r == NULL) {
        // 子が0個 or 1個
        if (p->r == NULL) *pp = p->l;
        else *pp = p->r;
        free(p);
    } else {
        // 子が2個
        q = p->r;
        f = q;
        while (q->l != NULL) {
            f = q;
            q = q->l;
        }
        // p: 削除するノード
        // q: 上に移すノード
        // f: qの親
        f->l = q->r;
        (*pp) = q;
        q->r = p->r;
        q->l = p->l;
        free(p);
    }
}

void printTree(struct vertex *p)
{
    printTree1(p, 0, false);
}

void printTree1(struct vertex *p, int depth, bool isLeft)
{
    if (p != NULL) {
        printf("%*s%d\n", 5 * depth + 2, isLeft ? "L:" : "R:" , p->data);
        printTree1(p->l, depth+1, true);
        printTree1(p->r, depth+1, false);
    }
}


int main(void)
{
    struct vertex *p, *q;
    // テスト用データ
    int a[12] = {18, 7, 22, 5, 11, 8, 9, 15, 22, 21, 31, 25};

    // 木を作成
    p = create();
    for (int i = 0; i < 12; i++) {
        insert(p, a[i]);
    }
    printTree(p->r);
    // ノードを検索
    q = search1(p, 15);
    printf("%p\n", q);
    if (q != NULL) printf("%d\n", (*search2(p, 15))->data);
    // ノードを削除
    delete(p, 31);
    delete(p, 25);
    delete(p, 7);
    printTree(p->r);
    return 0;
}

