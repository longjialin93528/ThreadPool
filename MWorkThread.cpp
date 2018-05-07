#include "MWorkThread.h"

//
// Created by 龙佳琳 on 2018/5/1.
//
#include "MThreadPool.h"
MWorkThread::MWorkThread() {
    ptr_MThreadJob= nullptr;
    MThreadJobData= nullptr;
}
MWorkThread::~MWorkThread() {
    if(ptr_MThreadJob!= nullptr)
    {
        delete ptr_MThreadJob;
    }
}
MThreadJob* MWorkThread::GetJob() {
    return ptr_MThreadJob;
}
void MWorkThread::AddJob(MThreadJob *pjob, void *jobdata) {
    pri_mux.lock_mux();
    ptr_MThreadJob=pjob;
    MThreadJobData=jobdata;
    pjob->SetWorkThread(this);
    pri_mux.unlock_mux();
    cond.cond_signal();
}

void MWorkThread::MThreadRun() {
    set_MThreadstate(THREAD_RUN);
    while(1)
    {
        while(ptr_MThreadJob== nullptr)
        {
            cond.cond_wait();
        }
        ptr_MThreadJob->execute(MThreadJobData);
        ptr_MThreadJob->SetWorkThread(nullptr);
        ptr_MThreadJob= nullptr;
        /*线程池操作*/

    }
}