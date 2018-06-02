#ifndef STR_LIB_H
#define STR_LIB_H

#include "all.h"

#ifdef __WIN32__
typedef LPSTR str_type;
#else
typedef char* str_type;
#endif // __WIN32__

str_type my_itoa(int32 value, str_type str, int32 radix);

int32 my_atoi(str_type str);

str_type my_strcpyn(str_type dest, str_type src, int32 len);

str_type strcpy_2n(str_type dest, str_type src);

str_type strcat_2n(str_type dest, str_type src);

str_type stradd_2n(str_type src);

bool b_strcmpi(str_type s1, str_type s2);

int32 read_filename_string(char **out, const char *init_str,
                         int32 max_files, bool dir_inc);


str_type time_string(int32 ms, str_type dest);

str_type Proper_Filename(str_type s);

int32 CDTrack_number(str_type current, str_type next, str_type src);

bool multi_file_select(str_type s);

#endif

