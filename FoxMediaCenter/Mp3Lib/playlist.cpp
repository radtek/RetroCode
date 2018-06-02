#ifdef __WIN32__
#define STRICT
#include <windows.h>
#include "str_lib.h"
#else
#include <stdio.h>
#endif // __WIN32__

#ifdef GUI

#ifdef   WIN32GUI

#else
#include <iostream.h>
#endif // WIN32GUI

#endif // GUI

#include <fstream.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "all.h"
#include "playlist.h"

bool is_list(const char *fn)
{
	return((strlen(fn) > 4) &&
          ((stricmp(fn + strlen(fn)-4, ".TXT")==0) ||
           (stricmp(fn + strlen(fn)-4, ".LST")==0) ||
           (stricmp(fn + strlen(fn)-4, ".M3U")==0)));
}

const char *first_nonwhite(const char *src)
// Returns the position of the first character that is not a space or
// a tab. No, I am not a racist.
{
	const char *result = src;

   while ((*result == ' ') || (*result == '\t'))
   	result++;

   return result;
}

bool all_white(const char *src)
// True if the string contains only spaces and tabs.
{
	const char *fnw_str = first_nonwhite(src);

   return (bool) (*fnw_str == '\0');
}

char *dir_expand(char *dest, const char *src, const char *base_path)
// Expands the pathname if %BASE_DIR% is used.
{
   char temp[16];

   strncpy(temp, src, 10);
   temp[10]='\0';

   if (strcmpi(temp, "%BASE_DIR%") == 0) {

		strcpy(dest, base_path);
      strcat(dest, src+10);

   } else {

   	strcpy(dest, src);
   }

   return dest;
}

char *dir_contract(char *dest, const char *src,
			          const char *base_path)
// Replaces the partial pathname with %BASE_DIR% if found
{
	char  temp[MAX_FILENAME_LENGTH];
	int32 dir_length = strlen(base_path);

   strcpy(temp, src);
   temp[dir_length] = '\0';

   if (strcmpi(temp, base_path) == 0) {
   	strcpy(dest, "%BASE_DIR%");
      strcat(dest, src+dir_length);
   } else {
   	strcpy(dest, src);
   }
   return dest;
}

PlayListItem::PlayListItem()
{
   filename = NULL;
   alias    = NULL;
   lyric_filename = NULL;
   image_filename = NULL;

   list_frequency = 1.0f;
   scalefactor    = 32768.0f;

   sort_index = 0;
   del_mark   = false;
   select_mark = false;
}

PlayListItem::PlayListItem(const char *fn)
{
   filename = new char[strlen(fn)+1];
   strcpy(filename, fn);

   alias = NULL;
   lyric_filename = NULL;
   image_filename = NULL;

   list_frequency = 1.0f;
   scalefactor    = 32768.0f;

   sort_index = 0;
   del_mark   = false;
   select_mark = false;
}

PlayListItem::PlayListItem(const PlayListItem &pli0)
{
 	if (pli0.filename) {
     	filename = new char[strlen(pli0.filename)+1];
     	strcpy(filename, pli0.filename);
   } else {
     	filename = NULL;
   }

  	if (pli0.alias) {
    	alias = new char[strlen(pli0.alias)+1];
     	strcpy(alias, pli0.alias);
   } else {
     	alias = NULL;
   }

  	if (pli0.lyric_filename) {
    	lyric_filename = new char[strlen(pli0.lyric_filename)+1];
     	strcpy(lyric_filename, pli0.lyric_filename);
   } else {
     	lyric_filename = NULL;
   }

   if (pli0.image_filename) {
    	image_filename = new char[strlen(pli0.image_filename)+1];
    	strcpy(image_filename, pli0.image_filename);
   } else {
     	image_filename = NULL;
   }

   list_frequency = pli0.list_frequency;

   scalefactor    = pli0.scalefactor;

   sort_index = 0;
   del_mark   = false;
   select_mark = false;
}

PlayListItem::~PlayListItem()
{
 	if (filename) delete [] filename;
   if (alias)    delete [] alias;
   if (lyric_filename) delete [] lyric_filename;
   if (image_filename) delete [] image_filename;
}

