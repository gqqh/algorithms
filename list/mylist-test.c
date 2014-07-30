#include <stdio.h>
#include "mylist.h"

typedef struct mylist {
    int num;
    struct list_head list;
} mylist_t;


static LIST_HEAD(list1); 
static LIST_HEAD(list2);

int main()
{
    struct list_head *i;
    mylist_t tmp_list1;
    mylist_t tmp_list2;
    INIT_LIST_HEAD(&list1);
    INIT_LIST_HEAD(&list2);
    tmp_list1.num = 1;
    tmp_list2.num = 2;
    list_add(&tmp_list1.list, &list1);
    list_del(&tmp_list1.list);
    list_add(&tmp_list1.list, &list1);
    list_add_tail(&tmp_list2.list, &list1);

    list_move_tail(&tmp_list2.list, &list2);
    list_splice_init(&list1, &list2); 
    return 0;
}