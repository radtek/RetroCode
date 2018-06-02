/* Obuffer.cpp

   Includes the correct implementation of Obuffer for the
   operating system you are compiling for.

   Last edit : 05/02/97 */

#include "fileobuf.cc"

#ifdef IRIX
#include "indigo_obuffer.cc"
#endif

#ifdef SPARC
#include "sparc_obuffer.cc"
#endif

#ifdef HPUX
#include "hpux_obuffer.cc"
#endif

#if defined(LINUX) || defined(__FreeBSD__)
#include "linux_obuffer.cc"
#endif

#ifdef NeXT
#include "NeXT_obuffer.cc"
#endif

#ifdef AIX
#include "aix_obuffer.cc"
#endif

#ifdef __WIN32__
#include "mci_obuf.cpp"
#include "wavefile_obuffer.cpp"
// #include "ds_obuffer.cpp"
#endif

#ifdef BEOS
#include "beos_obuffer.cc"
#endif

#ifdef OS2
#include "os2_obuffer.cc"
#endif
