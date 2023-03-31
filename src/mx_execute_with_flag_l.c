#include "../inc/uls.h"

static inline void print_with_arguments(uls_command_t* command, files_arr_t* files_arr) {
	t_list* tmp = command->files;		
	t_list* files_with_p = NULL;
	t_list* dirs_with_p = NULL;
	
	while(tmp) {
		if(mx_is_file(tmp->data)) {
			file_with_prop_t* file = (file_with_prop_t*)malloc(sizeof(file_with_prop_t));
			file->file_name = mx_strdup((char*)tmp->data);
			file->path = mx_strdup((char*)tmp->data);
			mx_set_file_prop(file);
			mx_push_back(&files_with_p, file);	
		}
		tmp = tmp->next;
	}	
	
	mx_fill_dir_list(command, files_arr, &dirs_with_p);

	bool only_one_dir = files_with_p == NULL && dirs_with_p != NULL && dirs_with_p->next == NULL;
	bool only_files = dirs_with_p == NULL;
	
	if(files_with_p != NULL) {
		mx_print_files_with_flag_l(files_with_p, command->flag_mask, only_files);	
		mx_clear_files_with_prop_list(files_with_p);
	}
	
	if(dirs_with_p != NULL) {
		mx_print_dirs_with_flag_l(dirs_with_p, command->flag_mask, only_one_dir);
		mx_clear_dirs_with_prop_list(dirs_with_p);
	}
}

static inline void print_without_arguments(uls_command_t* command, files_arr_t* files_arr) {
	dir_with_prop_t *dir = (dir_with_prop_t*)malloc(sizeof(dir_with_prop_t));
	t_list* files_in_dir = NULL;
	t_list* dirs_with_p = NULL;
	for(int i = 0; i < files_arr->len; i++) {
		file_with_prop_t* file = (file_with_prop_t*)malloc(sizeof(file_with_prop_t));
		
		file->file_name = mx_strdup(files_arr->files[i]);
		file->path = mx_strjoin("./", files_arr->files[i]);			
		
		mx_set_file_prop(file);
		mx_push_back(&files_in_dir, file);			
	}
	dir->dir_name = ".";
	dir->files_with_prop = files_in_dir;
	mx_push_back(&dirs_with_p, dir);	
	mx_print_dirs_with_flag_l(dirs_with_p, command->flag_mask, true);

	mx_clear_dirs_with_prop_list(dirs_with_p);
	mx_clear_files_arr(&files_arr);
}

static inline bool print_recursive(uls_command_t* command, files_arr_t* files_arr, const char* parent_dir, bool f) {
	(void)files_arr; (void)parent_dir;
    
	bool has_f = false;

	if (parent_dir == NULL) {
		t_list* files_in_dir = NULL;

		for (int i = 0; i < files_arr->len; i++) {
			if(mx_is_file(files_arr->files[i])) {
				file_with_prop_t* file = (file_with_prop_t*)malloc(sizeof(file_with_prop_t));
					
				file->file_name = mx_strdup(files_arr->files[i]);
				file->path = mx_strjoin("./", files_arr->files[i]);			
					
				mx_set_file_prop(file);
				mx_push_back(&files_in_dir, file);	
				has_f = true;
			}
		}

		if(files_in_dir != NULL)
			mx_print_files_with_flag_l(files_in_dir, command->flag_mask, true);
		
		mx_clear_files_with_prop_list(files_in_dir);
		
    }
	else {
		t_list* files_in_dir = NULL;
		t_list* dirs_with_p = NULL;
		dir_with_prop_t *dir = (dir_with_prop_t*)malloc(sizeof(dir_with_prop_t));
		dir->dir_name = (char*)parent_dir;		
		//bool not_print_dir_name = true;

		if (!f){
			mx_printstr("\n");
		}

		//if(mx_strcmp(parent_dir, ".") != 0){
			if(!(f && (command->f_count == 0 && command->dirs <= 1))){
				mx_printstr(parent_dir);
    	    	mx_printstr(":\n");	
			}
			
		//}

		mx_add_to_dir_list(dir, files_arr, files_in_dir, &dirs_with_p);
		
		if(dirs_with_p != NULL) 
			mx_print_dirs_with_flag_l(dirs_with_p, command->flag_mask, true);
		
		mx_clear_dirs_with_prop_list(dirs_with_p);
		f = false;
    }

	for (int i = 0; i < files_arr->len; i++){
		if (!mx_is_file(files_arr->files[i])) {
			char* p;
			if (parent_dir == NULL){
				p = mx_strdup(files_arr->files[i]);
			}
			else {
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

void mx_execute_with_flag_l(uls_command_t* command) {
	files_arr_t* files_arr = NULL;
	
	if (command->files != NULL) {
		if (command->flag_mask & FLAG_R) {
			files_arr = mx_file_names_to_arr(command->files);
			print_recursive(command, files_arr, NULL, true);
		}
		else {
			print_with_arguments(command, files_arr);
		}
	}
	else if (!command->err_oc) {
		files_arr = mx_get_files_from_dir(".", command->flag_mask);
		if (command->flag_mask & FLAG_R) {
			print_recursive(command, files_arr, ".", true);
		}
		else {
			print_without_arguments(command, files_arr);
		}
	}
}