PlayListItem& PlayListItem::operator = (const PlayListItem &pli0)
{
  	if (pli0.filename) {
     	filename = new char[strlen(pli0.filename)+1];
     	strcpy(filename, pli0.filename);
   } else {
     	if (filename)
        	delete [] filename;
      filename = NULL;
   }

 	if (pli0.alias) {
     	alias = new char[strlen(pli0.alias)+1];
     	strcpy(alias, pli0.alias);
   } else {
    	if (alias)
        	delete [] alias;
      alias = NULL;
   }

  	if (pli0.lyric_filename) {
    	lyric_filename = new char[strlen(pli0.lyric_filename)+1];
     	strcpy(lyric_filename, pli0.lyric_filename);
   } else {
     	if (lyric_filename)
        	delete [] lyric_filename;
      lyric_filename = NULL;
   }

  	if (pli0.image_filename) {
    	image_filename = new char[strlen(pli0.image_filename)+1];
     	strcpy(image_filename, pli0.image_filename);
   }  else {
     	if (image_filename)
       	delete [] image_filename;
      image_filename = NULL;
   }

   list_frequency = pli0.list_frequency;

   scalefactor    = pli0.scalefactor;

   sort_index = 0;
   del_mark   = false;
   select_mark = false;

   return *this;
}

void PlayListItem::set_filename(const char *fn)
{
  	if (filename)
     	delete [] filename;

  	if ((fn == NULL) || (strcmp(fn, "") == 0)) {
     	filename = NULL;
     	return;
   }

	filename = new char [strlen(fn)+1];
   strcpy(filename, fn);
}

void PlayListItem::set_alias(const char *name)
{
  	if (alias)
    	delete [] alias;

  	if ((name == NULL) || (strcmp(name, "") == 0)) {
		alias = NULL;
     	return;
   }

	alias = new char [strlen(name)+1];
   strcpy(alias, name);
}

void PlayListItem::set_lyric_filename(const char *lfn)
{
  	if (lyric_filename)
     	delete [] lyric_filename;

	if ((lfn == NULL) || (strcmp(lfn, "") == 0)) {
     	lyric_filename = NULL;
     	return;
   }

	lyric_filename = new char [strlen(lfn)+1];
   strcpy(lyric_filename, lfn);
}

void PlayListItem::set_image_filename(const char *ifn)
{
  	if (image_filename)
     	delete [] image_filename;

  	if ((ifn == NULL) || (strcmp(ifn, "") == 0)) {
     	image_filename = NULL;
     	return;
   }

	image_filename = new char [strlen(ifn)+1];
   strcpy(image_filename, ifn);
}

int pli_compare(const void *item1, const void *item2)
{
	PlayListItem *pli1 = (PlayListItem *) *((PlayListItem **) item1);
	PlayListItem *pli2 = (PlayListItem *) *((PlayListItem **) item2);

   if (*pli1 < *pli2)
   	return -1;
   else if (*pli1 == *pli2)
   	return 0;
   else
   	return 1;
}

FileList::FileList()
{
   reset(true);

  	check_files = true;
  	warn = true;
   save_relative = true;
   save_expand   = false;

#ifdef WIN32GUI
	warn_hWnd = NULL;
#endif
}

FileList::FileList(const FileList &fl0)
{
 	int32 i;

   reset(true);

   for (i=0; i<fl0.entries; i++) {
      pli_array[i] = new PlayListItem(*(fl0.pli_array[i]));
      entries++;
   }

  	check_files = fl0.check_files;
  	warn = fl0.warn;
   save_relative = fl0.save_relative;
   save_expand   = fl0.save_expand;

   if (fl0.list_name) {
	   list_name = new char[strlen(fl0.list_name)+1];
      strcpy(list_name, fl0.list_name);
   }

#ifdef WIN32GUI
	warn_hWnd = fl0.warn_hWnd;
#endif
}

#ifdef __WIN32__
FileList::FileList(const char *init_str, bool dir_inc)
{
	reset(true);

  	check_files = true;
  	warn = true;
   save_relative = true;
   save_expand   = false;

#ifdef WIN32GUI
	warn_hWnd = NULL;
#endif // WIN32GUI

   read_from_string(init_str, dir_inc, PL_OVERWRITE, 0);
}
#endif // __WIN32__

