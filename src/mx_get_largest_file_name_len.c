#include "../inc/uls.h"

int mx_get_largest_file_name_len(files_arr_t* files_arr) {
	int largest_file_name_len = -1;

	for(int i = 0; i < files_arr->len; i++){
		const int name_len = mx_strlen(files_arr->files[i]);

		if(name_len > largest_file_name_len)
			largest_file_name_len = name_len;
	}

	return largest_file_name_len;
}
