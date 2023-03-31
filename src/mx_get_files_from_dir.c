#include "../inc/uls.h"

 char** mx_grow_char_arra(char** arr, int len, int new_capacity) {
	char** result = (char**)malloc(sizeof(char*) * new_capacity);

	if(arr == NULL) {
		return result;
 	}

	for(int i = 0; i < len; i++)
		result[i] = mx_strdup(arr[i]);

	mx_free_strarr(arr, len);
	return result;	
}

files_arr_t* mx_get_files_from_dir(const char* path, /*bool include_hidden*/ int flag_mask) {
	files_arr_t* files_arr = (files_arr_t*)malloc(sizeof(files_arr_t));
	files_arr->len = 0;
	files_arr->capacity = 4;
	files_arr->files = NULL;
	files_arr->files = mx_grow_char_arra(files_arr->files, 0, files_arr->capacity);

	DIR* dir;
	struct dirent* entry;

	if((dir = opendir(path)) != NULL) {
		while((entry = readdir(dir)) != NULL) {
			if(entry->d_name[0] == '.') {
				if(!((flag_mask & FLAG_A) || (flag_mask & FLAG_a))) 
					continue;
				if(flag_mask & FLAG_A) {
					if(mx_strcmp(entry->d_name, ".") == 0 || mx_strcmp(entry->d_name, "..") == 0)
						continue;
				}
			}

			if(files_arr->len >= files_arr->capacity - 1) {
				files_arr->capacity += files_arr->capacity / 3 + 1;
				files_arr->files = mx_grow_char_arra(files_arr->files, files_arr->len, files_arr->capacity);
			}

			files_arr->files[files_arr->len++] = mx_strdup(entry->d_name);
		}
		closedir(dir);
	} else {
		const char* str_err = strerror(errno);
		write(2, "uls: ", 5);
		write(2, path, mx_strlen(path));
		write(2, ": ", 3);
		write(2, str_err, mx_strlen(str_err));
		write(2, "\n", 1);
		exit(-1);
	}
	mx_sort_files(files_arr);
	return files_arr;
}
