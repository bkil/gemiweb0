/* Copyright (C) 2023 bkil.hu
Refer to the GNU GPL v2 in LICENSE for terms */

#ifndef _include_include_h
#define _include_include_h

#define _include_h_need_XOPEN_SOURCE
#ifdef _XOPEN_SOURCE
# if _XOPEN_SOURCE >= 700
#  ifndef _include_h_have_posix_include
#   define _include_h_have_posix_include
#  endif
#  undef _include_h_need_XOPEN_SOURCE
# endif
#endif

#define _include_h_need_POSIX_C_SOURCE
#ifdef _POSIX_C_SOURCE
# if _POSIX_C_SOURCE >= 200808L
#  ifndef _include_h_have_posix_include
#   define _include_h_have_posix_include
#  endif
#  undef _include_h_need_POSIX_C_SOURCE
# endif
#endif

#ifdef _GNU_SOURCE
# ifndef _include_h_have_posix_include
#  define _include_h_have_posix_include
# endif
#endif

#ifdef _include_h_have_posix_include

# undef _include_h_have_posix_include

#else

# ifdef _include_h_need_XOPEN_SOURCE
/* strnlen strdup strndup getline getaddrinfo freeaddrinfo gai_strerror */
#  define _XOPEN_SOURCE 700
# endif

# ifdef _include_h_need_POSIX_C_SOURCE
/* strnlen strdup strndup getline clock_gettime getaddrinfo freeaddrinfo gai_strerror */
#  define _POSIX_C_SOURCE 200809L
# endif

# ifndef _GNU_SOURCE
/* strnlen strdup strndup getline */
#  define _GNU_SOURCE
# endif

#endif

#ifdef _include_h_need_XOPEN_SOURCE
# undef _include_h_need_XOPEN_SOURCE
#endif

#ifdef _include_h_need_POSIX_C_SOURCE
# undef _include_h_need_POSIX_C_SOURCE
#endif

/* strnlen strdup strndup getline */
#include <string.h>

/* clock_gettime */
#include <time.h>

/* getaddrinfo freeaddrinfo gai_strerror socket connect */
#include <sys/types.h>

/* getaddrinfo freeaddrinfo gai_strerror socket connect shutdown */
#include <sys/socket.h>

/* getaddrinfo freeaddrinfo gai_strerror */
#include <netdb.h>

#endif
