//
// Created by long on 2018/5/1.
//

#ifndef THREADPOOL_MTHREADJOB_H
#define THREADPOOL_MTHREADJOB_H

#include "MThread.h"
class MThreadJob{
private:
    int JobID;
    char * JobName;
    MThread* workthread;
public:
    MThreadJob();
    virtual ~MThreadJob();
    virtual void execute(void *ptr)=0;
    MThread * GetWorkThread();
    void SetWorkThread(MThread* wthd);
    int GetJobID()const
    {
        return JobID;
    }
    void SetJobID(int id)
    {
        JobID=id;
    }
    char * GetJobName()
    {
        return JobName;
    }
    void SetJobName(char * name);
};
#endif //THREADPOOL_MTHREADJOB_H
