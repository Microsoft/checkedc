//---------------------------------------------------------------------//
// Bounds-safe interfaces for some functions in assert.h that          //
// take pointer arguments.                                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

#ifndef __cplusplus
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include <assert.h>

#ifndef __cplusplus
#pragma CHECKED_SCOPE pop
#endif

#ifndef __cplusplus
#ifndef __ASSERT_CHECKED_H
#define __ASSERT_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE ON

#if defined(_WIN32) || defined(_WIN64)
_ACRTIMP void __cdecl _wassert(_In_z_ wchar_t const *_Message : itype(_Nt_array_ptr<const wchar_t>),
                               _In_z_ wchar_t const *_File : itype(_Nt_array_ptr<const wchar_t>),
                               _In_ unsigned _Line);
#else
#ifdef __APPLE__
#define __THROW
extern void __assert_rtn(const char *msg : itype(_Nt_array_ptr<const char>),
			 const char *file : itype(_Nt_array_ptr<const char>),
			 int line,
			 const char *fn : itype(const char _Nt_checked[]));
#else
extern void __assert(const char *msg : itype(_Nt_array_ptr<const char>), 
					 const char *file : itype(_Nt_array_ptr<const char>), 
					 int line);

#endif
#undef __assert_fail
extern void __assert_fail (const char *__assertion : itype(_Nt_array_ptr<const char>), const char *__file : itype(_Nt_array_ptr<const char>),
        unsigned int __line, const char *__function : itype(const char _Nt_checked[]))
__THROW __attribute__ ((__noreturn__));

#endif

#pragma CHECKED_SCOPE pop

#endif  // guard
#endif  // no c++
