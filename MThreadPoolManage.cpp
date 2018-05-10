//
// Created by 龙佳琳 on 2018/5/10.
//

#include "MThreadPoolManage.h"
MThreadPoolManager::MThreadPoolManager() {
    pool_ptr=new MThreadPool();//执行线程池无参数默认构造函数
}
MThreadPoolManager::MThreadPoolManager(unsigned int max, unsigned int minIdle, unsigned int maxIdle, unsigned int initNum) {
    pool_ptr=new MThreadPool(max,minIdle,maxIdle,initNum);//执行全参数的线程池构造函数
}
MThreadPoolManager::~MThreadPoolManager() {
    if(pool_ptr!= nullptr)
    {
        pool_ptr->destoryThreadPool();
        delete pool_ptr;
    }
}
void MThreadPoolManager::manager_run(MThreadJob *job, void *data) {
    pool_ptr->run(job,data);
}