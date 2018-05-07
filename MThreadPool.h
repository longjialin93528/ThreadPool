//
// Created by long on 2018/5/1.
//

#ifndef THREADPOOL_MTHREADPOOL_H
#define THREADPOOL_MTHREADPOOL_H

#include <vector>
#include "MThreadMutex.h"
#include "MThreadCond.h"
#include "MWorkThread.h"
class MThreadPool
{
    friend class MWorkThread;
private:
    unsigned int maxnum_thread;//最大的线程数量
    unsigned int minavli_thread;//空闲线程的最小数量
    unsigned int maxavli_thread;//空闲线程的最大数量
    unsigned int currIdlenum_thread;//当前空闲线程的数量
    unsigned int initnum_thread;//线程池初始数量
protected:
    MWorkThread* getIdleThread();
    void addToAllList(MWorkThread* thread);
    void addToIdleList(MWorkThread * idleThread);
    void moveToBusyList(MWorkThread * runThread);
    void moveToIdleList(MWorkThread * busyToIdLeThread);
    /*操作空闲的线程队列里空闲数量*/
    void deleteIdleThread(int num);
    void createIdleThread(int num);
public:
    /*互斥量*/
    MThreadMutex idleMutex;
    MThreadMutex busyMutex;
    MThreadMutex mux;
    /*条件变量*/
    MThreadCond idleCond;
    MThreadCond busyCond;
    MThreadCond cond;
    /*线程队列*/
    std::vector<MWorkThread *> allList;
    std::vector<MWorkThread *> idleList;
    std::vector<MWorkThread *> busyList;
public:
    MThreadPool();
    MThreadPool(unsigned int initNum);
    virtual ~MThreadPool();

    void set_maxNum(int num){maxnum_thread=num;}
    int get_maxNum(){return maxnum_thread;}

    void set_minavliNum(int num){minavli_thread=num;}
    int get_minavliNum(){return minavli_thread;}

    void set_maxavliNum(int num){maxavli_thread=num;}
    int get_maxavliNum(){return maxavli_thread;}

    void set_initNum(int num){initnum_thread=num;}
    int get_initNum(){return initnum_thread;}

    int get_currIdleNum(){return currIdlenum_thread;}
    int get_allNum(){return allList.size();}
    int get_busyNum(){return busyList.size();}

    void destoryThreadPool();
    void run(MThreadJob* job,void * jobdata);
};
#endif //THREADPOOL_MTHREADPOOL_H
