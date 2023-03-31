#include "../inc/uls.h"

void mx_clear_dir_with_prop(dir_with_prop_t *dir_with_prop) {
    //free(dir_with_prop->dir_name);
    mx_clear_files_with_prop_list(dir_with_prop->files_with_prop);
    free(dir_with_prop);
}
