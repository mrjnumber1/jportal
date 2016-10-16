#ifndef JP_PRELUDE_H_INCLUDED
#define JP_PRELUDE_H_INCLUDED

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

#include <SDL.h>

#ifndef static_assert
#   define static_assert(cond, msg) \
        typedef char _stasrt_##msg[(!!cond)*2-1]
#endif

static_assert(UCHAR_MAX == 0xFF, "byte definition needs changed!!");
static_assert(USHRT_MAX == 0xFFFFU, "word definition needs changed!!");
static_assert(UINT_MAX == 0xFFFFFFFFU, "dword definition needs changed!!");

typedef unsigned char byte;
typedef unsigned short dbyte;
typedef unsigned int qbyte;  

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
#elif (!defined(true))
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
        //typedef unsigned long ulong;
        //typedef unsigned int uint;
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


#define streq(s1, s2) (strcmp((s1), (s2))==0)
#define strneq(s1, s2) (strcmp((s1), (s2))) 
#define nstreq(s1, s2, len) (strncmp((s1), (s2), (size_t)(len))==0)
#define nstrneq(s1, s2, len) (strncmp((s1), (s2), (size_t)(len)))
#define streq_i(s1, s2) (strcmpi((s1), (s2))==0)
#define strneq_i(s1, s2) (strcmpi((s1), (s2)))
#define nstreq_i(s1, s2, len) (strncmpi((s1), (s2), (size_t)(len))==0)
#define nstrneq_i(s1, s2, len) (strncmpi((s1), (s2), (size_t)(len)))

#define QUOTE(x) #x
#define EXPAND_AND_QUOTE(x) QUOTE(x)

#define NLP_MARK __FILE__, __LINE__, __func__

bool nullpo_chk(const char* file, unsigned line, const char *func, const void* target)
{
    if (target != NULL)
        return false;

    if (file == NULL)
        file = "?";

    func = 
        func == NULL ? "?":
        func[0] == '\0' ? "?":
            func;
    fprintf(stderr, "nullpo: %s:%d in `%s`\n", file, line, func);
    fflush(stderr);

    return true;
}

#define is_compatible_type(x, T) _Generic((x), T:true, default:false)
#define is_integer_type(x) is_compatible_type(x, int)
#define is_float_type(x) _Generic((x), \
    float:true, const float: true, double:true, const double: true, default:false)
#define is_string_type(x) _Generic( ((0,(x))+0), \
    char*: true, const char*: true, default:false)
#define ensure_type(x, T) static_assert(is_compatible_type(x, T), \
    "incorrect type for paramenter " QUOTE(x) "expected " QUOTE(T))

#ifdef JP_SELFTESTING 
#   define jassert(cond) \
        (void)( (!!(cond) || printf("assert fail: '%s', @ %s:%u in %s", \
            QUOTE(cond), NLP_MARK)));
#else
#   define jassert(cond) assert((cond))
#endif

#define jassert_eq(a,b) jassert((a) == (b))
#define jassert_neq(a,b) jassert((a) != (b))
#define jassert_greater(a,b) jassert((a) > (b))
#define jassert_geq(a,b) jassert((a) >= (b))
#define jassert_less(a,b) jassert((a) < (b))
#define jassert_leq(a,b) jassert((a) <= (b))
#define jassert_true(a) jassert((a))
#define jassert_false(a) jassert(!(a))
#define jassert_isnull(a) jassert((a) == NULL)
#define jassert_notnull(a) jassert((a) != NULL)
#define jassert_ptreq(a,b) \
    jassert((void*)(a) == (void*)(b))
#define jassert_ptrneq(a,b) \
    jassert((void*)(a) != (void*)(b))
#define jassert_aresame(a,b) \
    jassert(((a) == (b)) && ((void*)(a) == (void*)(b)))
#define jassert_notsame(a,b) \
    jassert(((a) != (b)) && ((void*)(a) != (void*)(b)))
#define jassert_isinteger(a) jassert(is_numeric_type(a))
#define jassert_isnumeric(a) jassert(is_numeric_type(a) || is_float_type(a))
#define jassert_isstr(a) jassert(is_string_type(a))
#define jassert_notinteger(a) jassert(!is_numeric_type(a))
#define jassert_isnotnumeric(a) jassert(!is_numeric_type(a) || !is_float_type(a))
#define jassert_notstr(a) jassert(!is_string_type(a))

#define jstrassert_eq(a,b) \
    jassert(is_string_type(a) && is_string_type(b) \
        && streq(a,b))

#define jnstrassert_eq(a,b,len) \
    jassert(is_string_type(a) && is_string_type(b) \
        && nstreq(a,b, len)) 

