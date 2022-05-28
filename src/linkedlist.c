#include "linkedlist.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

inline static ListItem create_item(const void * data, size_t sz);

struct ListItemInner {
    void * data;
    struct ListItemInner * next;
    struct ListItemInner * prev;
};

struct ListInner {
    struct ListItemInner * head;
    struct ListItemInner * tail;
    size_t sz;
    size_t data_sz;
    void (*fn_destroy)(void*);
};

List list_create(size_t data_sz, void(*fn_destroy)(void*)){
    assert(data_sz > 0);
    List list = malloc(sizeof (struct ListInner));
    if (list == NULL){
        perror("Unable to allocate memory. The process is finished");
        abort();
    }
    list->head = NULL;
    list->tail = NULL;
    list->sz = 0;
    list->data_sz = data_sz;
    list->fn_destroy = fn_destroy;
    return list;
}

void list_create_item(List list, const void * data){
    assert(list != NULL && data != NULL);
    ListItem item = create_item(data, list->data_sz);
    if(item == NULL){
        perror("Unable to allocate memory. The process is finished");
        abort();
    }
    list->sz++;
    if (list->head == NULL) {
        list->head = item;
        list->tail = item;
    } else {
        item->prev = list->tail;
        list->tail->next = item;
        list->tail = item;
    }
}

ListItem list_first_item(const List list){
    assert(list != NULL);
    return list->head;
}

ListItem list_next_item(const ListItem item){
    assert(item != NULL);
    return item->next;
}

ListItem list_remove_item(List list, ListItem item){
    assert(list != NULL && item != NULL);
    ListItem next = item->next;
    if (list->head == item) 
        list->head = item->next;
    else 
        item->prev->next = item->next;

    if (list->tail == item) 
        list->tail = item->prev;
    list->fn_destroy(item->data);
    free(item);
    list->sz--;
    return next;
}

void * list_get_item_data(const ListItem item){
    assert(item != NULL);
    return item->data;
}

size_t list_size(List list) {
    return list->sz;
}

void list_free(List list){
    if (list == NULL)
        return;
    ListItem item = list_first_item(list);
    while (item != NULL) {
        ListItem next = item->next;
        list->fn_destroy(item->data);
        free(item);
        item = next;
    }
    free(list);
    list = NULL;
}

inline static ListItem create_item(const void * data, size_t sz){
    assert(data != NULL);
    ListItem item = malloc(sizeof (struct ListItemInner));
    if (item == NULL){
        perror("Unable to allocate memory. The process is finished");
        abort();
    }
    item->data = malloc(sz);
    if (item->data == NULL){
        perror("Unable to allocate memory. The process is finished");
        abort();
    }
    memcpy(item->data, data, sz);
    item->next = NULL;
    item->prev = NULL;
    return item;
}
