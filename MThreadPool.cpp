//
// Created by 龙佳琳 on 2018/5/6.
//
#include "MThreadPool.h"
MThreadPool::MThreadPool() {
    maxnum_thread=30;
    minavli_thread=5;
    maxavli_thread=20;
    initnum_thread=10;
    currIdlenum_thread=0;
    for(int i=0;i<initnum_thread;i++)
    {
        MWorkThread * workThread_ptr=new MWorkThread();
        addToIdleList(workThread_ptr);
        addToAllList(workThread_ptr);
        workThread_ptr->start();
    }
}
/*全参数的线程池构造函数，方便线程池管理类构建自己想要大小的线程池*/
MThreadPool::MThreadPool(unsigned int max, unsigned int minIdle, unsigned int maxIdle, unsigned int initNum ) {
    assert(initNum>0&&minIdle<maxIdle&&minIdle<max&&maxIdle<max&&initNum<max);
    initnum_thread=initNum;
    maxnum_thread=max;
    minavli_thread=minIdle;
    maxavli_thread=maxIdle;
    for(int i=0;i<initnum_thread;i++)
    {
        MWorkThread * workThread_ptr=new MWorkThread();
        workThread_ptr->set_threadPool(this);
        addToIdleList(workThread_ptr);
        workThread_ptr->start();
    }
}
MThreadPool::~MThreadPool() {
    destoryThreadPool();
}
void MThreadPool::createIdleThread(int num) {
    for(int i=0;i<num;i++)
    {
        MWorkThread * newThread_ptr=new MWorkThread();
        newThread_ptr->set_threadPool(this);
        addToAllList(newThread_ptr);
        currIdlenum_thread_mux.lock_mux();
        currIdlenum_thread++;
        currIdlenum_thread_mux.unlock_mux();
    }
}
void MThreadPool::addToIdleList(MWorkThread *idleThread) {
    idleMutex.lock_mux();
    idleList.push_back(idleThread);
    addToAllList(idleThread);
    idleMutex.unlock_mux();
}
void MThreadPool::addToAllList(MWorkThread *thread) {
    allMutex.lock_mux();
    allList.push_back(thread);
    allMutex.unlock_mux();
}
void MThreadPool::moveToBusyList(MWorkThread *runThread) {
    busyMutex.lock_mux();
    busyList.push_back(runThread);
    currIdlenum_thread_mux.lock_mux();
    currIdlenum_thread--;
    currIdlenum_thread_mux.unlock_mux();
    busyMutex.unlock_mux();

    idleMutex.lock_mux();
    std::vector<MWorkThread *>::iterator itor;
    for(itor=idleList.begin();itor<idleList.end();itor++)
    {
        if(*itor==runThread)
        {
            break;
        }
    }
    if(itor!=idleList.end())
    {
        idleList.erase(itor);
    }
    idleMutex.unlock_mux();
}
void MThreadPool::moveToIdleList(MWorkThread *busyToIdLeThread) {
    idleMutex.lock_mux();
    idleList.push_back(busyToIdLeThread);
    currIdlenum_thread_mux.lock_mux();
    currIdlenum_thread++;
    currIdlenum_thread_mux.unlock_mux();
    idleMutex.unlock_mux();

    busyMutex.lock_mux();
    std::vector<MWorkThread *>::iterator itor;
    for(itor=busyList.begin();itor<busyList.end();itor++)
    {
        if(*itor==busyToIdLeThread)
        {
            break;
        }
    }
    if(itor!=busyList.end())
    {
        busyList.erase(itor);
    }
    busyMutex.unlock_mux();
    idleCond.cond_signal();
    maxnum_threadCond.cond_signal();
}
void MThreadPool::deleteIdleThread(int num) {
    std::cout<<"Begin to delete "<<num<<"idle threads."<<std::endl;
    idleMutex.lock_mux();
    for(int i=0;i<num;i++)
    {
        if(idleList.size()>0)
        {
            idleList.erase(idleList.begin());
            currIdlenum_thread_mux.lock_mux();
            currIdlenum_thread--;
            currIdlenum_thread_mux.unlock_mux();
        }
        else
        {
            std::cout<<"There is no additional thread in idleList."<<std::endl;
            break;
        }
        std::cout<<idleList.size()<<" idle thread in idleList"<<std::endl;
    }
    idleMutex.unlock_mux();
}
void MThreadPool::destoryThreadPool() {
    for(int i=0;i<allList.size();i++)
    {
        MWorkThread * temp_ptr=allList[i];
        temp_ptr->destoryThread();
    }
}
MWorkThread* MThreadPool::getIdleThread() {
    while(idleList.size()==0)//此时为0代表全是繁忙线程，并且无法创建新空闲线程，只能等待繁忙线程移向空闲线程时signal
    {
        std::cout<<"There is no idle thread in IdleList, wait for a moment."<<std::endl;
        idleCond.cond_wait();
    }
    /*有空闲线程时*/
    idleMutex.lock_mux();
    if(idleList.size()>0)
    {
        MWorkThread * idle_ptr=idleList.front();
        idleMutex.unlock_mux();
        return idle_ptr;
    }
    idleMutex.unlock_mux();
    return nullptr;//假如由有多个线程等待cond_signal,但是该线程在接收到signal信号后没抢到锁，因此只能返回nullptr
}

void MThreadPool::run(MThreadJob *job, void *jobdata) {
    assert(job!= nullptr);
    if(get_busyNum()==maxnum_thread)
    {
        maxnum_threadCond.cond_wait();
    }
    if(idleList.size()<minavli_thread)
    {
        /*假如最低数量的空闲线程未被满足，则判断创建达到最低线程数量的空闲线程是否会超过最大数量*/
        if(get_allNum()+minavli_thread-idleList.size()<=maxnum_thread)
        {
            createIdleThread(minavli_thread-idleList.size());
        } else
        {
            createIdleThread(maxnum_thread-get_allNum());
        }
    }
    MWorkThread * idle_ptr=getIdleThread();
    if(idle_ptr!= nullptr)
    {
        idle_ptr->work_mux.lock_mux();
        moveToBusyList(idle_ptr);
        job->SetWorkThread(idle_ptr);
        idle_ptr->AddJob(job,jobdata);
        idle_ptr->work_mux.unlock_mux();
    }
    else
    {
        std::cout<<"There is no avaliable idle thread to run the job."<<std::endl;
    }
}