FileList &FileList::operator = (const FileList &fl0)
{
	int32 i;

   reset(false);

   for (i=0; i<fl0.entries; i++) {
      pli_array[i] = new PlayListItem(*(fl0.pli_array[i]));
      entries++;
   }

  	check_files = fl0.check_files;
  	warn = fl0.warn;
   save_relative = fl0.save_relative;
   save_expand   = fl0.save_expand;

   if (fl0.list_name) {
	   list_name = new char[strlen(fl0.list_name)+1];
      strcpy(list_name, fl0.list_name);
   }

#ifdef WIN32GUI
	warn_hWnd = fl0.warn_hWnd;
#endif

   return *this;
}


FileList::~FileList()
{
  	int32 i;

  	for (i=0; i<MAX_SONGS; i++) {
     	if (pli_array[i]) {
       	delete pli_array[i];
      }
   }

   if (list_name) delete [] list_name;
}

char *FileList::get_track_display_at(char *dest, int32 i, bool no_alias) const
{
   char *alias0;

   if ((i < 0) || (i >= entries))
   	return NULL;

	itoa(i+1, dest, 10);

   strcat(dest, ". ");

   alias0 = pli_array[i]->get_alias();

   if (!no_alias && (alias0 != NULL))
      strcat(dest, alias0);
   else
   	strcat(dest, Proper_Filename(pli_array[i]->get_filename()));

   return dest;
}

bool FileList::save(const char *filename) const
{
	int32 i;
   char pathname[MAX_FILENAME_LENGTH];
   char temp[MAX_FILENAME_LENGTH];

	ofstream ofs(filename);

   if (ofs.fail()) return false;

   if (list_name != NULL)
   	ofs << "#n " << list_name << endl;

   strcpy(pathname, filename);

   i = strlen(pathname)-1;

   while ((pathname[i] != DIR_MARKER) && (i>0)) {
   	i--;
   }

   pathname[i] = '\0';

   for (i=0; i<entries; i++) {

      ofs << (save_relative ? dir_contract(temp,
                               pli_array[i]->get_filename(),
                               pathname)
                            : pli_array[i]->get_filename())
   	       << endl;

      if (pli_array[i]->get_alias())
      	ofs << "\#a " << pli_array[i]->get_alias() << endl;

      if (pli_array[i]->get_lyric_filename()) {
      	ofs << "\#l " << (save_relative ? dir_contract(temp,
                                            pli_array[i]->get_lyric_filename(),
                                            pathname)
                       					     : pli_array[i]->get_lyric_filename())
         	 << endl;
      }

      if (pli_array[i]->get_image_filename()) {
      	ofs << "\#i " << (save_relative ? dir_contract(temp,
                                            pli_array[i]->get_image_filename(),
                                            pathname)
                       					     : pli_array[i]->get_image_filename())
         	 << endl;
      }

      if (pli_array[i]->get_list_frequency()!= 1.0)
      	ofs << "\#f " << pli_array[i]->get_list_frequency() << endl;

      ofs << endl;
   }

   ofs.close();

   return true;
}

void FileList::reset(bool construct)
{
  	int32 i;
	static bool rand_init = false;

   if (!rand_init) {
	   time_t t;
		srand((unsigned) time(&t));
      rand_init = true;
   }

   if (construct) {

   	for (i=0; i<MAX_SONGS; i++)
      	pli_array[i] = NULL;

      list_name = NULL;

   } else {

	  	for (i=0; i<entries; i++) {
	     	if (pli_array[i]) {
	        	delete pli_array[i];
	         pli_array[i] = NULL;
	      }
	   }

	   if (list_name) {
	   	delete [] list_name;
		   list_name = NULL;
   	}
   }

   recursion_level = 0;
   entries = 0;
}

#ifdef __WIN32__
int32 FileList::read_from_string(const char *init_str, bool dir_inc,
                                 enum pl_add_mode add_mode,
                                 int32 start_index)
