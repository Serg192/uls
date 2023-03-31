#include "../inc/uls.h"

void mx_set_file_prop(file_with_prop_t *file) {
	struct stat file_info; 
	struct passwd *pw; 
	struct group  *gr;

    lstat(file->path, &file_info);  
	file->link = NULL;
	mx_set_file_permissions(file, &file_info);
	
	file->number_of_links = (int)file_info.st_nlink;
	
	pw = getpwuid(file_info.st_uid);
	file->owner_name = pw ? mx_strdup(pw->pw_name) : mx_itoa((int)file_info.st_uid);

	gr = getgrgid(file_info.st_gid);
	file->group_name = gr ? mx_strdup(gr->gr_name) : mx_itoa((int)file_info.st_gid);

	file->file_size = (int)file_info.st_size;

	mx_set_last_modification_time(file, &file_info);
	
	file->count_blocks = file_info.st_blocks;
}

