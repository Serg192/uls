#include "../inc/uls.h"

void mx_clear_files_list(t_list* list) {
    while(list){
        //free(list->data);
        t_list* del = list;
        list = list->next;
        free(del);
    }
}

