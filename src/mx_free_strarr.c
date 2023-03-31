#include "../inc/uls.h"

void mx_free_strarr(char** arr, int len){
	
	for(int i = 0; i < len; i++){
		free(arr[i]);
	}
	if(len != 0)
		free(arr);
	arr = NULL;
}
