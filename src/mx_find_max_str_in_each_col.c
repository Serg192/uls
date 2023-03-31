#include "../inc/uls.h"

void mx_find_max_str_in_each_col(files_arr_t* files_arr, column_params_t* c_params, int* max_col_str_len){

	for(int i = 0; i < c_params->cols; i++)
    	max_col_str_len[i] = -1;

    bool shoud_finish = false;
    bool is_perfect_split = files_arr->len % c_params->cols == 0;

    if(is_perfect_split)
    	c_params->rows = files_arr->len / c_params->cols;

    for(int c = 0; c < c_params->cols; c++){
    	for(int r = 0; r < c_params->rows; r++) {
    		if(!is_perfect_split && c == c_params->cols -1 && r >= c_params->full_rows){
    			shoud_finish = true;
    			break;
    		}

    		const int current_str_len = mx_strlen(files_arr->files[c * c_params->rows + r]);

    		if(current_str_len > max_col_str_len[c])
    			max_col_str_len[c] = current_str_len;

    	}
    	if(shoud_finish)
    		break;
    }
}

