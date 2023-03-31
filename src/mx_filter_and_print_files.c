#include "../inc/uls.h"

bool mx_filter_files(files_arr_t* arr, bool* is_file_a) {
	bool dirs_were_provided = false;

	for(int i = 0; i < arr->len; i++) {
		if(mx_is_file(arr->files[i])){
			is_file_a[i] = true;
		} else {
			is_file_a[i] = false;
			dirs_were_provided = true;
		}
	}

	return dirs_were_provided;
}

//if it's file than print, if not mark as dir
//return true if there is files in command->fikes
bool mx_filter_and_print_files(uls_command_t* command, bool* is_file_a){
	bool to_terminal = isatty(STDOUT_FILENO);
	t_list* tmp = command->files;
		int index = 0;
		bool make_new_line = false;
		while(tmp) {
			if(mx_is_file(tmp->data)) {
				is_file_a[index++] = true;
				
				const char* pref = ((const char*)(tmp->data))[0] == '/' ? "" : ".";
				mx_print_filename(pref, tmp->data, command->flag_mask);
				//mx_printstr(tmp->data);
				mx_printstr(to_terminal ? "  " : "\n");

				make_new_line = true;
			}else {
				is_file_a[index++] = false;
			}
			tmp = tmp ->next;
		}

		if(make_new_line)
			mx_printstr("\n");

	return make_new_line;
}

