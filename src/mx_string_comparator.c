#include "../inc/uls.h"

/*
static inline bool is_upper_case(char c) {
	return c >= 'A' && c <= 'Z';
}

static inline char to_lower(char c) {
    return is_upper_case(c) ? c + 32 : c;
}

static int strcmp_ignore_case(const char *s1, const char *s2) {
    int i;
    for (i = 0; s1[i] && s2[i]; ++i) {
        if (to_lower(s1[i]) != to_lower(s2[i]))
            return (to_lower(s1[i]) < to_lower(s2[i])) ? -1 : 1;
    }
    return (s1[i] == s2[i]) ? 0 : (s1[i] < s2[i]) ? -1 : 1;
}
*/

bool mx_string_comparator(void* str1, void* str2) {
	//return strcmp_ignore_case((char*)str1, (char*)str2) >= 0; It's for Linux
    return mx_strcmp((char*)str1, (char*)str2) >= 0; // for mac
}


