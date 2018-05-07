//
// Created by 龙佳琳 on 2018/5/1.
//

#ifndef THREADPOOL_MWORKTHREAD_H
#define THREADPOOL_MWORKTHREAD_H

#include "MThread.h"
#include "MThreadJob.h"
#include "MThreadMutex.h"
#include "MThreadCond.h"
class MWorkThread:public MThread
{
private:
    MThreadJob * ptr_MThreadJob;
    void * MThreadJobData;
    MThreadMutex pri_mux;
    bool end_thread;
public:
    MThreadMutex work_mux;
    MThreadCond cond;
public:
    MWorkThread();
    ~MWorkThread();
    void MThreadRun();
    void AddJob(MThreadJob * pjob,void * jobdata);
    MThreadJob * GetJob();


};
#endif //THREADPOOL_MWORKTHREAD_H
