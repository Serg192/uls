#include "../inc/uls.h"

void mx_add_to_dir_list(dir_with_prop_t* dir, files_arr_t* files_arr, t_list* files_in_dir, t_list** dirs_with_p) {
	for(int i = 0; i < files_arr->len; i++) {
		file_with_prop_t* file = (file_with_prop_t*)malloc(sizeof(file_with_prop_t));
		char *path = NULL;
		
		if(!mx_check_char_delim(dir->dir_name)) {
			char *parent = mx_strjoin(dir->dir_name, "/");
			path = mx_strjoin(parent, files_arr->files[i]);
			free(parent);
		}
		else 
			path = mx_strjoin(dir->dir_name, files_arr->files[i]);

		file->file_name = mx_strdup(files_arr->files[i]);
		file->path = path;
		mx_set_file_prop(file);
		mx_push_back(&files_in_dir, file);		
	}
	dir->files_with_prop = files_in_dir;
	mx_push_back(dirs_with_p, dir);	
}
