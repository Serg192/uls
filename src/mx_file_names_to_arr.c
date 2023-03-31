#include "../inc/uls.h"

files_arr_t* mx_file_names_to_arr(t_list* f_list) {
	t_list* tmp = f_list;

	files_arr_t* f_arr = (files_arr_t*)malloc(sizeof(files_arr_t));
	f_arr->len = 0;
	f_arr->capacity = 4;
	f_arr->files = (char**)malloc(sizeof(char*) * f_arr->capacity);


	while(tmp) {
		if(f_arr->len >= f_arr->capacity - 1) {
				f_arr->capacity += f_arr->capacity / 3 + 1;
				f_arr->files = mx_grow_char_arra(f_arr->files, f_arr->len, f_arr->capacity);
		}

		f_arr->files[f_arr->len++] = mx_strdup((char*)tmp->data);

		tmp = tmp->next;
	}

	return f_arr;
}
