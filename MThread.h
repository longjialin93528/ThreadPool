//
// Created by 龙佳琳 on 2018/4/25.
//

#ifndef THREADPOOL_MTHREAD_H
#define THREADPOOL_MTHREAD_H

#include <_types.h>
#include <pthread.h>
#include <semaphore.h>
enum MThreadState
{
    THREAD_IDLE=0,
    THREAD_RUN,
    THREAD_EXIT
};
class MThread
{
private:
    unsigned long MThreadID;
    char * MThreadName;
    MThreadState MTState;
    int MTErrCode;
    bool is_THreadExit;
    pthread_t tid;
protected:
    static void* ThreadFunction(void *);
public:
    MThread();
    virtual ~MThread();
    void set_MThreadid(unsigned long ID);
    unsigned long get_MThreadid();
    void set_MThreadname(char *name);
    char * get_MThreadname();
    void set_MThreadstate(MThreadState mstate);
    MThreadState get_MThreadstate();
    void set_isThreadExit(bool is_exit);
    bool get_isThreadExit();
    void set_MTErrCode(int errcode);
    int get_MTErrCode();

    void start();
    void join();
    virtual void MThreadRun()=0;

};
#endif //THREADPOOL_MTHREAD_H
