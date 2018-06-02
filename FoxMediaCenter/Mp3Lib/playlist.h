#ifndef PLAYLIST_H
#define PLAYLIST_H

#ifdef WIN32GUI
#define STRICT
#include <windows.h>
#else
#include <stdlib.h>
#endif // WIN32GUI

#include <string.h>

#include "all.h"

#define MAX_SONGS 1024
#define MAX_FILENAME_LENGTH 256
#define MAX_RECURSION  8

bool is_list(const char *fn);

const char *first_nonwhite(const char *src);
bool  all_white(const char *src);
char *dir_expand(char *dest, const char *src, const char *base_path);
char *dir_contract(char *dest, const char *src, const char *base_path);

enum pl_add_mode {PL_OVERWRITE, PL_APPEND, PL_INSERT};

class PlayListItem {

public:

	PlayListItem();
	PlayListItem(const char *fn);
	PlayListItem(const PlayListItem &pli0);

   ~PlayListItem();

   PlayListItem &operator = (const PlayListItem &pli0);

   bool operator < (const PlayListItem &pli0) const
   {
   	return (bool) (sort_index < pli0.sort_index);
   }

	bool operator == (const PlayListItem &pli0) const
   {
   	return (bool) (sort_index == pli0.sort_index);
   }

   bool operator > (const PlayListItem &pli0) const
   {
   	return (bool) (sort_index > pli0.sort_index);
   }

   bool operator <= (const PlayListItem &pli0) const
   {
   	return (bool) (sort_index <= pli0.sort_index);
   }

   bool operator >= (const PlayListItem &pli0) const
   {
   	return (bool) (sort_index >= pli0.sort_index);
   }

	char *get_filename()       const { return filename;       }
	char *get_alias()          const { return alias;          }
	char *get_lyric_filename() const { return lyric_filename; }
	char *get_image_filename() const { return image_filename; }

   real  get_list_frequency() const { return list_frequency; }
	real  get_scalefactor()    const { return scalefactor;    }
	real  get_sort_index()     const { return sort_index;     }
   bool  get_del_mark()       const { return del_mark;       }
   bool  get_select_mark()    const { return select_mark;    }

   void set_filename(const char *fn);
   void set_alias(const char *name);
   void set_lyric_filename(const char *lfn);
   void set_image_filename(const char *ifn);

   bool set_list_frequency(real freq)
   {
   	if (freq < 0.0f) return false;

   	list_frequency = freq;
      return true;
   }

   void set_weighted_sort_index(int32 index)
   {
   	sort_index = (int32) (list_frequency * index);
   }

   void set_sort_index(int32 index)      { sort_index = index;    }
   void set_del_mark(bool mark=true)     { del_mark = mark;       }
   void set_select_mark(bool mark=true)  { select_mark = mark;    }

private:

   char *filename;
   char *alias;
	char *lyric_filename;
   char *image_filename;

   real list_frequency;

   real scalefactor;

   int32 sort_index;
   bool  del_mark;
   bool  select_mark;

};

int pli_compare(const void *item1, const void *item2);

class FileList {

public:

   FileList();
   FileList(const FileList &fl0);

#ifdef __WIN32__
   FileList(const char *init_str, bool dir_inc=false);
#endif // __WIN32__

   ~FileList();

   FileList &operator = (const FileList &fl0);

	int32 get_number_of_entries() const { return entries; }
   bool  empty() const { return (entries <= 0); }

   PlayListItem &get_item_at(int32 index) const
   {
   	if (index < 0)
         return (PlayListItem &) *(pli_array[-index]);
      else if (index >= entries)
      	return (PlayListItem &) *(pli_array[index % entries]);
      else
	   	return (PlayListItem &) *(pli_array[index]);
   }

   char *get_track_display_at(char *dest, int32 i,
                              bool no_alias = false)  const;

   bool  get_entry_check()   const  { return check_files;   }
	bool  get_warn_level()    const  { return warn;          }
   bool  get_save_relative() const  { return save_relative; }
	bool  get_save_expand()   const  { return save_expand;   }

   char *get_list_name() const { return list_name; }

#ifdef WIN32GUI
	HWND get_warn_hWnd() const { return warn_hWnd; }
#endif

   virtual bool  save(const char *filename) const;

   virtual void  reset(bool construct=false);

	virtual int32 read_from_file(const char *fn, bool append=false,
								        bool recurse=false);

#ifdef __WIN32__
   virtual int32 read_from_string(const char *init_str, bool dir_inc=false,
                                  enum pl_add_mode pam=PL_OVERWRITE,
                                  int32 start_index=0);
#endif

   bool file_ok(const char *fn) const;

   void set_entry_check(bool cf)   { check_files = cf;   }
   void set_warn_level(bool w)     { warn = w;           }
   void set_save_relative(bool r)  { save_relative = r;  }
	void set_save_expand(bool expd) { save_expand = expd; }

   void set_list_name(char *name)
   {
   	if (list_name) {
      	delete [] list_name;
         list_name = NULL;
      }
      if (!name || (name[0]=='\0')) return;

      list_name = new char[strlen(name)+1];
      strcpy(list_name, name);
   }

#ifdef WIN32GUI
   void set_warn_window(HWND hWnd) { warn_hWnd = hWnd; }
#endif

   bool set_del_mark_at(int32 index, bool mark = true)
   {
   	if ((index>= 0) && (index < entries)) {
			pli_array[index]->set_del_mark(mark);
         return true;
      } else {
      	return false;
      }
   }

