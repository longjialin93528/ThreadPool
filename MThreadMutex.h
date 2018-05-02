//
// Created by long on 2018/5/1.
//

#ifndef THREADPOOL_MTHREADMUTEX_H
#define THREADPOOL_MTHREADMUTEX_H

#include <pthread.h>
class MThreadMutex
{
private:
    pthread_mutex_t mux;
public:
    MThreadMutex();
    ~MThreadMutex();
    bool lock_mux();
    bool unlock_mux();
    bool trylock_mux();
    pthread_mutex_t *get_mux();
};
#endif //THREADPOOL_MTHREADMUTEX_H
