#ifndef JP_PRELUDE_H_
#define JP_PRELUDE_H

#if (defined(__64BIT__) || defined(__x64_64__))
#   define __IS_64BIT__
#else
#   define __IS_32BIT__
#endif

#if (defined(WIN32) || defined(_WIN32))
#   undef __WINDOWS__
#   define __WINDOWS__
#   undef __MSDOS__
#   define __MSDOS__
#endif

#if (defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS__))
#   undef __WINDOWS__
#   define __WINDOWS__
#   undef __MSDOS__
#   define __MSDOS__
#   if _MSC_VER >= 1500
#       undef _CRT_SECURE_NO_DEPRECATE
#       define _CRT_SECURE_NO_DEPRECATE
#       pragma warning(disable: 4996)
#   endif
#endif

#if (defined(MSDOS) || defined (_MSC_VER))
#   undef __MSDOS__
#   define __MSDOS__
#   if (defined(_DEBUG) && !defined(DEBUG))
#       define DEBUG
#   endif
#endif

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <setjmp.h>
#include <assert.h>

#include <SDL2/SDL.h>


static_assert(UCHAR_MAX == 0xFF, "byte definition needs changed!!");
static_assert(USHRT_MAX == 0xFFFFU, "word definition needs changed!!");
static_assert(UINT_MAX == 0xFFFFFFFFU, "dword definition needs changed!!");

typedef unsigned char   byte;
typedef unsigned short  dbyte;
typedef unsigned int    qbyte;  

#define streq(s1, s2) (!strcmp((s1), (s2)))
#define strnew(s1, s2) (strcmp((s1), (s2))) 

#if (defined(__WINDOWS__))
#   define randof(num) (int) ((float) (num) * rand() / (RAND_MAX + 1.0))
#else
#   define randof(num) (int) ((float) (num) * random() / (RAND_MAX + 1.0))
#endif

#if (defined(_MSC_VER))
#   if(!defined(__cplusplus) && (!defined(true)))
#       define true (1==1)
#       define false (1==0)
        typedef char bool;
#   endif
#else
#   include <stdbool.h>
#endif


#if (defined(__WINDOWS__))
#   if (!defined(__cplusplus) && (!defined(inline)))
#       define inline __inline
#   endif
#   define strtoull _strtoui64
#   define strtoll _strtoi64
#   define atoll _atoi64
#   define srandom srand
#   define TIMEZONE _timezone
#   if (!defined(__MINGW32__))
#       define snprintf _snprintf
#       define vsnprintf _vsnprintf
#   endif
    typedef unsigned long ulong;
    typedef unsigned int uint;
#   if (!defined(__MINGW32__))
        typedef int mode_t;
#       if (!defined(_SSIZE_T_DEFINED))
            typedef intptr_t ssize_t;
#           define _SSIZE_T_DEFINED
#       endif
#   endif
#   if ((!defined(__MINGW32__) \
    || (defined(__MINGW32__) && defined(__IS_64BIT))))
        typedef __int8 int8;
        typedef __int16 int16;
        typedef __int32 int32;
        typedef __int64 int64;
        typedef unsigned __int8 uint8;
        typedef unsigned __int16 uint16;
        typedef unsigned __int32 uint32;
        typedef unsigned __int64 uint64;
#   endif
#   if (!defined(PRId8))
#       define PRId8    "d"
#   endif
#   if (!defined(PRId16))
#       define PRId16   "d"
#   endif
#   if (!defined(PRId32))
#       define PRID32   "d"
#   endif
#   if (!defined(PRId64))
#       define PRId64   "I64d"
#   endif
#   if (!defined(PRIu8))
#       define PRIu8    "u"
#   endif
#   if (!defined(PRIu16))
#       define PRIu16   "u"
#   endif
#   if (!defined(PRIu32))
#       define PRIu32   "u"
#   endif
#   if (!defined(PRIu64))
#       define PRIu64   "I64u"
#   endif
#   if (!defined(va_copy))
#       define va_copy(dest, src) (dest) = (src)
#   endif
#endif


