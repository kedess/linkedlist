## Linkedlist
<hr/>

### Installing:
```bash
git clone https://github.com/kedess/linkedlist.git
cd linkedlist
make
sudo make install
```

### Usage:
```C
#include <assert.h>
#include <linkedlist/linkedlist.h>

void drop(void * elem){
    size_t * ptr = (size_t*) elem;
    free(ptr);
}

int main() {
    List list = list_create(sizeof(size_t), drop);
    for (size_t i = 0; i < 10; i++) {
        list_create_item(list, &i);
    }
    ListItem item = list_first_item(list);
    while (item != NULL) {
        size_t * data = list_item_elem(item);
        printf("%ld\n", *data);
        item = list_next_item(item);
    }
    assert(list_size(list) == 10);
    list_remove_item(list, list_first_item(list));
    assert(list_size(list) == 9);
    list_free(list);
    return 0;
}
```