// Read from a string of filenames separated by '\0' characters.
// If dir_inc is true, the first string is the directory path
// for the rest of the strings.
{
   char *filenames[MAX_SONGS];
   bool  add_ok[MAX_SONGS];
   int32 num_in_list;
   int32 ok_entries;
 	int32 i, j;

   if (add_mode == PL_OVERWRITE) {
      reset(false);
   }

   if (start_index == -1)
   	start_index = entries;

   if (start_index > entries)
   	return 0;

	num_in_list = read_filename_string(filenames, init_str,
                                      MAX_SONGS, dir_inc);

	if (check_files) {

   	ok_entries = 0;
	   for (i=0; i<num_in_list; i++) {
			if (!file_ok(filenames[i])) {
         	add_ok[i] = false;

				if (warn) {
            	display_bad_file_warning(filenames[i]);
            } // if (warn)
         } else {
         	add_ok[i] = true;
            ok_entries++;
         } // if (bad file)
      } // for (i=0; i<num_in_list ...

   } else {
   	ok_entries = num_in_list;
   } // if (check_files)

   if ((entries + ok_entries) > MAX_SONGS)
   	ok_entries = MAX_SONGS - entries;

   if (start_index < entries) {
   	for (i=entries+ok_entries-1; i>=(start_index+ok_entries); i--)
      	pli_array[i] = pli_array[i - ok_entries];
   } // if (start_index < entries)

   j = 0;
   for (i=start_index; i<start_index+ok_entries; i++) {

   	if (check_files) {
	   	while(!add_ok[j])
		      	j++;
      }

      pli_array[i] = new PlayListItem(filenames[j]);
      j++;
   }

   entries += ok_entries;

   for (i=0; i<num_in_list; i++)
       delete [] filenames[i];

   return ok_entries;
}
#endif // __WIN32__

int32 FileList::read_from_file(const char *fn, bool append,
								       bool recurse)
{
	ifstream f(fn);
   char f_s[MAX_FILENAME_LENGTH];
   char base_path[MAX_FILENAME_LENGTH];
   char scratch[MAX_FILENAME_LENGTH+32];
   const char *temp;
	bool add_ok;
   int32 entries_read = 0;

   if (!append) {
      reset(false);
   }

   // get base path
   {
	   strcpy(base_path, fn);

   	int32 path_end = strlen(base_path) - 4;

      while (base_path[path_end] != DIR_MARKER)
      	path_end--;

      base_path[path_end] = '\0';
   }

	while(!(f.eof() || f.fail() || (entries>=MAX_SONGS-1))) {

   	do {

	      f.getline(scratch, MAX_FILENAME_LENGTH, '\n');

         if (!all_white(scratch)) {

	         if (scratch[0] == '#') {

               if ((recursion_level == 0) && (entries == 0)) {
               	// process global list options
                  switch (scratch[1]) {

                   case 'N':
                   case 'n':
                   temp = first_nonwhite(scratch+2);
                   if (!list_name) {
                      list_name = new char[strlen(temp)+1];
                      strcpy(list_name, temp);
                   }
						 break;

                   default:
                   break;
                  } // switch(scratch[1])

   	      	} else {
	   	      	// process options for [entries-1]
	      	      switch (scratch[1]) {

                   case 'A':
	         	    case 'a':
                	 pli_array[entries-1]->
                   	set_alias(first_nonwhite(scratch+2));
	             	 break;

                   case 'I':
	         	    case 'i':
               	 dir_expand(f_s, first_nonwhite(scratch+2), base_path);
                	 pli_array[entries-1]->set_image_filename(f_s);
	             	 break;

                   case 'L':
	             	 case 'l':
					 	 dir_expand(f_s, first_nonwhite(scratch+2), base_path);
                	 pli_array[entries-1]->set_lyric_filename(f_s);
	             	 break;

                   case 'F':
                	 case 'f':
                	 pli_array[entries-1]->
                	  set_list_frequency(atof(first_nonwhite(scratch+2)));
                	 break;

	             	 default:
	             	 // Unknown option
   	          	 break;
                  } // switch (scratch[i])
            	} // if (entries > 0)

  	         } else {

         		add_ok = true;

	            // mandatory check needed for garbage read in
   	         if (strlen(scratch) <= 1)
	            	add_ok = false;

	            dir_expand(f_s, scratch, base_path);

					if (add_ok & check_files) {
	            	if (!file_ok(f_s)) {

   	            	add_ok = false;

							if (warn) {
   	               	display_bad_file_warning(f_s);
							} // warn

						} // if (bad file)
					} // check_files

	            if (add_ok) {
               	if (recurse && is_list(f_s)) {
                     ++recursion_level;

                     if (recursion_level > MAX_RECURSION) {
								display_recursion_warning();
                        return entries_read;
                     }
                     read_from_file(f_s, true, true);
                     --recursion_level;
               	} else {
	               	if (append_to_list(f_s))
	                  	entries_read++;
                  } // if (recurse && is_list)
            	}  // if (add_ok)

         	} // if (scratch[0] == '#')
         } // if (!all_white(scratch)

   	} while ((f_s[0]=='#') &&
      			 !(f.eof() || f.fail()) &&
                (entries<MAX_SONGS-1));

	} // while (file stream good)

	f.close();

   if (entries_read <= 0) {
		strcpy(scratch, "Unable to open the playlist \"");
      strcat(scratch, fn);
      strcat(scratch, "\".");
	//MessageBox(warn_hWnd, scratch, "Error opening playlist",
	MessageBox(NULL, scratch, "Error opening playlist",
                 MB_OK | MB_ICONEXCLAMATION);
	}

   return entries_read;
}


