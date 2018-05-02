//
// Created by 龙佳琳 on 2018/5/2.
//

#ifndef THREADPOOL_MTHREADCOND_H
#define THREADPOOL_MTHREADCOND_H
#include <pthread.h>
#include "MThreadMutex.h"
class MThreadCond
{
private:
    pthread_cond_t cond;
    MThreadMutex mux;
public:
    MThreadCond(MThreadMutex mutex);
    ~MThreadCond();
    void cond_wait();
    void cond_signal();
};
#endif //THREADPOOL_MTHREADCOND_H
