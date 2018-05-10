//
// Created by 龙佳琳 on 2018/5/10.
//

#ifndef THREADPOOL_MTHREADPOOLMANAGE_H
#define THREADPOOL_MTHREADPOOLMANAGE_H

#include "MThreadPool.h"
class MThreadPoolManager
{
public:
    MThreadPoolManager();
    MThreadPoolManager(unsigned int max, unsigned int minIdle, unsigned int maxIdle, unsigned int initNum );
    ~MThreadPoolManager();
    void manager_run(MThreadJob * job,void * data);
private:
    MThreadPool * pool_ptr;
};
#endif //THREADPOOL_MTHREADPOOLMANAGE_H