void FileList::randomize_order()
{
	int32 i;

   for (i=0; i<entries; i++)
   	pli_array[i]->set_sort_index(rand());

   sort_by_index();
}

void FileList::sort_by_index(int32 start_index, int32 end_index)
{
   if (end_index < 0)
      end_index = entries;

   qsort(pli_array + start_index,
         end_index - start_index, sizeof(PlayListItem *),
         pli_compare);
}

bool FileList::insert_entry(const char *song_name, int32 index)
{
	int32 i;

	if ((entries+1) < MAX_SONGS) {

     for (i=entries; i>index; i--)
     	   pli_array[i] = pli_array[i-1];
     pli_array[index] = new PlayListItem(song_name);
     entries++;
     return true;
   } else {
     return false;
	}
}

bool FileList::insert_entry(PlayListItem *pli, int32 index)
{
	int32 i;

	if ((entries+1) < MAX_SONGS) {

     for (i=entries; i>index; i--)
     	   pli_array[i] = pli_array[i-1];
     pli_array[index] = pli;
     entries++;
     return true;
   } else {
     return false;
	}
}

bool FileList::append_to_list(const char *song_name)
{
 	if ((entries+1) < MAX_SONGS) {
      pli_array[entries] = new PlayListItem(song_name);
      entries++;
      return true;
   } else {
     	return false;
   }
}

bool FileList::append_to_list(const PlayListItem &pli)
{
 	if ((entries+1) < MAX_SONGS) {
      pli_array[entries] = new PlayListItem(pli);
      entries++;
      return true;
   } else {
     	return false;
   }
}

int32 FileList::remove_marked_entries()
{
	int32 i=0;
   int32 j;
   int32 entries_removed=0;

	while (i < entries) {

   	if (pli_array[i]->get_del_mark()) {
      	delete pli_array[i];
         pli_array[i] = NULL;
         entries_removed++;

      	for (j=i; j<entries-1; j++)
         	pli_array[j] = pli_array[j+1];

         pli_array[entries-1] = NULL;

         entries--;
      } else {
      	i++;
      }
   }
   return entries_removed;
}

bool FileList::remove_from_list(int32 index)
{
	int32 i;

	if ((index >= 0) && (index < entries)) {

   	delete pli_array[index];
      pli_array[index] = NULL;

      for (i=index; i<(entries-1); i++)
			pli_array[i] = pli_array[i+1];

      pli_array[entries-1] = NULL;

      entries--;

      return true;

   } else {
   	return false;
   }
}

