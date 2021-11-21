#include "SYNCHBuffer.h"
#include <string>

template<class T> 
SYNCHBuffer<T>::SYNCHBuffer()
{
	//m_circularBuffer = CIRCULAR_BUFFER_SIZE;
	pthread_mutex_init(&m_mutex, NULL);
}

template<class T>
SYNCHBuffer<T>::~SYNCHBuffer()
{
    pthread_mutex_destroy(&m_mutex);
}

template<class T>
bool SYNCHBuffer<T>::add(T pkt)
{
    pthread_mutex_lock(&m_mutex);
    m_circularBuffer.push_back(pkt);
    pthread_mutex_unlock(&m_mutex);
    return true;
}

template<class T>
bool SYNCHBuffer<T>::get(T& pkt)
{
	pthread_mutex_lock(&m_mutex);
	if(!m_circularBuffer.empty())
	{
		pkt = m_circularBuffer.front();
		m_circularBuffer.pop_front();
		pthread_mutex_unlock(&m_mutex);

		return true;
	}
	else
	{
		pthread_mutex_unlock(&m_mutex);
		return false;
	}
}

template<class T>
bool SYNCHBuffer<T>::read(T& pkt)
{
    pthread_mutex_lock(&m_mutex);
    if(!m_circularBuffer.empty())
    {
		pkt = m_circularBuffer.front();
		pthread_mutex_unlock(&m_mutex);

		return true;
    }
    else
    {
		pthread_mutex_unlock(&m_mutex);

		return false;
    }
}

template<class T>
bool SYNCHBuffer<T>::clear()
{
	pthread_mutex_lock(&m_mutex);
	m_circularBuffer.clear();
	pthread_mutex_unlock(&m_mutex);

	return true;
}

template<class T>
bool SYNCHBuffer<T>::isEmpty()
{
	pthread_mutex_lock(&m_mutex);

	return m_circularBuffer.empty();
}

template<class T>
size_t SYNCHBuffer<T>::size()
{
	pthread_mutex_lock(&m_mutex);
	
	return m_circularBuffer.size();
}

template class SYNCHBuffer<std::string>;