#define jstrassert_eq_i(a,b) \
    jassert(is_string_type(a) && is_string_type(b) \
        && streq_i(a,b))

#define jnstrassert_eq_i(a,b,len) \
    jassert(is_string_type(a) && is_string_type(b) \
        && nstreq(a,b,len))

#define jstrassert_neq(a,b) \
    jassert(is_string_type(a) && is_string_type(b) \
        && strneq(a,b))

#define jnstrassert_neq(a,b,len) \
    jassert(is_string_type(a) && is_string_type(b) \
        && nstrneq(a,b,len))

#define jstrassert_neq_i(a,b) \
    jassert(is_string_type(a) && is_string_type(b) \
        && strneq_i(a,b))

#define jnstrassert_neq_i(a,b,len) \
    jassert(is_string_type(a) && is_string_type(b) \
        && nstrneq_i(a,b,len))

#define jstrassert_contains(a, sub) \
    jassert(is_string_type(a) && is_string_type(sub) \
        && strstr((a),(sub)) != NULL)

#define jstrassert_notcontain(a, sub) \
    jassert(is_string_type(a) && is_string_type(sub) \
        && strstr((a),(sub)) == NULL)

#define jstrassert_startswith(a, sub) \
    jassert(is_string_type(a) && is_string_type(sub) \
        && strstr((a),(sub))-(a) == 0)

#define jstrassert_notstartwith(a, sub) \
    jassert(is_string_type(a) && is_string_type(sub) \
        && strstr((a),(sub))-(a) != 0)

#define jstrassert_endswith(a, sub) \
    jassert(is_string_type(a) && is_string_type(sub) \
        && ( strlen((a)) >= strlen((sub)) \
            && streq((a)+strlen((sub))-strlen((a)), (sub)) ) )

#define jstrassert_notendwith(a, sub) \
    jassert(is_string_type(a) && is_string_type(sub) \
        && ( strlen((a)) >= strlen((sub)) \
            && strneq((a)+strlen((sub))-strlen((a)), (sub)) ) )

#define jdblassert_eq(a,b,gran) \
    jassert(is_float_type(a) && is_float_type(b) && is_float_type(gran) \
        (fabs((double)(a)-(b)) <= fabs((double)gran)))
#define jdblassert_neq(a,b,gran) \
    jassert(is_float_type(a) && is_float_type(b) && is_float_type(gran) \
        (fabs((double)(a)-(b)) > fabs((double)gran)))


#define nullpo_ret(t) \
    if (nullpo_chk(NLP_MARK, (void *)(t))) { return(0);}

#define nullpo_retv(t) \
    if (nullpo_chk(NLP_MARK, (void *)(t))) { return; }

#define nullpo_retr(t, ret) \
    if (nullpo_chk(NLP_MARK, (void *)(t))) { return (ret); }

static inline void*
trace_malloc(size_t size, const char *file, unsigned line, const char* func)
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
        fprintf(stderr, "OUT OF MEMORY!! calloc returned null!");
        fflush(stderr);
        abort();
    }

    return mem;
}

#define TRACE_MEMLEAKS
#if defined(TRACE_MEMLEAKS)
#   define jmalloc(size) calloc(1,(size))
#else
#   define jmalloc(size) trace_malloc((size), NLP_MARK) 
#endif

#if (defined(__GNUC__) && (__GNUC__ >= 2))
#   define CHECK_PRINTF(a) __attribute((format(printf, a, a+1)))
#else
#   define CHECK_PRINTF(a)
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

#define ARRAY_SIZE(a) ( sizeof(a)/sizeof((a)[0]) )

#define min(x, y) ({ \
        typeof(x) _min1 = (x); \
        typeof(y) _min2 = (y); \
        (void) (&_min1 == &_min2); \
        _min1 < _min2 ? _min1 : min2; })

#define min3(x, y, z) min((typeof(x))min(x, y), z)

#define max(x, y) ({ \
        typeof(x) _max1 = (x); \
        typeof(y) _max2 = (y); \
        (void) (&_max1 == &_max2); \
        _max1 > _max2 ? _max1 : max2; })

#define max3(x, y, z) max((typeof(x))max(x, y),z)

#define clamp(val, lo, hi) min((typeof(val))max(val, lo), hi)

#define swap(a, b) \
        do { typeof(a) _tmp =(a); (a) = (b); (b) = _tmp; } while(0)

#define abs(a) ((a) < 0 ? -(a) : (a))
// sign(n) will return -1, 0, or 1
#define sign(a) (((v) > 0) - ((v) < 0))

#define BUILD_BUG_ON_ZERO(e) static_assert((e) != 0) 
#define BUILD_BUG_ON_NULL(e) static_assert((e) != NULL) 
#define BUILD_BUG_ON(e) static_assert((e)) 



#endif
