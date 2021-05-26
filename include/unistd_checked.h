//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in unistd.h that               //
// take pointer arguments.                                             //
//                                                                     //
// These are POSIX-only                                                //
/////////////////////////////////////////////////////////////////////////


// Uses clang-specific __has_include macro to detect unistd.h
// which is required by Posix Standard.
// The Windows environment also may not have unistd.h
#if defined __has_include_next && __has_include_next(<unistd.h>)

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <unistd.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __UNISTD_CHECKED_H
#define __UNISTD_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

#if _POSIX_VERSION >= 200112L

char *getpass(const char *prompt : itype(_Nt_array_ptr<const char>)) : itype(_Nt_array_ptr<char>);
char *crypt(const char *phrase : itype(_Nt_array_ptr<const char>), const char *setting : itype(_Nt_array_ptr<const char>)) : itype(_Nt_array_ptr<char>);

extern char ** environ : itype(_Nt_array_ptr<_Nt_array_ptr<char>>);

extern char *getcwd(char *buf : itype(_Nt_array_ptr<char>), size_t size) : itype(_Nt_array_ptr<char>);
extern char *getwd(char *buf : itype(_Nt_array_ptr<char>)) : itype(_Nt_array_ptr<char>);
extern char *get_current_dir_name(void) : itype(_Nt_array_ptr<char>);
extern int rmdir(const char *pathname : itype(_Nt_array_ptr<const char>));
extern int chdir(const char *p_dirname : itype(_Nt_array_ptr<const char>));
extern ssize_t readlink (const char *restrict path : itype(restrict _Nt_array_ptr<const char>),
                         char *restrict buf : itype(restrict _Nt_array_ptr<char>), size_t len);
extern int chroot(const char *dirname : itype(_Nt_array_ptr<const char>));
int unlink(const char *pathname : itype(_Nt_array_ptr<const char>));
int mkstemp(char *template : itype(_Nt_array_ptr<char>));

#ifdef __APPLE__

extern int access (const char *__name : itype(_Nt_array_ptr<const char>), int __type);
extern ssize_t read (int __fd, void *__buf : byte_count(__nbytes), size_t __nbytes);
extern ssize_t write (int __fd, const void *__buf : byte_count(__n), size_t __n);

#else

extern int access (const char *__name : itype(_Nt_array_ptr<const char>), int __type) __THROW __nonnull ((1));
extern ssize_t read (int __fd, void *__buf : byte_count(__nbytes), size_t __nbytes) __wur;
extern ssize_t write (int __fd, const void *__buf : byte_count(__n), size_t __n) __wur;

#endif

extern int execve(const char *pathname : itype(_Nt_array_ptr<const char>),
                  char * const *argv : itype(_Nt_array_ptr<const _Nt_array_ptr<char>>),
                  char * const *envp : itype(_Nt_array_ptr<const _Nt_array_ptr<char>>));

int gethostname(char *name : count(len), size_t len);

#endif

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C

#else // doesn't have unistd.h
#error "cannot include 'unistd_checked.h' because this system does not have the original 'unistd.h'"
#endif
