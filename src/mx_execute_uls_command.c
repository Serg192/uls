#include "../inc/uls.h"

static inline bool print_recursive(uls_command_t* command, files_arr_t* files_arr, const char* parent_dir, bool f){
	bool has_f = false;
	
     if(parent_dir == NULL) {
    	
    	for(int i = 0; i < files_arr->len; i++) {
			if(mx_is_file(files_arr->files[i])){
				//mx_printstr(files_arr->files[i]);
				mx_print_filename(".", files_arr->files[i], command->flag_mask);
				mx_printstr(!isatty(STDOUT_FILENO) || command->flag_mask & FLAG_1 ? "\n" : " ");
				has_f = true;
			}
		}

		if(has_f && isatty(STDOUT_FILENO) && !(command->flag_mask & FLAG_1))
			mx_printstr("\n");
    }else{
    	if(!f){
			mx_printstr("\n");
		}

		//if(mx_strcmp(parent_dir, ".") != 0){
			if(!(f && (command->f_count == 0 && command->dirs <= 1))){
				mx_printstr(parent_dir);
    	    	mx_printstr(":\n");	
			}
			
		//}
    
    	mx_handle_disp_dir_in_col_r(parent_dir, files_arr, command->flag_mask);

		f = false;
    }
	//f = false;

	for(int i = 0; i < files_arr->len; i++){
		if(!mx_is_file(files_arr->files[i])) {
			char* p;

			if(parent_dir == NULL){
				p = mx_strdup(files_arr->files[i]);
			}else {
				p = mx_strnew(mx_strlen(parent_dir) + mx_strlen(files_arr->files[i]) + 2);
				mx_strcat(p, parent_dir);
				mx_strcat(p, "/");
				mx_strcat(p, files_arr->files[i]);
			}
		    
			if(has_f){
				mx_printstr("\n");
				has_f = false;
			}

			if(!mx_is_file(p) && !mx_is_link(mx_strjoin("./", p)) 
				&& ((mx_strcmp(files_arr->files[i], ".") != 0 && mx_strcmp(files_arr->files[i], "..") != 0) || mx_strcmp(p, files_arr->files[i]) == 0))
				f = print_recursive(command, mx_get_files_from_dir(p, command->flag_mask), p, f);
			free(p);
		}
	}

	mx_clear_files_arr(&files_arr);
	return f;
}

static inline void execute_without_flags(uls_command_t* command) {
	files_arr_t* files = NULL;
	
	if(command->files != NULL) {
		if(command->flag_mask & FLAG_R){
			files = mx_file_names_to_arr(command->files);
			print_recursive(command, files, NULL, true);
		} else {
			bool is_file_a[command->files_count];
			bool files_were_provided = mx_filter_and_print_files(command, is_file_a);
			mx_handle_disp_dir_in_col(command, is_file_a, files_were_provided);
		}
	}
	else if(!command->err_oc){
	    files = mx_get_files_from_dir(".", command->flag_mask);
		if(command->flag_mask & FLAG_R)
			print_recursive(command, files, ".", true);
		else {
	    	//mx_print_files(files);
			mx_handle_disp_dir_in_col_r(".", files, command->flag_mask);	
			mx_clear_files_arr(&files);
		}
	}
	//if(files != NULL)
	//	mx_clear_files_arr(&files);
}

void mx_execute_uls_command(uls_command_t* command) {

	if(!(command->flag_mask & FLAG_l))
		execute_without_flags(command);
	if(command->flag_mask & FLAG_l)
		mx_execute_with_flag_l(command);
	
}

