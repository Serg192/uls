#include "../inc/uls.h"

static inline char* build_output(const char* parent_prefix, const char* filename) {
    
    char* filepath = mx_strnew(mx_strlen(parent_prefix) + mx_strlen(filename) + 1);
    mx_strcat(filepath, parent_prefix);
    mx_strcat(filepath, "/");
    mx_strcat(filepath, filename);

    char* color = mx_get_file_color(filepath);
    char* output = mx_strnew(mx_strlen(filename) + mx_strlen(color) + mx_strlen(COLOR_RESET) + 1);
    mx_strcat(output, color);
    mx_strcat(output, filename);
    mx_strcat(output, COLOR_RESET);

    free(filepath);
    return output;
}

void mx_print_filename(const char* parent_prefix, const char* filename, int flag_mask){
    char* output = flag_mask & FLAG_G ? build_output(parent_prefix, filename) : mx_strdup(filename);
    mx_printstr(output);
    free(output);
}
