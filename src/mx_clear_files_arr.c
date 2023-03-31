#include "../inc/uls.h"

void mx_clear_files_arr(files_arr_t** arr) {
	for(int i = 0; i < (*arr)->len; i++)
		free((*arr)->files[i]);
	free((*arr)->files);
	free(*arr);
	*arr = NULL;
}
