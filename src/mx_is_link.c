#include "../inc/uls.h"

bool mx_is_link(char* link) {
	struct stat st;
	if(lstat(link, &st) == 0) {
        mx_strdel(&link);
        return S_ISLNK(st.st_mode);
    }
    mx_strdel(&link);
	return false;
}
