//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in time.h that                 //
// take pointer arguments.                                             //
//                                                                     //
// These are listed in the same order that they occur in the C11       //
// specification.                                                      //
/////////////////////////////////////////////////////////////////////////

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <time.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __TIME_CHECKED_H
#define __TIME_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

time_t mktime(struct tm *timeptr : itype(_Ptr<struct tm>));

int timespec_get(struct timespec *ts : itype(_Ptr<struct timespec>),
                 int base);

char *asctime(const struct tm *timeptr : itype(_Ptr<const struct tm>)) :
  itype(_Nt_array_ptr<char>);

char *ctime(const time_t *timer : itype(_Ptr<const time_t>)) :
  itype(_Nt_array_ptr<char>);

struct tm *gmtime(const time_t *timer : itype(_Ptr<const time_t>)) :
  itype(_Ptr<struct tm>);

struct tm *localtime(const time_t *timer : itype(_Ptr<const time_t>)) :
  itype(_Ptr<struct tm>);

size_t strftime(char * restrict output : itype(restrict _Nt_array_ptr<char>) count(maxsize),
                size_t maxsize,
                const char * restrict format : itype(restrict _Nt_array_ptr<const char>),
                const struct tm * restrict timeptr :
                   itype(restrict _Ptr<const struct tm>));

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C
