//
// Created by long on 2018/5/1.
//
#include "MThreadMutex.h"
MThreadMutex::MThreadMutex() {
    pthread_mutex_init(&mux,NULL);
}
MThreadMutex::~MThreadMutex() {
    pthread_mutex_destroy(&mux);
}
bool MThreadMutex::lock_mux() {
    if(pthread_mutex_lock(&mux)==0)
    {
        return true;
    }
    return false;
}
bool MThreadMutex::unlock_mux() {
    if(pthread_mutex_unlock(&mux)==0)
    {
        return true;
    }
    return false;
}
bool MThreadMutex::trylock_mux() {
    if(pthread_mutex_trylock(&mux)==0)
    {
        return true;
    }
    return false;
}
