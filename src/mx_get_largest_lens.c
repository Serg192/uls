#include "../inc/uls.h"

largest_file_prop_lens_t* mx_get_largest_lens(t_list *files) {
	largest_file_prop_lens_t *largest_lens = (largest_file_prop_lens_t*)malloc(sizeof(largest_file_prop_lens_t));

	int largest_number_of_links_len = -1;
	int largest_owner_name_len = -1;
	int largest_group_name_len = -1;
	int largest_file_size_len = -1;
	
	t_list *tmp = files;
	while(tmp) {
		file_with_prop_t* file = tmp->data;
		
		char* str_number_of_links = mx_itoa(file->number_of_links);
		if(mx_strlen(str_number_of_links) > largest_number_of_links_len) {
			largest_number_of_links_len = mx_strlen(str_number_of_links);
		}		

		if(mx_strlen(file->owner_name) > largest_owner_name_len) {
			largest_owner_name_len = mx_strlen(file->owner_name);
		}
		
		if(mx_strlen(file->group_name) > largest_group_name_len) {
			largest_group_name_len = mx_strlen(file->group_name);
		}

		char* str_file_size = mx_itoa(file->file_size);
		if(mx_strlen(str_file_size) > largest_file_size_len) {
			largest_file_size_len = mx_strlen(str_file_size);
		}
		
		free(str_number_of_links);
		free(str_file_size);
		tmp = tmp->next;
	}

	largest_lens->largest_number_of_links_len = largest_number_of_links_len;
	largest_lens->largest_owner_name_len = largest_owner_name_len;
	largest_lens->largest_group_name_len = largest_group_name_len;
	largest_lens->largest_file_size_len = largest_file_size_len;
	
	return largest_lens;	
}

