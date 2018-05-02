#include "MWorkThread.h"

//
// Created by 龙佳琳 on 2018/5/1.
//
MWorkThread::MWorkThread() {
    ptr_MThreadPool= nullptr;
    ptr_MThreadJob= nullptr;
    MThreadJobData= nullptr;
}
MWorkThread::~MWorkThread() {

}