#include "../inc/uls.h"

static inline void check_ex_attributes_and_acl(file_with_prop_t *file, char *file_permissions) {
	if (file_permissions[0] == 'l') {
		int count;
		char buf[1024];
		count = readlink(file->path, buf, sizeof(buf) - 1);
		if (count > 0) {
			buf[count] = '\0';
			file->link = mx_strdup((char*)buf);
		}
	}

	char *buf = (char*) malloc(MAX_BUF_SIZE);
	bool has_ex_attributes = listxattr(file->path, buf, MAX_BUF_SIZE, XATTR_NOFOLLOW) > 0;
	acl_t acl = acl_get_file(file->path, ACL_TYPE_EXTENDED);
	bool has_acl = file_permissions[0] != 'l' && acl;

	if (has_ex_attributes) {
		file_permissions[10] = '@';
	}
	else if (has_acl) {
		file_permissions[10] = '+';
	}	

	free(buf);
	if (acl) {
		acl_free(acl);
	}
}

static inline void set_file_type(struct stat *file_info, char *file_permissions) {
	if (S_ISBLK(file_info->st_mode)) file_permissions[0] = 'b';
	if (S_ISCHR(file_info->st_mode)) file_permissions[0] = 'c';
	if (S_ISDIR(file_info->st_mode)) file_permissions[0] = 'd';
	if (S_ISLNK(file_info->st_mode)) file_permissions[0] = 'l';
	if (S_ISSOCK(file_info->st_mode)) file_permissions[0] = 's';
	if (S_ISFIFO(file_info->st_mode)) file_permissions[0] = 'p';
}

static inline void set_owner_permissions(struct stat *file_info, char *file_permissions) {
	if (file_info->st_mode & S_IRUSR) file_permissions[1] = 'r';
	if (file_info->st_mode & S_IWUSR) file_permissions[2] = 'w';
	if (file_info->st_mode & S_ISUID) {
		file_permissions[3] =  (file_info->st_mode & S_IXUSR) ? 's' : 'S';
	}
	else if (file_info->st_mode & S_IXUSR) file_permissions[3] = 'x';
}

static inline void set_group_permissions(struct stat *file_info, char *file_permissions) {
	if (file_info->st_mode & S_IRGRP) file_permissions[4] = 'r';
	if (file_info->st_mode & S_IWGRP) file_permissions[5] = 'w';
	if (file_info->st_mode & S_ISGID) {
		file_permissions[6] =  (file_info->st_mode & S_IXGRP) ? 's' : 'S';
	}
	else if (file_info->st_mode & S_IXGRP) file_permissions[6] = 'x';
}

static inline void set_other_permissions(struct stat *file_info, char *file_permissions) {
	if (file_info->st_mode & S_IROTH) file_permissions[7] = 'r';
	if (file_info->st_mode & S_IWOTH) file_permissions[8] = 'w';
	if (file_info->st_mode & S_ISVTX) {
		file_permissions[9] =  (file_info->st_mode & S_IXOTH) ? 't' : 'T';
	}
	else if (file_info->st_mode & S_IXOTH) file_permissions[9] = 'x';
}

void mx_set_file_permissions(file_with_prop_t *file, struct stat *file_info) {
	char file_permissions[] = "---------- ";

	set_file_type(file_info, file_permissions);
	set_owner_permissions(file_info, file_permissions);
	set_group_permissions(file_info, file_permissions);
	set_other_permissions(file_info, file_permissions);
	check_ex_attributes_and_acl(file, file_permissions);

	file->file_permissions = mx_strdup((char*)file_permissions);
}

