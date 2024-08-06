#ifndef __INCLUDE_LOCK_H__
#define __INCLUDE_LOCK_H__

#define __LINUX__

#ifdef __LINUX__
#include <pthread.h>
#elif __WINDOWS__
#endif /* __LINUX__/__WINDOWS__ */


// mutex
typedef struct _mutex_t
{
#ifdef __LINUX__
    pthread_mutex_t lock;
#elif __WINDOWS__
#endif /* __LINUX__/__WINDOWS__ */
}mutex_t;

// init
static inline 
int mutex_init(mutex_t* lock)
{
#ifdef __LINUX__
    pthread_mutex_init(&(lock->lock), NULL);
#elif __WINDOWS__
#endif /* __LINUX__/__WINDOWS__ */
}

// destory
static inline
int mutex_destory(mutex_t* lock)
{
#ifdef __LINUX__
    pthread_mutex_destroy(&(lock->lock));
#elif __WINDOWS__
#endif /* __LINUX__/__WINDOWS__ */
}

// lock
static inline
int mutex_lock(mutex_t* lock)
{
#ifdef __LINUX__
    pthread_mutex_lock(&(lock->lock));
#elif __WINDOWS__
#endif /* __LINUX__/__WINDOWS__ */
}

// unlock
static inline
int mutex_unlock(mutex_t* lock)
{
#ifdef __LINUX__
    pthread_mutex_unlock(&(lock->lock));
#elif __WINDOWS__
#endif /* __LINUX__/__WINDOWS__ */
}

#endif /* __INCLUDE_LOCK_H__ */