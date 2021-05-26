//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in threads.h that              //
// take pointer arguments.                                             //
//                                                                     //
// These are listed in the same order that they occur in the C11       //
// specification.                                                      //
/////////////////////////////////////////////////////////////////////////



#ifdef _CHECKEDC_MOCKUP_THREADS
// C implementations may not support the C11 threads package or even the
// macro that says C11 threads are not supported.  This mocks up
// the types needed by threads so that we can test that the declarations
// below compile.
typedef struct __once_flag_struct once_flag;
typedef struct __cnd_struct cnd_t;
typedef struct __mtx_struct mtx_t;
typedef struct __thread_struct thrd_t;
typedef int (*thrd_start_t)(void *);
typedef struct __thread_specific_storage_struct tss_t;
typedef void (tss_dtor_t)(void *);
struct timespec;
#else

#if defined __has_include_next && __has_include_next(<threads.h>)

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <threads.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#else // doesn't have threads.h
#error "cannot include 'threads_checked.h' because this system does not have the original 'threads.h'"
#endif // threads.h
#endif // _CHECKEDC_MOCKUP_THREADS


#if defined _CHECKEDC_MOCKUP_THREADS || \
    (defined __has_include_next && __has_include_next(<threads.h>))

#ifdef __checkedc
#ifndef __THREADS_CHECKED_H
#define __THREADS_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

void call_once(once_flag *flag : itype(_Ptr<once_flag>),
               void ((*fn)(void)) : itype(_Ptr<void (void)>));

int cnd_broadcast(cnd_t *condition : itype(_Ptr<cnd_t>));
void cnd_destroy(cnd_t *condition : itype(_Ptr<cnd_t>));
void cnd_init(cnd_t *condition : itype(_Ptr<cnd_t>));
int cnd_signal(cnd_t *condition : itype(_Ptr<cnd_t>));
int cnd_timedwait(cnd_t *restrict cond : itype(restrict _Ptr<cnd_t>),
                  mtx_t *restrict mutex: itype(restrict _Ptr<mtx_t>),
                  const struct timespec *restrict spec :
                    itype(restrict _Ptr<const struct timespec>));
int cnd_wait(cnd_t *condition : itype(_Ptr<cnd_t>),
             mtx_t *mutex : itype(_Ptr<mtx_t>));
void mtx_destroy(mtx_t *mutex : itype(_Ptr<mtx_t>));
int mtx_init(mtx_t *mutex : itype(_Ptr<mtx_t>), int type);
int mtx_lock(mtx_t *mutex : itype(_Ptr<mtx_t>));
int mtx_timedlock(mtx_t *restrict mutex : itype(restrict _Ptr<mtx_t>),
                  const struct timespec *restrict ts :
                    itype(restrict _Ptr<const struct timespec>));
int mtx_trylock(mtx_t *mtex : itype(_Ptr<mtx_t>));
int mtx_unlock(mtx_t *mtex : itype(_Ptr<mtx_t>));

int thrd_create(thrd_t *thr : itype(_Ptr<thrd_t>),
                thrd_start_t func :
                  itype(_Ptr<int (void * : itype(_Ptr<void>))>),
                void *arg : itype(_Ptr<void>));
int thrd_join(thrd_t thr, int *res : itype(_Ptr<int>));
int thrd_sleep(const struct timespec *duration :
                 itype(_Ptr<const struct timespec>),
               struct timespec *remaining : itype(_Ptr<struct timespec>));
int tss_create(tss_t *key : itype(_Ptr<tss_t>),
               tss_dtor_t dtor :
                 itype(_Ptr<void (void * : itype(_Ptr<void>))>));
// Casting the Ptr<void> returned by tss_get to a specific type will be an
// unchecked operation.
void *tss_get(tss_t key) : itype(_Ptr<void>);
int tss_set(tss_t key, void *value : itype(_Ptr<void>));

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C 

#endif
