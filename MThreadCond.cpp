//
// Created by 龙佳琳 on 2018/5/2.
//
#include "MThreadCond.h"
MThreadCond::MThreadCond() {
    pthread_cond_init(&cond, nullptr);
}
MThreadCond::MThreadCond(MThreadMutex mutex):mux(mutex) {
    pthread_cond_init(&cond, nullptr);
}
MThreadCond::~MThreadCond() {
    pthread_cond_destroy(&cond);
}
void MThreadCond::cond_wait() {
    mux.lock_mux();
    pthread_cond_wait(&cond,mux.get_mux());
    mux.unlock_mux();
}
void MThreadCond::cond_signal() {
    pthread_cond_signal(&cond);
}
