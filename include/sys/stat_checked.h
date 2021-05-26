//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in sys/stat.h that             //
// take pointer arguments.                                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <sys/stat.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __STAT_CHECKED_H
#define __STAT_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

extern int mkdir(const char *pathname : itype(_Nt_array_ptr<const char>), mode_t mode);
extern int chmod(const char *pathname : itype(_Nt_array_ptr<const char>), mode_t mode);
extern int fstat(int fd, struct stat *buf : itype(_Ptr<struct stat>));
extern int lstat(const char *restrict file : itype(restrict _Nt_array_ptr<const char>),
                 struct stat *restrict buf : itype(restrict _Ptr<struct stat>));
extern int stat(const char *restrict file : itype(restrict _Nt_array_ptr<const char>),
                struct stat *restrict buf : itype(restrict _Ptr<struct stat>));

// int fchmod(int, mode_t) and mode_t umask(mode_t) inherited from system header

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C
