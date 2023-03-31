#include "../inc/uls.h"

void mx_clear_dirs_with_prop_list(t_list *list) {
    while (list) {
        t_list *next = list->next;
        mx_clear_dir_with_prop(list->data);
        free(list);
        list = next;
    }
}
