//
// Created by 龙佳琳 on 2018/4/25.
//
#include <cstring>
#include "MThread.h"
MThread::MThread() {
    MThreadID=0;
    MThreadName=new char[5];
    strcpy(MThreadName,"NONE");
    MThreadName[4]='\0';
    MTState=THREAD_IDLE;
    is_THreadExit= false;
}
MThread::~MThread() {
    delete MThreadName;
}
void MThread::set_MThreadid(unsigned long ID) {
    MThreadID=ID;
}
unsigned long MThread::get_MThreadid() {
    return MThreadID;
}
void MThread::set_MThreadname(char *name) {
    int len=strlen(name);
    MThreadName=new char[len+1];
    strcpy(MThreadName,name);
    MThreadName[len]='\0';
}
char * MThread::get_MThreadname() {
    return MThreadName;
}
void MThread::set_MThreadstate(MThreadState mstate) {
    MTState =mstate;
}
MThreadState MThread::get_MThreadstate() {
    return MTState;
}
void MThread::set_isThreadExit(bool is_exit) {
    is_THreadExit=is_exit;
}
bool MThread::get_isThreadExit() {
    return is_THreadExit;
}
void MThread::set_MTErrCode(int errcode) {
    MTErrCode=errcode;
}
int MThread::get_MTErrCode() {
    return MTErrCode;
}