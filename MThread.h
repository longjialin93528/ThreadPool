//
// Created by 龙佳琳 on 2018/4/25.
//

#ifndef THREADPOOL_MTHREAD_H
#define THREADPOOL_MTHREAD_H

#include <sys/types.h>
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
    void * thread_exit_message;
    void * join_message;
    pthread_t tid;//unsigned long int,若是printf输出需要 %lu 格式
protected:
    static void* ThreadFunction(void *);
public:
    MThread();
    virtual ~MThread();//定义为虚函数，确保以正确的顺序析构
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

    pthread_t get_pthread_t();

    void start();
    void join(pthread_t tid_wait);
    virtual void MThreadRun()=0;

};
#endif //THREADPOOL_MTHREAD_H
