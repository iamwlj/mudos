#ifndef STD_H
#define STD_H

/* This stuff should be included EVERYWHERE */

/* the definition of ARCH */
#include "arch.h"

#define CONST const
#ifdef EDIT_SOURCE
#define INLINE
#else
/* all options and configuration */
#include "options_incl.h"
#include "configure.h"

#   ifdef PEDANTIC
#      undef INLINE
#      define INLINE
#   endif
#endif

#ifdef WIN32
#define INCL_STDLIB_H
#define INCL_TIME_H
#define INCL_FCNTL_H
#define INCL_DOS_H
#define INCL_SYS_STAT_H
#define INCL_LIMITS_H
#define USE_STRUCT_DIRENT
#define INCL_STDARG_H
#define HAS_MEMMOVE
#define RAND
#define HAS_STRERROR
#define HAS_GETCWD
#endif

#include "portability.h"
#include "macros.h"
#ifndef _FUNC_SPEC_
#   include "std_incl.h"
#   include "malloc_incl.h"
#   ifndef NO_OPCODES
#      include "opcodes.h"
#   endif
#endif
#include "debug.h"

#ifdef WIN32
#  define outp outptr
void mudos_exit(int);
#else
#define mudos_exit(x) exit(x)
#endif

#endif






