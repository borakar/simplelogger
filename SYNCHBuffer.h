#ifndef SYNC_BUFFER_H
#define SYNC_BUFFER_H

#define CIRCULAR_BUFFER_SIZE 1024;
#include <list>
#include <pthread.h>


/*template<class T>
class ISynchronizedBuffer
{
  public:
    virtual ~ISynchronizedBuffer() {};
    virtual bool add(T pkt) = 0;
    virtual bool get(T pkt) = 0;
    virtual bool read(T pkt) = 0;
    virtual bool clear() = 0;
    virtual bool isEmpty() = 0;
    virtual size_t size() = 0;
};*/

template<class T>
class SYNCHBuffer /*: public ISynchronizedBuffer<T>*/
{
  private:
    /*boost::mutex m_mutex;
    boost::circular_buffer<T> m_circularBuffer;*/
	std::list<T> m_circularBuffer;
    pthread_mutex_t m_mutex;

  public:
    SYNCHBuffer();

    virtual ~SYNCHBuffer();
    virtual bool add(T pkt);
    virtual bool get(T &pkt);
    virtual bool read(T &pkt);
    virtual bool clear();
    virtual bool isEmpty();
    virtual size_t size();
};

#endif
