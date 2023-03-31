#include "../inc/uls.h"

bool mx_check_char_delim(char *str) {
	if(str[mx_strlen(str)] == '/') {
		return true;
	}
	return false;
}
