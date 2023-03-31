#include "../inc/uls.h"

void mx_print_dirs_with_flag_l(t_list* dirs_with_p, int flag_mask,  bool only_one) {
	t_list *tmp_dirs = dirs_with_p; 
	
	while(tmp_dirs) {
		dir_with_prop_t *dir = tmp_dirs->data;
		t_list* tmp_files = dir->files_with_prop;
		int total_blocks = 0;
		bool last = tmp_dirs->next == NULL;

		if(!only_one) {
			mx_printstr(dir->dir_name);
			mx_printstr(":\n");
		}
		
		if (tmp_files != NULL) {
			while(tmp_files) {
				file_with_prop_t* f = (file_with_prop_t*)tmp_files->data;
				total_blocks += f->count_blocks;
				tmp_files = tmp_files->next;
			}
			mx_printstr("total ");
			mx_printint(total_blocks);
			mx_printstr("\n");
		}

		tmp_files = dir->files_with_prop;
		mx_print_files_with_flag_l(tmp_files, flag_mask, last);
		tmp_dirs = tmp_dirs->next;
	}
}

