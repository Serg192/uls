#include "../inc/uls.h"

void mx_clear_files_with_prop_list(t_list *files_with_prop) {
    while (files_with_prop) {
        file_with_prop_t *file = files_with_prop->data;
        free(file->file_permissions);
        free(file->owner_name);
        free(file->group_name);
        free(file->last_modification_time);
        free(file->file_name);
        free(file->path);
		if (file->link != NULL) {
        	free(file->link);
		}
		
        t_list *next = files_with_prop->next;
        free(files_with_prop->data);
        free(files_with_prop);
        files_with_prop = next;
    }
}
