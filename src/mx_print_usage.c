#include "../inc/uls.h"

void mx_print_usage(void) {
    const char* usage = "usage: uls [-l] [file ...]\n";
    write(2, usage, mx_strlen(usage));
}


