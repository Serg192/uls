#include "../inc/uls.h"

void mx_fill_dir_list(uls_command_t* command, files_arr_t* files_arr, t_list** dirs_with_p) {
	t_list* tmp = command->files;
	while(tmp) {
		if(!mx_is_file(tmp->data)) {

			dir_with_prop_t *dir = (dir_with_prop_t*)malloc(sizeof(dir_with_prop_t));
			dir->dir_name = (char*)tmp->data;
			files_arr = mx_get_files_from_dir(dir->dir_name, command->flag_mask);
			t_list* files_in_dir = NULL;
			
			mx_add_to_dir_list(dir, files_arr, files_in_dir, dirs_with_p);
			mx_clear_files_arr(&files_arr);
		}
		tmp = tmp->next;
	}
}
