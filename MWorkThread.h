//
// Created by 龙佳琳 on 2018/5/1.
//

#ifndef THREADPOOL_MWORKTHREAD_H
#define THREADPOOL_MWORKTHREAD_H

#include "MThread.h"
#include "MThreadJob.h"
#include "MThreadPool.h"
#include "MThreadMutex.h"
class MWorkThread:public MThread
{
private:
    MThreadPool * ptr_MThreadPool;
    MThreadJob * ptr_MThreadJob;
    void * MThreadJobData;
    MThreadMutex mux;
public:
    MWorkThread();
    virtual ~MWorkThread();
    void MThreadRun();
    void AddJob(MThreadJob * pjob,void * jobdata);
    MThreadJob * GetJob(){
        return ptr_MThreadJob;
    }
    void SetThreadPool(MThreadPool * ptr_pool)
    {
        ptr_MThreadPool=ptr_pool;
    }
    MThreadPool * GetMThreadPool()
    {
        return ptr_MThreadPool;
    }
    void MThrendOver();
};
#endif //THREADPOOL_MWORKTHREAD_H