#define NLP_MARK __FILE__, __LINE__, __func__

inline bool
nullpo_chk(const char* file, unsigned line, const char *func, const void* target)
{
    if (target != NULL)
        return false;

    if (file == NULL)
        file = "?";

    func = 
        func == NULL ? "?":
        func[0] == '\0' ? "?":
            func;

    fprintf(stderr, "ERROR! nullpo passed! info: \n");
    fprintf(stderr, "%s:%d in func `%s`\n", file, line, func);
    fflush(stderr);

    return true;
}


#define nullpo_ret(t) \
    if (nullpo_chk(NLP_MARK, (void *)(t))) { return(0);}

#define nullpo_retv(t) \
    if (nullpo_chk(NLP_MARK, (void *)(t))) { return; }

#define nullpo_retr(t, ret) \
    if (nullpo_chk(NLP_MARK, (void *)(t))) { return (ret); }



static inline void*
safe_malloc(size_t size, const char *file, unsigned line, const char* func)
{
    void *mem = calloc(1, size);

    if (mem == NULL)
    {
        if (file == NULL)
            file = "?";

        func = 
            func == NULL ? "?":
            func[0] == '\0' ? "?":
                func;

        fprintf(stderr, "FATAL ERROR at %s:%u in `%s`! \n", file, line, func);
        fprintf(stderr, "OUT OF MEMORY!! malloc returned null!");
        fflush(stderr);
        abort();
    }

    return mem;
}

#define TRACE_MEMLEAKS
#if defined(TRACE_MEMLEAKS)
#   define jmalloc(size) calloc(1,(size))
#else
#   define jmalloc(size) safe_malloc((size), NLP_MARK) 
#endif

#if (defined(__GNUC__) && (__GNUC__ >= 2))
#   define CHECK_PRINTF(a) __attribute((format(printf, a, a+1)))
#else
#   define CHECK_PRINTF(a)
#endif


typedef intptr_t intptr;
typedef uintptr_t uintptr;

#if (defined(_MSC_VER))
#   define strcasecmp   stricmp
#   define strncasecmp  strnicmp
#   define strncmpi strnicmp
#   if (_MSC_VER < 1900)
#       define snprintf _snprintf
#   endif
#   if (_MSC_VER < 1400)
#       define vsnprintf    _vsnprintf
#   endif
#else
#   define strcmpi  strcasecmp
#   define stricmp  strcasecmp
#   define strncmpi strncasecmp
#   define strnicmp strncasecmp
#endif

#define ISALNUM(c) (isalnum((unsigned char)(c)))
#define ISALPHA(c) (isalpha((unsigned char)(c)))
#define ISCNTRL(c) (iscntrl((unsigned char)(c)))
#define ISDIGIT(c) (isdigit((unsigned char)(c)))
#define ISGRAPH(c) (isgraph((unsigned char)(c)))
#define ISLOWER(c) (islower((unsigned char)(c)))
#define ISPRINT(c) (isprint((unsigned char)(c)))
#define ISPUNCT(c) (ispunct((unsigned char)(c)))
#define ISSPACE(c) (isspace((unsigned char)(c)))
#define ISUPPER(c) (isupper((unsigned char)(c)))
#define ISXDIGIT(c) (isxdigit((unsigned char)(c)))

#define TOASCII(c) (toascii((unsigned char)(c)))
#define TOLOWER(c) (tolower((unsigned char)(c)))
#define TOUPPER(c) (toupper((unsigned char)(c)))

#define ARRAYLENGTH(a) ( sizeof(a)/sizeof((a)[0]) )

#define QUOTE(x) #x
#define EXPAND_AND_QUOTE(x) QUOTE(x)

#define jp_assert(cond) \
 (void)( (!!(cond) || printf("test assertion failed: '%s', at %s:%u in %s", \
        QUOTE(cond), NLP_MARK)));

#endif
