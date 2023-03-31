#include "../inc/uls.h"

void mx_sort_files(files_arr_t* arr){
	for(int i = 0; i < arr->len; i++) {
		for(int j = 0; j + 1 < arr->len; j++){
			if(mx_string_comparator(arr->files[j], arr->files[j+1])){
				char* t = arr->files[j];
				arr->files[j] = arr->files[j + 1];
				arr->files[j + 1] = t;
			}
		}
	}
}
