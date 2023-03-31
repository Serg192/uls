#include "../inc/uls.h"

//retun enum flag if flag is valid, -1 otherwise
static inline int is_valid_flag(char flag) {
	switch(flag) {
		case 'l' :
			return FLAG_l;
		case 'R' :
			return FLAG_R;
		case 'a':
			return FLAG_a;
		case 'A':
			return FLAG_A;
		case 'G':
			return FLAG_G;
		case '1':
			return FLAG_1;
		case 'C':
			return FLAG_C;
		default:
			return -1;
	}
}

static inline int* int_arr_grow(int* arr, const int old_len, int new_len) {
	int* new_arr = (int*)malloc(sizeof(int) * new_len);

	for(int i = 0; i < old_len; i++)
		new_arr[i] = arr[i];

	free(arr);
	return new_arr;
}

static inline void wrong_option(char flag) {
	const char* err = "uls: illegal option -- ";
	int err_len = mx_strlen(err);

	char* err_str = mx_strnew(err_len + 1);
	mx_strcpy(err_str, err);
	err_str[err_len] = flag;
	err_str[err_len + 1] = '\n';

	write(2, err_str, err_len + 2);

	mx_print_usage();
	exit(-1);
}

uls_command_t* mx_parse_uls_command(int argc, char* argv[]) {

	uls_command_t* command = (uls_command_t*)malloc(sizeof(uls_command_t));
	command->files_count = 0;
	command->flag_mask = 0;
	command->err_oc = false;
	command->dirs = 0;
	command->f_count = 0;
	command->files = NULL;

	int flags_arr_len = 4;
	int flags_arr_index = 0;

	command->flags = (int*)malloc(sizeof(int) * flags_arr_len);

	for(int i = 1; i < argc; i++) {
		const int word_len = mx_strlen(argv[i]);
		if(argv[i][0] == '-' && word_len > 1) {
			for(int j = 1; j < word_len; j++) {
				int fg = is_valid_flag(argv[i][j]);
				if(fg == -1) {
					wrong_option(argv[i][j]);
				} else {
					if(flags_arr_index == flags_arr_len - 2) {
						int n = flags_arr_len / 3 + 1;
						command->flags = int_arr_grow(command->flags, flags_arr_len, flags_arr_len + n);
						flags_arr_len += n;
					}
					command->flags[flags_arr_index++] = fg;
					command->flag_mask |= fg;
				}
			}
			
		} else {
			bool is_dir = mx_is_dir(argv[i]);
			if(is_dir || mx_is_file(argv[i])){
				mx_push_back(&(command->files), argv[i]);
				command->files_count++;
				if(is_dir) command->dirs++;
				else command->f_count++;
			} else {
				mx_printerr("uls: ");
				mx_printerr(argv[i]);
				mx_printerr(": No such file or directory\n");
				command->err_oc = true;
			}
		}
	}
	command->flags[flags_arr_index] = FLAGS_ARR_END;
	command->files = mx_sort_list(command->files, mx_string_comparator);
	return command;
}

