#include "../inc/uls.h"

bool mx_is_dir(const char* dir){
    DIR* d;
	if((d = opendir(dir)) == NULL) 
        return false;

	closedir(d);
    return true;
}

