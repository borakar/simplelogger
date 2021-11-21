#ifndef _CTHREAD_H
#define _CTHREAD_H

#include "pthread.h"

class CThread
{
  public:
    CThread();
	~CThread();
    int start();
    int join();
    int detach();
    pthread_t self();
    virtual void* run() = 0;

  private:
    pthread_t m_tid;
    int m_running;
    int m_detached;
};

#endif
