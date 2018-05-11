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
    void * workThread_exit_message;
public:
    MThreadMutex work_mux;
    MThreadCond cond;//用来同步是否得到任务（任务即是生产者消费者中的消耗品），具体在run中消耗，在addjob中产生
public:
    MWorkThread();
    ~MWorkThread();
    void destoryThread();
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
