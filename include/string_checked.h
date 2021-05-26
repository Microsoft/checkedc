//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in string.h that               //
// take pointer arguments.                                             //
//                                                                     //
// These are listed in the same order that they occur in the C11       //
// specification.                                                      //
//                                                                     //
// TODO: revise string types after support for pointers to             //
// null-terminated arrays is added to C.                               //
//                                                                     //
// TODO: Better Support for _FORTIFY_SOURCE > 0                        //
/////////////////////////////////////////////////////////////////////////

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <string.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc

#ifndef __STRING_CHECKED_H
#define __STRING_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

// GCC has macros that it uses as part of its string implementation to optimize cases
// where one or both strings are compile-time constants.  I'm not sure
// why they put this logic into macros instead of the compiler because the
// compiler can recognize these cases in more contexts than a macro, but they
// did.
//
// For now, undefine the various macros.  GCC has a #define for turning off
// this feature, but that must be set before string.h is included and we don't
// control when that happens (string.h may already have been included before
// this file is ever included).
#if defined(__GNUC__)
#undef strchr
#undef strcmp
#undef strcspn
#undef strncmp
#undef strncmp
#undef strpbrk
#undef strspn
#undef strdup
#endif

// We wrap each definition in a complex conditional, there two boolean values:
// - we are fortifying, or we're not (_FORTIFY_SOURCE==0 is not fortifying)
// - there is or there isn't a macro hash-defining this symbol (defined(symbol))
// Cases:
// - Fortifying,     Macro Exists: this is expected, we don't need the definition
// - Not Fortifying, Macro Exists: we need the definition, we need to undef macro
// - Fortifying,     No Macro:     we need the definition
// - Not Fortifying, No Macro:     we need the definition

#if _FORTIFY_SOURCE == 0 || !defined(memcpy)
#undef memcpy
_Itype_for_any(T) void *memcpy(void * restrict dest : itype(restrict _Array_ptr<T>) byte_count(n),
             const void * restrict src : itype(restrict _Array_ptr<const T>) byte_count(n),
             size_t n) : itype(_Array_ptr<T>) byte_count(n);
#endif

#if _FORTIFY_SOURCE == 0 || !defined(memmove)
#undef memmove
void *memmove(void * dest : byte_count(n),
              const void * src : byte_count(n),
              size_t n) : bounds(dest, (_Array_ptr<char>)dest + n);
#endif

#if _FORTIFY_SOURCE == 0 || !defined(memset)
#undef memset
void *memset(void * dest : byte_count(n),
             int c,
             size_t n) : bounds(dest, (_Array_ptr<char>)dest + n);
#endif

#if _FORTIFY_SOURCE == 0 || !defined(strcpy)
#undef strcpy
// Dest is left unchecked intentionally. There is no bound on dest, so this
// is always an unchecked function
_Unchecked
char *strcpy(char * restrict dest,
              const char * restrict src : itype(restrict _Nt_array_ptr<const char>));
#endif

#if _FORTIFY_SOURCE == 0 || !defined(strncpy)
#undef strncpy
char *strncpy(char * restrict dest : count(n),
              const char * restrict src : count(n),
              size_t n) : bounds(dest, (_Array_ptr<char>)dest + n);
#endif

#if _FORTIFY_SOURCE == 0 || !defined(strcat)
#undef strcat
// Dest is left unchecked intentionally. There is no bound on dest, so this
// is always an unchecked function.
_Unchecked
char *strcat(char * restrict dest,
             const char * restrict src : itype(restrict _Nt_array_ptr<const char>));
#endif

#if _FORTIFY_SOURCE == 0 || !defined(strncat)
#undef strncat
// TODO: we have no way to express the bounds requirement on dest,
// which needs to be count(strlen(dest) + n).
_Unchecked
char *strncat(char * restrict dest,
              const char * restrict src : count(n),
              size_t n);
#endif

int memcmp(const void *src1 : byte_count(n), const void *src2 : byte_count(n),
           size_t n);

int strcmp(const char *src1 : itype(_Nt_array_ptr<const char>),
           const char *src2 : itype(_Nt_array_ptr<const char>));
int strcasecmp(const char *src1 : itype(_Nt_array_ptr<const char>),
               const char *src2 : itype(_Nt_array_ptr<const char>));
int strcoll(const char *src1 : itype(_Nt_array_ptr<const char>),
            const char *src2 : itype(_Nt_array_ptr<const  char>));

// strncmp takes possibly null-terminated strings as arguments and checks
// up to n characters. For a bounds-safe interface, this means each string
// needs to be EITHER null-terminated OR have bounds greater than or equal to
// n. We cannot express them both in a single interface, so this is the
// interface for null-terminated strings (assumed to be the most common case).
// In the checkedc_extensions.h header there is a bounds-safe interface for
// use of _Array_ptr rather than _Nt_array_ptr.
int strncmp(const char *src : itype(_Nt_array_ptr<const char>),
            const char *s2 : itype(_Nt_array_ptr<const char>),
            size_t n);
int strncasecmp(const char *src : itype(_Nt_array_ptr<const char>),
                const char *s2 : itype(_Nt_array_ptr<const char>),
                size_t n);

size_t strxfrm(char * restrict dest : count(n),
               const char * restrict src :
                 itype(restrict _Nt_array_ptr<const char>),
               size_t n);

void *memchr(const void *s : byte_count(n), int c, size_t n) :
  bounds(s, (_Array_ptr<char>) s + n);

char *strchr(const char *s : itype(_Nt_array_ptr<const char>), int c) :
  itype(_Nt_array_ptr<char>);

size_t strcspn(const char *s1 : itype(_Nt_array_ptr<const char>),
               const char *s2 : itype(_Nt_array_ptr<const char>));

char *strpbrk(const char *s1 : itype(_Nt_array_ptr<const char>),
              const char *s2 : itype(_Nt_array_ptr<const char>)) :
  itype(_Nt_array_ptr<char>);
char *strrchr(const char *s : itype(_Nt_array_ptr<const char>), int c) :
  itype(_Nt_array_ptr<char>);
size_t strspn(const char *s1 : itype(_Nt_array_ptr<const char>),
              const char *s2 : itype(_Nt_array_ptr<const char>));
char *strstr(const char *s1 : itype(_Nt_array_ptr<const char>),
             const char *s2 : itype(_Nt_array_ptr<const char>)) :
  itype(_Nt_array_ptr<char>);
char *strtok(char * restrict s1 : itype(restrict _Nt_array_ptr<char>),
             const char * restrict s2 : itype(restrict _Nt_array_ptr<const char>)) :
  itype(_Nt_array_ptr<char>);

char *strerror(int errnum) : itype(_Nt_array_ptr<char>);
size_t strlen(const char *s : itype(_Nt_array_ptr<const char>));

char *strdup(const char *s : itype(_Nt_array_ptr<const char>)) : itype(_Nt_array_ptr<char>);

#include "_builtin_string_checked.h"

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C 
