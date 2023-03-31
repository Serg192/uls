#include "../inc/uls.h"

bool mx_is_file(const char* file) {
	struct stat st;
	if(lstat(file, &st) == 0) 
        return S_ISREG(st.st_mode);
	return false;
}
