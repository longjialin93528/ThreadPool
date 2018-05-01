//
// Created by long on 2018/5/1.
//
#include "MThreadJob.h"
#include <cstdlib>
#include <cstring>
MThreadJob::MThreadJob() {
    JobID=0;
    JobName= nullptr;
    workthread= nullptr;
}
MThreadJob::~MThreadJob() {
    if(JobName!= nullptr)
    {
        delete JobName;
        JobName= nullptr;
    }
    if(workthread!= nullptr)
    {
        delete workthread;
        workthread= nullptr;
    }
}
MThread* MThreadJob::GetWorkThread() {
    return workthread;
}
void MThreadJob::SetWorkThread(MThread *wthd) {
    workthread=wthd;
}
void MThreadJob::SetJobName(char * name) {
    if(JobName!= nullptr)
    {
        delete JobName;
    }
    if(name!= nullptr)
    {
        JobName=new char[strlen(name)+1];
        strcpy(JobName,name);
        JobName[strlen(name)]='\0';
    }
}
