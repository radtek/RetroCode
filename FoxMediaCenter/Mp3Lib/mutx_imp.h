/* mutx_imp.h

   Mutex locking and unlocking implementation for the operating
   system you are porting to. The _Mutex type is defined in
   "all.h". */

#ifndef THREAD_IMP_H
#define THREAD_IMP_H

#ifdef SEEK_STOP

#ifdef __WIN32__
#include <windows.h>
#endif // __WIN32__

#include "all.h"

inline uint32 mtx_lock(_Mutex m)
{
#ifdef __WIN32__
	return(WaitForSingleObject(m, INFINITE));
#else
	// lock mutex
#endif // __WIN32__
}

inline uint32 mtx_unlock(_Mutex m)
{
#ifdef __WIN32__
	return(ReleaseMutex(m));
#else
	// unlock mutex
#endif // __WIN32__
}

#endif  // SEEK_STOP

#endif
