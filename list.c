#include <stdio.h>
#include <stdlib.h>

struct element {
    char data;
    struct element *next;
};

struct element *new()
{
    return ((struct element *) malloc(sizeof(struct element)));
}

struct element *create()
{
    struct element *p;
    p = new();
    p->data = '!';
    p->next = NULL;
    return(p);
}

void insert(struct element *l, int k, char item)
{
    struct element *p;
    struct element *tmp;
    tmp = l;
    for (int i = k; k > 1; k--) {
        tmp = tmp->next;
    }
    p = new();
    p->data = item;
    p->next = tmp->next;
    tmp->next = p;
}

void delete(struct element *l, int k)
{
    struct element *next;
    struct element *tmp;
    tmp = l;
    for (int i = k; k > 1; k--) {
        tmp = tmp->next;
    }
    next = tmp->next;
    tmp->next = tmp->next->next;
    free(next);
}

char access(struct element *l, int k)
{
    struct element *tmp;
    tmp = l;
    for (int i = k; k > 1; k--) {
        tmp = tmp->next;
    }
    return(tmp->next->data);
}

void reverse(struct element *l)
{
    struct element *back, *p, *next;
    if (l->next == NULL || l->next->next == NULL) return;
    p = l->next;
    next = p->next;
    p->next = NULL;
    while (next) {
        back = p;
        p = next;
        next = p->next;
        p->next = back;
    }
    l->next = p;
}

void print(struct element *l)
{
    int i;
    struct element *p;
    p = l->next;
    for (i = 0; i < 20; i++) {
        if (p != NULL) {
            printf("%c -> ", p->data);
            p = p->next;
        } else {
            printf("NULL\n");
            return;
        }
    }
    printf("...\n");
}

int main(void) {
    struct element *p;
    p = create(); print(p);
    insert(p, 1, 'a'); print(p);
    insert(p, 2, 'b'); print(p);
    insert(p, 3, 'c'); print(p);
    reverse(p); print(p);
    delete(p, 2); print(p);
    return 0;
}

