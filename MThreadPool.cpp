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
MThreadPool::MThreadPool(unsigned int initNum) {
    assert(initNum>0&&initNum<=30);
    initnum_thread=initNum;
    minavli_thread=(initNum-10>0)?initNum-10:5;
    maxavli_thread=(initNum+10)?initNum+10:20;
    for(int i=0;i<initnum_thread;i++)
    {
        MWorkThread * workThread_ptr=new MWorkThread();
        addToIdleList(workThread_ptr);
        workThread_ptr->start();
    }
}
MThreadPool::~MThreadPool() {
    destoryThreadPool();
}
void MThreadPool::destoryThreadPool() {
    for(int i=0;i<allList.size();i++)
    {
        MWorkThread * temp_ptr=allList[i];
        temp_ptr->join();
    }
}