bool FileList::remove_all_occurences(const char *filename)
{
   // slow, O(n^2) algorithm

   int32 i = 0;
   int32 j;
   int32 occurences = 0;

   while (i < entries) {

     	if (strcmpi(pli_array[i]->get_filename(), filename) == 0) {

        	occurences++;

         delete pli_array[i];
         pli_array[i] = NULL;

	      for (j=i; j<(entries-1); j++)
				pli_array[j] = pli_array[j+1];

	  	   pli_array[entries-1] = NULL;

      	entries--;

      } else {

         i++;
      }

   } // while (i < entries)

   return (bool) (occurences > 0);
}

bool FileList::shift_up_selected()
{
   int32 i;
   int32 entries_selected = 0;
   int32 first_select_pos = entries;
   int32 last_select_pos = -1;

   for (i=0; i<entries; i++) {
   	if (pli_array[i]->get_select_mark()) {

         entries_selected++;

      	if (i < first_select_pos)
            first_select_pos = i;

      	if (i > last_select_pos)
            last_select_pos = i;
      }
   }

   if (first_select_pos <= 0) {
      set_select_marks(false, first_select_pos, last_select_pos + 1);
      return false;
   }

   if (entries_selected <= 0)
      return false;

   int32 first_mod_pos = first_select_pos - 1;
   int32 sel_sort_index = first_mod_pos;
   int32 sel_entries_left = entries_selected;

   for (i=first_mod_pos; i<(last_select_pos + 1); i++) {
   	if (pli_array[i]->get_select_mark()) {
        pli_array[i]->set_sort_index(sel_sort_index);
        sel_sort_index++;
        pli_array[i]->set_select_mark(false);
        sel_entries_left--;
      } else {
        pli_array[i]->set_sort_index(i + sel_entries_left);
      }
   }

   sort_by_index(first_mod_pos, last_select_pos + 1);
   return true;
}

bool FileList::shift_down_selected()
{
   int32 i;
   int32 first_select_pos;
   int32 last_select_pos = -1;
   bool  sel_found = false;

   i = 0;

   while ((i<entries) && (!sel_found)) {

      if (pli_array[i]->get_select_mark()) {
         first_select_pos = i;
         sel_found = true;
      }

      i++;
   }

   if (!sel_found)
      return false;

   int32 sel_sort_index = entries;
   int32 unsel_sort_index = 0;

   for (i=first_select_pos; i<entries; i++) {

   	if (pli_array[i]->get_select_mark()) {

         if (i > last_select_pos)
            last_select_pos = i;

         pli_array[i]->set_select_mark(false);
         pli_array[i]->set_sort_index(sel_sort_index);
         sel_sort_index++;
      } else {
         pli_array[i]->set_sort_index(unsel_sort_index);
         unsel_sort_index++;
      }
   }

   if (last_select_pos + 1 >= entries ) {
      set_select_marks(false, first_select_pos);
      return false;
   }

   sort_by_index(first_select_pos, last_select_pos + 2);
   return true;
}

void FileList::set_select_marks(bool mark, int32 from, int32 to)
{
   int32 i;

   if (to == -1)
      to = entries;

   for (i=from; i<to; i++) {
   	pli_array[i]->set_select_mark(mark);
   }
}

bool FileList::file_ok(const char *fn) const
{
	if (strcmpi(".CDA", fn+strlen(fn)-4) == 0)
      return true;

#ifdef __WIN32__

	return (GetFileAttributes(fn) != 0xFFFFFFFF);

#else
	// This is a bit ugly, I'm open to an alternative method

   FILE *fd = fopen(fn, "r");

   if (fd == NULL) {
      return false;
   } else {
      fclose(fd);
      return true;
   }

#endif // __WIN32__
}


void FileList::display_bad_file_warning(const char *f_s)
{
	char warn_message[MAX_FILENAME_LENGTH+32];
   strcpy(warn_message, "Invalid file in playlist : \"");
   strcat(warn_message, f_s);
   strcat(warn_message, "\". File will not be added.\n"
     							"Continue to warn? ");

#ifdef WIN32GUI

 	if (MessageBox(warn_hWnd, warn_message, "Warning",
                  MB_ICONEXCLAMATION | MB_YESNO) == IDNO)
      warn = false;

#else

   char c;

   cerr << warn_message;

	cin >> c;
   if ((c=='n') || (c=='N'))
     	warn = false;

#endif // WIN32GUI
}

