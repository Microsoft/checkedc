//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in poll.h that                 //
// take pointer arguments.                                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

// The Windows environment may not have poll.h
#if defined __has_include_next && __has_include_next(<poll.h>)

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <poll.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __POLL_CHECKED_H
#define __POLL_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

extern int poll(struct pollfd fds[] : count(nfds), nfds_t nfds, int timeout);

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C

#else // doesn't have poll.h
#error "cannot include 'poll_checked.h' because this system does not have the original 'poll.h'"
#endif
