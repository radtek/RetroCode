/* str_lib.cpp

   String manipulation routines for Win32 interface. Not needed
   for other operating systems. Bad programming by Jeff Tsay.

   Last modified : 06/21/97 */

#include <string.h>
#include "str_lib.h"

str_type my_itoa(int32 value, str_type str, int32 radix)
// Negative numbers not supported, nor radices bigger than 10
{
   char temp[256];

   if (value == 0) {
   	str[1] = '\0';
      str[0] = '0';

	} else {

	   temp[255]='\0';
      int32 last_index;

   	for(int32 i=254; i>=0, value>0; i--) {
      	int32 remainder = value % radix;
	      value /= radix;
   	   temp[i] = (char) (remainder + '0');
      	last_index = i;
	   }

   	strcpy(str, temp + last_index);
   }

   return str;
}

int32 my_atoi(str_type str)
// Negative numbers not supported
{
	int32 length = strlen(str);
   int32 base = 1;
   int32 result = 0;

   for(int32 i=length-1; i>=0; i--)
   {
		result += (str[i] - '0') * base;
      base = (base << 3) + (base << 1);  // base*=10;
   }

   return result;
}


str_type strcpy_2n(str_type dest, str_type src)
// Copies until 2 '\0' characters are reached
{
	int32 last_zero = 0;
   str_type temp_src = src;

   while (1) {
   	if ((*dest++ = *temp_src++) == '\0') {
      	if (last_zero) {
         	return dest;
         } else {
         	last_zero = 1;
         }
      } else {
      	last_zero = 0;
      }
   }
}

str_type strcat_2n(str_type dest, str_type src)
// Appends at the 2nd '\0' character
{
	int32 last_zero = 0;
   int32 found = 0;
   str_type temp_dest = dest;

   while (!found) {
      if (*temp_dest == '\0') {
      	if (last_zero) {
         	found = 1;
         } else {
         	last_zero = 1;
            temp_dest++;
         }
   	} else {
      	last_zero = 0;
         temp_dest++;
      }
   }

   strcpy_2n(temp_dest, src);

   return dest;
}

str_type stradd_2n(str_type src)
{
	*(src + strlen(src) + 1) = '\0';
   return src;
}

bool b_strcmpi(str_type s1, str_type s2)
// Case insensitive string compare that returns true if
// the strings match.
{
	return ((bool) (strcmpi(s1, s2) == 0));
}

int32 read_filename_string(char **out, const char *init_str,
                         int32 max_files, bool dir_inc)
{
	char path[MAX_PATH];
	const char *str_ptr = init_str;
   int32 path_length;
   int32 length;
	int32 entries_read = 0;

   if (*str_ptr == '\0')
   	return(0);

	if (dir_inc) {
	   strcpy(path, init_str);

      if (path[strlen(path)-1] != DIR_MARKER)
	   	strcat(path, DIR_MARKER_STR);

	   path_length = strlen(str_ptr);
   	str_ptr += (path_length+1);
   } else {
   	path_length = 0;
   }

	while ((*str_ptr != '\0') && (entries_read < max_files-1)) {

		length = strlen(str_ptr);

      out[entries_read] = new char[path_length+length+2];

      if (dir_inc) {
			strcpy(out[entries_read], path);
			strcat(out[entries_read], str_ptr);
      } else {
      	strcpy(out[entries_read], str_ptr);
      } // if (dir_inc)

      entries_read++;

   	str_ptr += (length+1);
   }

	return(entries_read);
}

str_type time_string(int32 ms, str_type dest)
{
	int32 i, j, nmlength;
	int32 seconds, minutes;
	char second_str[4];
	char minute_str[4];

	minutes = ms / 60000;
	seconds = ms / 1000 - minutes * 60;

	itoa(minutes, minute_str, 10);
	itoa(seconds, second_str, 10);

	nmlength = 3 - strlen(minute_str);

	for (i=0; i < nmlength ; i++)
		dest[i] = '0';

	for (i = nmlength, j=0; i<3; i++, j++)
		dest[i] = minute_str[j];

	dest[3] = ':';

	nmlength = 6 - strlen(second_str);

	for (i=4; i < nmlength ; i++)
		dest[i] = '0';

	for (i=nmlength, j=0; i<6; i++, j++)
		dest[i] = second_str[j];

	dest[6]='\0';

	return dest;
}

str_type Proper_Filename(str_type s)
{
	int32 length = strlen(s);

	for(int32 i=length; i>=0; --i)
		if (s[i]==DIR_MARKER)
			return (s+i+1);
	return s;
}

bool multi_file_select(str_type s)
{
	return (s[strlen(s)+1] != '\0');
}

int32 CDTrack_number(str_type current, str_type next, str_type src)
{
	int32 ret_val;
	int32 length = strlen(src);
   int32 chars_to_copy = 2;
   int32 i = length - 5;
   int32 next_track;

   while ((src[i]!='k') && (src[i]!='K') && (i>0)) {
   	chars_to_copy++;
      i--;
   };

   do {
	   i++;
      chars_to_copy--;
   } while (src[i]=='0');

   my_strcpyn(current, src + i, chars_to_copy);

   ret_val = atoi(current);
   next_track = ret_val + 1;

   itoa(next_track, next, 10);

   return ret_val;
}

str_type my_strcpyn(str_type dest, str_type src, int32 len)
{
	int32 chars_copied = 0;
   char  char_just_copied = '0';

   while ((chars_copied < (len-1)) && (char_just_copied != '\0')) {
   	dest[chars_copied] = src[chars_copied];
      char_just_copied   = src[chars_copied];
      chars_copied++;
   }

   if (char_just_copied != '\0')
      dest[chars_copied] = '\0';

   return dest;
}



