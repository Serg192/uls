#include "../inc/uls.h"

static inline bool check_six_months_have_passed(struct stat *file_info) {
	time_t current_time = time(NULL);
    time_t last_modification_time = file_info->st_mtime;
    int six_months_in_seconds = 6 * 30 * 24 * 60 * 60;
    int delta_time = current_time - last_modification_time;
    
	if (delta_time < -six_months_in_seconds ||
		delta_time > six_months_in_seconds) {
		return true;
    } 
    
    return false;
}

void mx_set_last_modification_time(file_with_prop_t *file, struct stat *file_info) {	
	char *time = ctime(&file_info->st_mtime); 
	char *month = mx_strndup(time + 4, 4);
	
	char *temp_day = mx_strndup(time + 8, 3);
	char *day = NULL;
	if(mx_strlen(temp_day) < 2) {
		day = mx_strjoin(" ", temp_day);
	}
	else {
		day = mx_strdup(temp_day);
	} 
	
	char *hours_and_minutes = NULL;
	if(check_six_months_have_passed(file_info)) {
		char *temp_hours_and_minutes = mx_strndup(time + 20, 4);
		hours_and_minutes = mx_strjoin(" ", temp_hours_and_minutes);
		free(temp_hours_and_minutes);
	}
	else {
		hours_and_minutes = mx_strndup(time + 11, 5);
	}
	
	char *month_day = mx_strjoin(month, day);
	file->last_modification_time = mx_strjoin(month_day, hours_and_minutes);
	free(month);
	free(day);
	free(temp_day);
	free(hours_and_minutes);
	free(month_day);
	//mx_sttrdel(&last_mod_time);
}

