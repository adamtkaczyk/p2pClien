#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue : std::queue<T>
{
public:
    using std::queue<T>::queue;
    T pop();
    void push(const T& elem);
    void push(T&& elem);
//private:
//    std::mutex mutex_;
//    std::condition_variable cv_;
};

template<typename T>
T BlockingQueue<T>::pop()
{
    T value = std::move(this->front());
    this->pop();
    return value;
}

template<typename T>
void BlockingQueue<T>::push(const T& elem)
{
    this->push(elem);
}

template<typename T>
void BlockingQueue<T>::push(T&& elem)
{
    this->push(std::move(elem));
}

#endif // BLOCKINGQUEUE_H
