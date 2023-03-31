#include "../inc/uls.h"

char* mx_get_file_color(const char* filename){
    struct stat st;

    if (lstat(filename, &st) == -1)
        return COLOR_RESET;

     if (S_ISDIR(st.st_mode)) {
        return COLOR_DIR;
    } else if (S_ISLNK(st.st_mode)) {
        return COLOR_LNK;
    } else if (S_ISSOCK(st.st_mode)) {
        return COLOR_SOCK;
    } else if (S_ISFIFO(st.st_mode)) {
        return COLOR_FIFO;
    } else if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode)) {
        return COLOR_DEV;
    } else if (st.st_mode & S_IXUSR) {
        return COLOR_EXEC;
    }
    
    return COLOR_RESET;
}

