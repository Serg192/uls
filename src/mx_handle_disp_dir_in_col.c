#include "../inc/uls.h"

//version for rec
void mx_handle_disp_dir_in_col_r(const char* parent_pref, files_arr_t* files_arr, int flag_mask) {
	
	column_params_t c_params;
	mx_calc_col_params(&c_params, files_arr, mx_get_largest_file_name_len(files_arr) + 3);
	int max_col_str_len[c_params.cols];
    mx_find_max_str_in_each_col(files_arr, &c_params, max_col_str_len);
    mx_print_files_in_cols(parent_pref, files_arr, &c_params, max_col_str_len, flag_mask);
				
	//mx_clear_files_arr(&files_arr);
}

void mx_handle_disp_dir_in_col(uls_command_t* command, bool* is_file_a, bool files_were_printed){
	
	files_arr_t* files_arr = NULL;
	t_list* tmp = command->files;
	bool one_file = command->files->next == NULL;
	int index = 0;

	while(tmp) {
			if(is_file_a[index] == false) {
				files_arr = mx_get_files_from_dir(tmp->data, command->flag_mask);
				if(!one_file || command->err_oc){
				    if(!files_were_printed){ //that means no files were provided alonside with dirs
				    	//ignore first new line
				    	files_were_printed = true;
				    } else {
				    	mx_printstr("\n");
				    }
					mx_printstr(tmp->data);
					mx_printstr(":\n");
				}

				column_params_t c_params;
				mx_calc_col_params(&c_params, files_arr, mx_get_largest_file_name_len(files_arr) + 2);
				int max_col_str_len[c_params.cols];
    			mx_find_max_str_in_each_col(files_arr, &c_params, max_col_str_len);
    			mx_print_files_in_cols(tmp->data, files_arr, &c_params, max_col_str_len, command->flag_mask);
				
				mx_clear_files_arr(&files_arr);
			}
			index++;
			tmp = tmp->next;
	}

}