   bool set_select_mark_at(int32 index, bool mark = true)
   {
   	if ((index>= 0) && (index < entries)) {
			pli_array[index]->set_select_mark(mark);
         return true;
      } else {
      	return false;
      }
   }
   
   void set_select_marks(bool mark = true, int32 from = 0, int32 to = -1);

   virtual void randomize_order();
   virtual void sort_by_index(int32 start_index = 0,
                              int32 end_index = -1);

   virtual bool  insert_entry(PlayListItem *pli, int32 index);
   virtual bool  insert_entry(const char *song_name, int32 index);

   bool append_to_list(const char *song_name);
   bool append_to_list(const PlayListItem &pli);

   bool shift_up_selected();
   bool shift_down_selected();

   virtual int32 remove_marked_entries();
   virtual bool  remove_from_list(int32 index);
   virtual bool  remove_all_occurences(const char *filename);

protected:

   PlayListItem *pli_array[MAX_SONGS];
   int32 entries;

   char *list_name;
   bool check_files;
   bool warn;
   bool save_relative;
   bool save_expand;

   int32 recursion_level;

#ifdef WIN32GUI
	HWND warn_hWnd;
#endif

	void display_bad_file_warning(const char *f_s);
   void display_recursion_warning() const;
};

class PlayList : public FileList {

public:

   PlayList();
   PlayList(const PlayList &pl0);
	PlayList(const FileList &fl0);
   PlayList(const char *init_str, bool dir_inc=false);

   ~PlayList();

   PlayList &operator = (const PlayList &pl0);
	PlayList &operator = (const FileList &fl0);

   int32 get_current_track() const { return current_index; }

   bool  has_filelist() const      { return (fl!=NULL); }

   const FileList &get_filelist() const
   {
	  	return (const FileList &) *fl;
   }

	char *get_previous_song_name() const
   {
   	if (current_index > 0)
	   	return pli_array[current_index-1]->get_filename();
 		else
      	return pli_array[entries-1]->get_filename();
   }

	char *get_previous_song_alias() const
   {
   	if (current_index > 0)
	   	return pli_array[current_index-1]->get_alias();
      else
		  	return pli_array[entries-1]->get_alias();
   }

	char *get_current_song_name() const
   {
   	return pli_array[current_index]->get_filename();
   }

	char *get_current_image_name() const
   {
   	return pli_array[current_index]->get_image_filename();
   }

	char *get_current_lyric_name() const
   {
   	return pli_array[current_index]->get_lyric_filename();
   }

	char *get_current_song_alias() const
   {
   	return pli_array[current_index]->get_alias();
   }

	char *get_next_song_name() const
   {
   	if (current_index < entries-1)
	   	return pli_array[current_index+1]->get_filename();
 		else
      	return pli_array[0]->get_filename();
   }

	char *get_next_song_alias() const
   {
   	if (current_index < entries-1)
	   	return pli_array[current_index+1]->get_alias();
      else
		  	return pli_array[0]->get_alias();
   }

   bool first_song() const
   {
   	return (current_index <= 0);
   }

   bool last_song() const
   {
   	return (current_index >= entries-1);
   }

   bool save(const char *filename) const
   {
   	return (save_expand ? FileList::save(filename)
                          : fl->save(filename));
   }

   void reset(bool construct=false);

	int32 read_from_file(const char *fn, bool append=false,
                        bool recurse=true)
   {
   	if (!recurse)
      	return 0;

      return FileList::read_from_file(fn, append, true);
   }

   int32 read_from_string(const char *init_str, bool dir_inc=false,
                          enum pl_add_mode add_mode=PL_OVERWRITE,
                          int32 start_index=0);

   char *goto_previous()
   {
   	current_index--;
      if (current_index < 0)
      	current_index+=entries;
      return pli_array[current_index]->get_filename();
   }

   char *goto_next()
   {
   	current_index++;
      if (current_index >= entries)
      	current_index-=entries;
      return pli_array[current_index]->get_filename();
   }

   char *goto_index(int32 index)
   {
   	if ((index >= 0) && (index < entries)) {
      	current_index = index;
	      return pli_array[current_index]->get_filename();
      } else {
      	return NULL;
      }
   }

   void randomize_order()
   {
   	FileList::randomize_order();
      current_index = 0;
   }

   void sort_by_index(int32 start_index = 0,
                      int32 end_index = -1)
   {
   	FileList::sort_by_index(start_index, end_index);
      current_index = 0;
   }

   bool insert_entry(PlayListItem *pli, int32 index)
   {
      bool shift = (index >= current_index);
      bool ret_val = FileList::insert_entry(pli, index);

      if (shift)
         current_index--;

      return ret_val;
   }

   bool insert_entry(const char *song_name, int32 index)
   {
      bool shift = (index >= current_index);
      bool ret_val = FileList::insert_entry(song_name, index);

      if (shift)
         current_index--;

      return ret_val;
   }

   bool set_current_track(int32 track)
   {
   	if ((track >= 0) && (track < entries)) {
	   	current_index = track;
         return true;
      } else {
	      return false;
      }
   }

	int32 remove_marked_entries();
   bool  remove_all_occurences(const char *filename);

   bool  remove_from_list(int32 index);
   bool  remove_current_track()
   {
   	return remove_from_list(current_index);
   }

protected:

   int32 current_index;
   FileList *fl;
};

#endif // PLAYLIST_H
