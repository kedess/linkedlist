#include <assert.h>
#include <linkedlist/linkedlist.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

void drop(void * elem){
    size_t * ptr = (size_t*)elem;
    free(ptr);
}

void test_1(){
    clock_t start = clock();
    List list = list_create(sizeof(size_t), drop);
    for (size_t i = 0; i < 1000000; i++) {
        list_create_item(list, &i);
    }
    ListItem item = list_first_item(list);
    while (item != NULL) {
        int * data = list_get_item_data(item);
        if (data == NULL) {
            assert(false);
        }
        item = list_next_item(item);
    }
    list_free(list);
    clock_t end = clock();
    printf("Test 1 completed successfully. Elapsed time %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
}

void test_2(){
    clock_t start = clock();
    List list = list_create(sizeof(size_t), drop);
    for (size_t i = 0; i < 10013; i++) {
        list_create_item(list, &i);
    }
    assert(list_size(list) == 10013);
    ListItem item = list_first_item(list);
    while (item != NULL) {
        item = list_remove_item(list, item);
    }
    assert(list_size(list) == 0);
    list_free(list);
    clock_t end = clock();
    printf("Test 2 completed successfully. Elapsed time %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
}

void test_3(){
    clock_t start = clock();
    List list = list_create(sizeof(size_t), drop);
    for (size_t i = 0; i < 10; i++) {
        list_create_item(list, &i);
    }
    ListItem item = list_first_item(list);
    while (item != NULL) {
        size_t * data = list_get_item_data(item);
        item = list_next_item(item);
    }
    assert(list_size(list) == 10);
    list_remove_item(list, list_first_item(list));
    assert(list_size(list) == 9);
    list_free(list);
    clock_t end = clock();
    printf("Test 3 completed successfully. Elapsed time %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
}

int main() {
    test_1();
    test_2();
    test_3();
    return 0;
}
