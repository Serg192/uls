#include "../inc/uls.h"


void mx_calc_col_params(column_params_t* c_params, files_arr_t* files_arr, int largest_file_name_len){

    int elm_in_last_row = 0;
    int rem = 0;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    c_params->cols = FLOOR(w.ws_col / largest_file_name_len);

    if((c_params->cols + 1)* largest_file_name_len - 1 < w.ws_col)
    	c_params->cols++;
  
    bool is_perfect_split = files_arr->len % c_params->cols == 0;
    
    if(!is_perfect_split){
    	while(true){
    		c_params->full_rows = (int)(files_arr->len / c_params->cols);
    		elm_in_last_row = (files_arr->len - c_params->full_rows * c_params->cols);
    		rem = elm_in_last_row == 0 ? 0 : c_params->cols - elm_in_last_row; 
    		c_params->rows = rem == 0 ? c_params->full_rows : c_params->full_rows + 1;

    		if(rem > c_params->full_rows)
    			c_params->cols -= 1;
    		else {
    			c_params->full_rows = c_params->rows - rem;
    			break;
    		}
    	} 
    }

}