void FileList::display_recursion_warning() const
{
#ifdef WIN32GUI

   MessageBox(warn_hWnd,
              "The maximum level of list recursion has been exceeded. "
              "Check to make sure your list does not contain a cycle.",
              "List recursion error",
              MB_ICONEXCLAMATION);

#else

	cerr << "The maximum level of list recursion has been exceeded. "
           "Check to make sure your list does not contain a cycle."
        << endl;

#endif // WIN32GUI
}

PlayList::PlayList()
{
	reset(true);

  	check_files = false;
  	warn = false;
   save_relative = true;
   save_expand   = false;

#ifdef WIN32GUI
	warn_hWnd = NULL;
#endif

}

PlayList::PlayList(const PlayList &pl0)
{
 	int32 i;

   reset(true);

  	check_files = pl0.check_files;
  	warn = pl0.warn;
   save_relative = pl0.save_relative;
   save_expand   = pl0.save_expand;

#ifdef WIN32GUI
	warn_hWnd = pl0.warn_hWnd;
#endif

   if (pl0.fl != NULL)
      fl = new FileList(*(pl0.fl));

   for (i=0; i<pl0.entries; i++) {
      pli_array[i] = new PlayListItem(*(pl0.pli_array[i]));
      entries++;
   }

   current_index = pl0.current_index;
}

PlayList::PlayList(const FileList &fl0)
{
   int32 fl_index = 0;

   reset(true);

   while ((fl_index < fl0.get_number_of_entries()) &&
          (entries < MAX_SONGS)) {

	  	if (is_list(fl0.get_item_at(fl_index).get_filename()))  {
   		if (recursion_level < MAX_RECURSION) {
      	   recursion_level++;
   	   	read_from_file(fl0.get_item_at(fl_index).get_filename(), true);
		      recursion_level--;
   	   } else {
	        	display_recursion_warning();
   	   }
	  	} else {
   	   	append_to_list(fl0.get_item_at(fl_index).get_filename());
	   } // if (is_list)

      fl_index++;
   }

  	check_files = fl0.get_entry_check();
  	warn = fl0.get_warn_level();
   save_relative = fl0.get_save_relative();
   save_expand   = fl0.get_save_expand();

   if (fl0.get_list_name()) {
	   list_name = new char[strlen(fl0.get_list_name())+1];
      strcpy(list_name, fl0.get_list_name());
   }

#ifdef WIN32GUI
	warn_hWnd = fl0.get_warn_hWnd();
#endif

   fl = new FileList(fl0);
}

#ifdef __WIN32__
PlayList::PlayList(const char *init_str, bool dir_inc)
{
	reset(true);

  	check_files = true;
  	warn = true;
   save_relative = true;
   save_expand   = false;

#ifdef WIN32GUI
	warn_hWnd = NULL;
#endif // WIN32GUI

   read_from_string(init_str, dir_inc, PL_OVERWRITE, 0);
}
#endif // __WIN32__

PlayList::~PlayList()
{
   if (fl != NULL) delete fl;
}

PlayList &PlayList::operator = (const PlayList &pl0)
{
	int32 i;

   reset(false);

  	check_files = pl0.check_files;
  	warn = pl0.warn;
   save_relative = pl0.save_relative;
   save_expand   = pl0.save_expand;

   if (pl0.list_name) {
	   list_name = new char[strlen(pl0.list_name)+1];
      strcpy(list_name, pl0.list_name);
   }

#ifdef WIN32GUI
	warn_hWnd = pl0.get_warn_hWnd();
#endif

   if (pl0.fl != NULL)
      fl = new FileList(*(pl0.fl));

   for (i=0; i<pl0.entries; i++) {
      pli_array[i] = new PlayListItem(*(pl0.pli_array[i]));
      entries++;
   }

   current_index = pl0.current_index;

   return *this;
}

