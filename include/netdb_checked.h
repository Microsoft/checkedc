//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in netdb.h that                //
// take pointer arguments.                                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

// The Windows environment may not have netdb.h
#if defined __has_include_next && __has_include_next(<netdb.h>)

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <netdb.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __NETDB_CHECKED_H
#define __NETDB_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

extern struct hostent *gethostbyname(const char *name : itype(_Nt_array_ptr<const char>)) : itype(_Ptr<struct hostent>);
_Unchecked
extern struct hostent *gethostbyaddr(const void *addr : byte_count(len), socklen_t len, int type);

int getaddrinfo(const char *node : itype(_Nt_array_ptr<const char>) , const char *service : itype(_Nt_array_ptr<const char>),
                const struct addrinfo *hints : itype(_Ptr<const struct addrinfo>),
                struct addrinfo **res : itype(_Nt_array_ptr<_Ptr<struct addrinfo>>));
void freeaddrinfo(struct addrinfo *res : itype(_Ptr<struct addrinfo>));
const char *gai_strerror(int errcode) : itype(_Nt_array_ptr<const char>);

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C

#else // doesn't have netdb.h
#error "cannot include 'netdb_checked.h' because this system does not have the original 'netdb.h'"
#endif
