#include "MWorkThread.h"

//
// Created by 龙佳琳 on 2018/5/1.
//
#include "MThreadPool.h"
MWorkThread::MWorkThread() {
    ptr_MThreadJob= nullptr;
    MThreadJobData= nullptr;
    threadPool_ptr= nullptr;
    workThread_exit_message=(void*)(0);
}
MWorkThread::~MWorkThread() {
    if(ptr_MThreadJob!= nullptr)
    {
        delete ptr_MThreadJob;
    }
    if(threadPool_ptr!= nullptr)
    {
        delete threadPool_ptr;
    }
    if(MThreadJobData!= nullptr)
    {
        delete MThreadJobData;
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
void MWorkThread::destoryThread() {
    work_mux.lock_mux();//线程运行时会占用此锁，所以用此锁可以避免打断线程运行
    set_isThreadExit(true);
    ptr_MThreadJob= nullptr;
    MThreadJobData= nullptr;
    cond.cond_signal();//给run中阻塞的cond发信号
    work_mux.unlock_mux();
    pthread_exit(workThread_exit_message);
}
void MWorkThread::MThreadRun() {
    set_MThreadstate(THREAD_RUN);
    while(1)
    {
        while(ptr_MThreadJob== nullptr&&!get_isThreadExit())//持续等待任务到来并且不需要线程退出
        {
            cond.cond_wait();
        }
        if(ptr_MThreadJob== nullptr)
        {
            if(get_isThreadExit())
            {
                break;
            }
            else
            {
                continue;
            }
        }
        /*得到任务进行工作*/
        work_mux.lock_mux();//开始工作后不能中断
        ptr_MThreadJob->execute(MThreadJobData);//由实际的job类得到jobdata后进行运算
        /*任务已执行完，清空线程相关数据，方便下一次使用*/
        ptr_MThreadJob->SetWorkThread(nullptr);
        ptr_MThreadJob= nullptr;
        /*线程池操作*/
        threadPool_ptr->moveToIdleList(this);
        set_MThreadstate(THREAD_IDLE);
        if(threadPool_ptr->idleList.size()>threadPool_ptr->maxavli_thread)
        {
            threadPool_ptr->deleteIdleThread(threadPool_ptr->idleList.size()-threadPool_ptr->maxavli_thread);
        }
        work_mux.unlock_mux();
    }
    std::cout<<"Work thread exit."<<std::endl;
}