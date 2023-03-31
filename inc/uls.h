#ifndef ULS_H
#define ULS_H

/* Allowed functions
 *
 write, malloc, malloc_size, free,
 perror, strerror, exit, opendir,
 readdir, closedir,stat, lstat, getpwuid, 
 getgrgid, listxattr, getxattr, time, ctime, 
 readlink, ioctl,isatty, acl_get_file, acl_to_text,
 acl_free, errno
 */

#include <libmx.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


#define COLOR_RESET "\x1B[0m"
#define COLOR_DIR   "\x1B[34m"
#define COLOR_LNK   "\x1B[35m"
#define COLOR_SOCK  "\x1B[32m"
#define COLOR_FIFO  "\x1B[33m"
#define COLOR_DEV   "\x1B[36m"
#define COLOR_EXEC  "\x1B[31m"

#define FLAGS_ARR_END -2

#define FLOOR(x) ((x) >= (int)(x) ? (int)(x) : (int)(x)-1)

#define MAX_BUF_SIZE 10000

//32 bit

enum flags {
    FLAG_l = 1,
    FLAG_R = 1 << 2,
	FLAG_A = 1 << 3,
	FLAG_a = 1 << 4,
	FLAG_G = 1 << 5,
	FLAG_1 = 1 << 6,
	FLAG_C = 1 << 7
};

typedef struct uls_command_s {
    int* flags;
    int flags_count;
    t_list* files;
    int files_count; // Dirs + files
    int flag_mask;
	int dirs;
	int f_count; // files only
	bool err_oc;
}              uls_command_t;

typedef struct files_list_s {
    t_list* files;
    int files_count;
}              files_list_t;

typedef struct file_with_prop_s {
	char *file_permissions;
	int number_of_links;
	char *owner_name;
	char *group_name;
	int file_size;
	char *last_modification_time;
	char *file_name;
	char *path;
	char *link;
	int count_blocks;
}			   file_with_prop_t;

typedef struct dir_with_prop_s {
	char *dir_name;
	t_list *files_with_prop;
}			   dir_with_prop_t;

typedef struct largest_file_prop_lens_s {
	int largest_number_of_links_len;
	int largest_owner_name_len;
	int largest_group_name_len;
	int largest_file_size_len;
}              largest_file_prop_lens_t;

////////////////////////////////////////////////////////////////////////////

typedef struct files_arr_s {
    int len;
    int capacity;
    char** files;
}              files_arr_t;

typedef struct column_params_s {
    int cols;
    int full_rows;
    int rows;
}              column_params_t;


files_arr_t* test_get_files_from_dir(const char* path, bool include_hidden);

void mx_sort_files(files_arr_t* arr);

void mx_free_strarr(char** arr, int len);

///////////////////////////////////////////////////////////////////////////

uls_command_t* mx_parse_uls_command(int argc, char* argv[]);

void mx_execute_uls_command(uls_command_t* command);

files_arr_t* mx_get_files_from_dir(const char* path, /*bool include_hidden*/int flag_mask);

files_arr_t* mx_file_names_to_arr(t_list* f_list);

void mx_print_usage(void);

void mx_print_files(files_arr_t* arr);

bool mx_is_file(const char* file);

bool mx_is_dir(const char* dir);

bool mx_is_link(char* link);

void mx_clear_files_arr(files_arr_t** arr);

void mx_clear_files_list(t_list* list);

int mx_get_largest_file_name_len(files_arr_t* files_arr);

bool mx_string_comparator(void* str1, void* str2);

void mx_calc_col_params(column_params_t* c_params, files_arr_t* files_arr, int largest_file_name_len);

void mx_find_max_str_in_each_col(files_arr_t* files_arr, column_params_t* c_params, int* max_col_str_len);

void mx_print_files_in_cols(const char* parent_pref, files_arr_t* files_arr, column_params_t* c_params, int* max_col_str_len, int flag_mask);

void mx_handle_disp_dir_in_col(uls_command_t* command, bool* is_file_a, bool files_were_printed);

//new func
void mx_handle_disp_dir_in_col_r(const char* parent_pref, files_arr_t* files_arr, int flag_mask);

bool mx_filter_and_print_files(uls_command_t* command, bool* is_file_a);

// new version of mx_filter_and_print_files function
bool mx_filter_files(files_arr_t* arr, bool* is_file_a);

char** mx_grow_char_arra(char** arr, int len, int new_capacity);

////////////////////////////////for -l/////////////////////////////////////

void mx_execute_with_flag_l(uls_command_t* command);

void mx_set_file_prop(file_with_prop_t *file);

void mx_set_file_permissions(file_with_prop_t *file, struct stat *file_info);

void mx_set_last_modification_time(file_with_prop_t *file, struct stat *file_info);

largest_file_prop_lens_t* mx_get_largest_lens(t_list *files);

void mx_print_files_with_flag_l(t_list *files_with_p, int flag_mask, bool new_line);

void mx_print_dirs_with_flag_l(t_list* dirs_with_p, int flag_mask, bool only_one);

void mx_clear_dirs_with_prop_list(t_list *list);

void mx_clear_dir_with_prop(dir_with_prop_t *dir_with_prop);

void mx_clear_files_with_prop_list(t_list *files_with_prop);

void mx_fill_dir_list(uls_command_t* command, files_arr_t* files_arr, t_list** dirs_with_p);

void mx_add_to_dir_list(dir_with_prop_t* dir, files_arr_t* files_arr, t_list* files_in_dir, t_list** dirs_with_p);

bool mx_check_char_delim(char *str);

///////////////////////////////////////////////////////////////////////////

char* mx_get_file_color(const char* filename);

void mx_print_filename(const char* parent_prefix, const char* filename, int flag_mask);

#endif
