#include "../inc/uls.h"

void mx_print_files(files_arr_t* arr) {

	bool to_terminal = isatty(STDOUT_FILENO);

	for(int i = 0; i < arr->len; i++){
		mx_printstr(arr->files[i]);
		mx_printstr(to_terminal ? "  " : "\n");
	}
	
	if(to_terminal)
		mx_printstr("\n");
}
