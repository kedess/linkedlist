#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

struct ListItemInner;
typedef struct ListItemInner *  ListItem;
struct ListInner;
typedef struct ListInner * List;

List list_create(size_t elem_sz, void(*fn_destroy)(void*));

void list_create_item(List list, const void * data);

ListItem list_first_item(const List list);
ListItem list_next_item(const ListItem item);

ListItem list_remove_item(List list, ListItem item);

void * list_get_item_data(const ListItem item);

size_t list_size(List list);

void list_free(List list);
