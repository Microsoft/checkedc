//---------------------------------------------------------------------//
// Bounds-safe interfaces for some functions in arpa/inet.h that       //
// take pointer arguments.                                             //
//                                                                     //
// These are POSIX-only                                                //
/////////////////////////////////////////////////////////////////////////

// The Windows environment may not have arpa/inet.h
#if defined __has_include_next && __has_include_next(<arpa/inet.h>)

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <arpa/inet.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __INET_CHECKED_H
#define __INET_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

extern in_addr_t inet_addr (const char *__cp : itype(_Nt_array_ptr<const char>)) __THROW;
extern int inet_aton(const char *cp : itype(_Nt_array_ptr<const char>),
                     struct in_addr *inp : itype(_Ptr<struct in_addr>));

extern char *inet_ntoa(struct in_addr) : itype(_Nt_array_ptr<char>);
_Unchecked
extern const char *inet_ntop(int af, const void *restrict src,
                             char *restrict : itype(restrict _Array_ptr<char>) byte_count(size),
                             socklen_t size) : itype(_Nt_array_ptr<const char>);
_Unchecked
extern int inet_pton(int af,
                     const char *restrict src : itype(restrict _Nt_array_ptr<const char>),
                     void *restrict dst);

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C

#else // doesn't have arpa/inet.h
#error "cannot include 'arpa/inet_checked.h' because this system does not have the original 'arpa/inet.h'"
#endif
