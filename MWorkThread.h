//
// Created by 龙佳琳 on 2018/5/1.
//

#ifndef THREADPOOL_MWORKTHREAD_H
#define THREADPOOL_MWORKTHREAD_H

#include "MThread.h"
#include "MThreadJob.h"
#include "MThreadMutex.h"
#include "MThreadCond.h"
class MThreadPool;
class MWorkThread:public MThread
{
private:
    MThreadJob * ptr_MThreadJob;
    void * MThreadJobData;
    MThreadPool * threadPool_ptr;
    MThreadMutex pri_mux;
public:
    MThreadMutex work_mux;
    MThreadCond cond;
public:
    MWorkThread();
    ~MWorkThread();
    void MThreadRun();
    void AddJob(MThreadJob * pjob,void * jobdata);
    MThreadJob * GetJob();
    void set_threadPool(MThreadPool * pool_ptr)
    {
        threadPool_ptr=pool_ptr;
    }
    MThreadPool * get_threadPool()
    {
        return threadPool_ptr;
    }
};
#endif //THREADPOOL_MWORKTHREAD_H
