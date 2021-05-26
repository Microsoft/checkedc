//---------------------------------------------------------------------//
// Bounds-safe interfaces for compiler-defined builtin functions       //
// corresponding to stdio.h functions                                  //
//                                                                     //
// These are given in the order they appear in clang's Builtins.def.   //
// Functions that do not appear can not have checked interfaces        //
// defined.                                                            //
//                                                                     //
// These are based on the types as declared within clang               //
// and https://gcc.gnu.org/onlinedocs/gcc/Object-Size-Checking.html    //
/////////////////////////////////////////////////////////////////////////

#include "_builtin_common.h"

#if _USE_FORTIFY_LEVEL > 0

#ifndef __has_builtin
#define _undef__has_builtin
#define __has_builtin(x) 0
#endif


#if __has_builtin(__builtin___sprintf_chk) || defined(__GNUC__)
// sprintf
extern _Unchecked
int __sprintf_chk(char * restrict buffer : itype(restrict _Nt_array_ptr<char>),
                  int flag,
                  size_t obj_size,
                  const char * restrict format :
                    itype(restrict _Nt_array_ptr<const char>),
                  ...);

_Unchecked
int __builtin___sprintf_chk(char * restrict buffer : itype(restrict _Nt_array_ptr<char>),
                            int flag,
                            size_t obj_size,
                            const char * restrict format :
                              itype(restrict _Nt_array_ptr<const char>),
                            ...);
#endif

#if __has_builtin(__builtin___snprintf_chk) || defined(__GNUC__)
// snprintf
extern _Unchecked
int __snprintf_chk(char * restrict buffer : itype(restrict _Nt_array_ptr<char>) count(maxlen == 0 ? 0 : maxlen-1),
                   size_t maxlen,
                   int flag,
                   size_t obj_size,
                   const char * restrict format :
                     itype(restrict _Nt_array_ptr<const char>),
                   ...);

_Unchecked
int __builtin___snprintf_chk(char * restrict buffer : itype(restrict _Nt_array_ptr<char>) count(maxlen == 0 ? 0 : maxlen-1),
                             size_t maxlen,
                             int flag,
                             size_t obj_size,
                             const char * restrict format :
                               itype(restrict _Nt_array_ptr<const char>)
                             ,
                             ...);
#endif

#if __has_builtin(__builtin___vsprintf_chk) || defined(__GNUC__)
// vsprintf
extern _Unchecked
int __vsprintf_chk(char * restrict buffer : itype(restrict _Nt_array_ptr<char>),
                   int flag,
                   size_t obj_size,
                   const char * restrict format :
                     itype(restrict _Nt_array_ptr<const char>),
                   va_list);


_Unchecked
int __builtin___vsprintf_chk(char * restrict buffer : itype(restrict _Nt_array_ptr<char>),
                             int flag,
                             size_t obj_size,
                             const char * restrict format :
                               itype(restrict _Nt_array_ptr<const char>),
                             va_list arg);
#endif


#if __has_builtin(__builtin___vsnprintf_chk) || defined(__GNUC__)
// vsnprintf
extern _Unchecked
int __vsnprintf_chk(char * restrict buffer : itype(restrict _Nt_array_ptr<char>) count(maxlen == 0 ? 0 : maxlen-1),
                    size_t maxlen,
                    int flag,
                    size_t obj_size,
                    const char * restrict format :
                      itype(restrict _Nt_array_ptr<const char>),
                    va_list);

_Unchecked
int __builtin___vsnprintf_chk(char * restrict buffer : itype(restrict _Nt_array_ptr<char>) count(maxlen == 0 ? 0 : maxlen-1),
                              size_t maxlen,
                              int flag,
                              size_t obj_size,
                              const char * restrict format :
                                itype(restrict _Nt_array_ptr<const char>),
                              va_list arg);
#endif

#if __has_builtin(__builtin___fprintf_chk) || defined(__GNUC__)
// fprintf
extern _Unchecked
int __fprintf_chk(FILE * restrict stream : itype(restrict _Ptr<FILE>),
                  int flag,
                  const char * restrict format :
                    itype(restrict _Nt_array_ptr<const char>),
                  ...);

_Unchecked
int __builtin___fprintf_chk(FILE * restrict stream : itype(restrict _Ptr<FILE>),
                            int flag,
                            const char * restrict format :
                              itype(restrict _Nt_array_ptr<const char>),
                            ...);
#endif

#if __has_builtin(__builtin___printf_chk) || defined(__GNUC__)
// printf
extern _Unchecked
int __printf_chk(int flag,
                 const char * restrict format :
                   itype(restrict _Nt_array_ptr<const char>),
                 ...);

_Unchecked
int __builtin___printf_chk(int flag,
                           const char * restrict format :
                             itype(restrict _Nt_array_ptr<const char>),
                           ...);
#endif

#if __has_builtin(__builtin___vfprintf_chk) || defined(__GNUC__)
// vfprintf
extern _Unchecked
int __vfprintf_chk(FILE * restrict stream : itype(restrict _Ptr<FILE>),
                   int flag,
                   const char * restrict format :
                     itype(restrict _Nt_array_ptr<const char>),
                   va_list);

_Unchecked
int __builtin___vfprintf_chk(FILE * restrict stream : itype(restrict _Ptr<FILE>),
                             int flag,
                             const char * restrict format :
                               itype(restrict _Nt_array_ptr<const char>),
                             va_list);
#endif

#if __has_builtin(__builtin___vprintf_chk) || defined(__GNUC__)
// vprintf
extern _Unchecked
int __vprintf_chk(int flag,
                  const char * restrict format :
                    itype(restrict _Nt_array_ptr<const char>),
                  va_list);

_Unchecked
int __builtin___vprintf_chk(int flag,
                            const char * restrict format :
                              itype(restrict _Nt_array_ptr<const char>),
                            va_list);
#endif

#ifdef _undef__has_builtin
#undef _undef__has_builtin
#undef __has_builtin
#endif

#endif