PlayList& PlayList::operator = (const FileList &fl0)
{
   int32 fl_index = 0;

   reset(false);

   while ((fl_index < fl0.get_number_of_entries()) &&
          (entries < MAX_SONGS)) {

	  	if (is_list(fl0.get_item_at(fl_index).get_filename()))  {
   		if (recursion_level < MAX_RECURSION) {
      	   recursion_level++;
   	   	read_from_file(fl0.get_item_at(fl_index).get_filename(), true);
		      recursion_level--;
   	   } else {
	        	display_recursion_warning();
   	   }
	  	} else {
   	   	append_to_list(fl0.get_item_at(fl_index));
	   } // if (is_list)

      fl_index++;
   }

  	check_files = fl0.get_entry_check();
  	warn = fl0.get_warn_level();
   save_relative = fl0.get_save_relative();
   save_expand   = fl0.get_save_expand();

   if (fl0.get_list_name()) {
	   list_name = new char[strlen(fl0.get_list_name())+1];
      strcpy(list_name, fl0.get_list_name());
   }

#ifdef WIN32GUI
	warn_hWnd = fl0.get_warn_hWnd();
#endif

   fl = new FileList(fl0);

	return *this;
}

void PlayList::reset(bool construct)
{
   FileList::reset(construct);

   current_index = 0;

   if (construct) {
   	fl = NULL;
   } else {
	   if (fl) {
	   	delete fl;
	      fl = NULL;
	   }
   }
}

int32 PlayList::read_from_string(const char *init_str, bool dir_inc,
									     enum pl_add_mode add_mode,
                                int32 start_index)
// Read from a string of filenames separated by '\0' characters.
// If dir_inc is true, the first string is the directory path
// for the rest of the strings.
{
   FileList t_fl(init_str, dir_inc);
   int32 entries_read = 0;

   if (start_index == -1)
      start_index = entries;

   switch (add_mode) {

     case PL_OVERWRITE:

     if (start_index == 0) {

       *this = t_fl;

     } else {

       PlayList t_pl = t_fl;

       entries_read = t_pl.get_number_of_entries();
       int32 i, j;

       if ((entries_read + start_index) > MAX_SONGS) {
          entries_read = MAX_SONGS - start_index;
       }

       j = 0;
       for(i=start_index; i<(start_index+entries_read);i++)
       {
       	 if (pli_array[i] != NULL) {
             *(pli_array[i]) = t_pl.get_item_at(j);
          } else {
             pli_array[i] = new PlayListItem(t_pl.get_item_at(j));
          }
          j++;
       }

       // delete extra stuff
       for(i=start_index+entries_read;i<entries;i++) {
          delete pli_array[i];
          pli_array[i] = NULL;
       }

       if (current_index >= start_index)
          current_index = 0;

       entries = start_index + entries_read;
     }
     break;

     case PL_INSERT:
     {
       PlayList t_pl = t_fl;

       entries_read = t_pl.get_number_of_entries();
       int32 i;

       if ((entries + entries_read) > MAX_SONGS) {
          entries_read = MAX_SONGS - entries;
       }

       for (i=entries + entries_read - 1;
            i>=(start_index + entries_read); i--) {
            pli_array[i] = pli_array[i - entries_read];
       }

       if (current_index >= start_index)
          current_index += entries_read;

       entries += entries_read;
     }
     break;

     case PL_APPEND:
     {
       PlayList t_pl = t_fl;

       entries_read = t_pl.get_number_of_entries();
       int32 i;

       if ((entries + entries_read) > MAX_SONGS) {
          entries_read = MAX_SONGS - entries;
       }

       for(i=0; i<entries_read; i++) {
          pli_array[entries + i] = new PlayListItem(t_pl.get_item_at(i));
       }
       entries += entries_read;
     }
     break;
   }

   return entries_read;
}

int32 PlayList::remove_marked_entries()
{
   bool ret_val = FileList::remove_marked_entries();

   if (current_index >= entries)
   	current_index -= entries;

   return ret_val;
}

bool PlayList::remove_from_list(int32 index)
{

	bool ret_val = FileList::remove_from_list(index);

   // should remove it from fl too, but where is it?

   if (current_index >= entries)
   	current_index -= entries;

   return ret_val;
}

bool PlayList::remove_all_occurences(const char *filename)
{
	bool ret_val = FileList::remove_all_occurences(filename);

   if (current_index >= entries)
   	current_index -= entries;

   if (fl) fl->remove_all_occurences(filename);

   return ret_val;
}

