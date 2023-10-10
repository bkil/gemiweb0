#ifndef _include_string_h
#define _include_string_h

#define _string_h_need_XOPEN_SOURCE
#ifdef _XOPEN_SOURCE
# if _XOPEN_SOURCE >= 700
#  ifndef _string_h_have_posix_include
#   define _string_h_have_posix_include
#  endif
#  undef _string_h_need_XOPEN_SOURCE
# endif
#endif

#define _string_h_need_POSIX_C_SOURCE
#ifdef _POSIX_C_SOURCE
# if _POSIX_C_SOURCE >= 200808L
#  ifndef _string_h_have_posix_include
#   define _string_h_have_posix_include
#  endif
#  undef _string_h_need_POSIX_C_SOURCE
# endif
#endif

#ifdef _GNU_SOURCE
# ifndef _string_h_have_posix_include
#  define _string_h_have_posix_include
# endif
#endif

#ifdef _string_h_have_posix_include

# undef _string_h_have_posix_include

#else

# ifdef _string_h_need_XOPEN_SOURCE
#  define _XOPEN_SOURCE 700 /* strnlen strdup strndup getline */
# endif

# ifdef _string_h_need_POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L /* strnlen strdup strndup getline */
# endif

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE /* strnlen strdup strndup getline */
# endif

#endif

#ifdef _string_h_need_XOPEN_SOURCE
# undef _string_h_need_XOPEN_SOURCE
#endif

#ifdef _string_h_need_POSIX_C_SOURCE
# undef _string_h_need_POSIX_C_SOURCE
#endif

#include <string.h>

#endif
