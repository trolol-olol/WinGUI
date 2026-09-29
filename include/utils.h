#ifndef UTILS_H
#define UTILS_H

typedef struct {
    void **items;
    int count;
    int capacity;
} List;

List* list_create(int capacity);
int list_append(List *list,void *item);
void* list_get(List *list,int index);
int list_remove(List *list,int index);
void list_free(List *list);

#endif
