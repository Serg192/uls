#include "../inc/uls.h"

static inline void print_str_values(char *str, int largest_len) {
	mx_printstr(str);
		
	for(int i = mx_strlen(str); i < largest_len; i++) {
		mx_printstr(" ");
	}

	mx_printstr("  "); 	
}

static inline void print_int_values(int number, int largest_len) {
	char *str_number = mx_itoa(number);
	
	for (int i = mx_strlen(str_number); i < largest_len; i++) {
		mx_printstr(" ");
	}
	
	mx_printint(number); 
	mx_printstr(" ");
	free(str_number); 	
}

static inline void print_name(file_with_prop_t *file, int flag_mask) {
	if (flag_mask & FLAG_G) {
		char* color = mx_get_file_color(file->path);
		char* output = mx_strnew(mx_strlen(file->file_name) + mx_strlen(color) + mx_strlen(COLOR_RESET) + 1);
		mx_strcat(output, color);
		mx_strcat(output, file->file_name);
		mx_strcat(output, COLOR_RESET);
		mx_printstr(output);
		free(output);
	}
	else {
		mx_printstr(file->file_name);
	}

	if (file->file_permissions[0] == 'l') {
		mx_printstr(" -> ");
		mx_printstr(file->link);
	}
	mx_printstr("\n");
}

void mx_print_files_with_flag_l(t_list *files_with_p,  int flag_mask, bool new_line) {
	t_list* tmp = files_with_p;
	largest_file_prop_lens_t *largest_lens = mx_get_largest_lens(files_with_p);
	while (tmp) {
		file_with_prop_t* file = (file_with_prop_t*)tmp->data;
		
		mx_printstr(file->file_permissions);
		mx_printstr(" ");

		print_int_values(file->number_of_links, largest_lens->largest_number_of_links_len);
		
		print_str_values(file->owner_name, largest_lens->largest_owner_name_len);
		print_str_values(file->group_name, largest_lens->largest_group_name_len);

		print_int_values(file->file_size, largest_lens->largest_file_size_len);
		
		mx_printstr(file->last_modification_time); 
		mx_printstr(" "); 
		
		print_name(file, flag_mask);
		tmp = tmp->next;
	}
	if (!new_line) {
		mx_printstr("\n");
	}
	free(largest_lens);
}

