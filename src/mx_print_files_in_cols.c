#include "../inc/uls.h"

static inline void print_in_one_col(const char* parent_pref, files_arr_t* files_arr, int flag_mask){
	for(int i = 0; i < files_arr->len; i++){
		mx_print_filename(parent_pref, files_arr->files[i], flag_mask);
		mx_printstr("\n");
	}
}

void mx_print_files_in_cols(const char* parent_pref, files_arr_t* files_arr, column_params_t* c_params, int* max_col_str_len, int flag_mask){
	bool to_terminal = isatty(STDOUT_FILENO);

	if(flag_mask & FLAG_1){
		print_in_one_col(parent_pref, files_arr, flag_mask);
		return;
	}
	 
	bool is_perfect_split = files_arr->len % c_params->cols == 0;

	 for(int r = 0; r < c_params->rows; r++){
    	for(int c = 0; c < c_params->cols; c++) {

    		if(!is_perfect_split && c == c_params->cols - 1 && r + 1 > c_params->full_rows){
    			//ignore
    		} else {
    			const char* current_file_name = files_arr->files[c * c_params->rows + r];

    			//mx_printstr(current_file_name);
				mx_print_filename(parent_pref, current_file_name, flag_mask);

    			if(!to_terminal){
    				if(c != c_params->cols - 1)
    					mx_printstr("\n");
    				continue;
    			}

    			for(int t = 0; t < max_col_str_len[c] - mx_strlen(current_file_name); t++)
    				mx_printstr(" ");

    			mx_printstr(c == c_params->cols - 1 ? " " : "   ");
    		}
    	}
    	mx_printstr("\n");
    }
}
