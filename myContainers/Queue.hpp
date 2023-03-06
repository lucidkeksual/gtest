#ifndef QUEUE_HPP
# define QUEUE_HPP
# include"./Container.hpp"

template<typename T> 
class Queue : public Container<T>
{
    private:
        ContainerList<T> *tail;
    public:
        Queue();
        virtual ~Queue();
        void    push(T value);
        Queue   *init();
        T*      fromQueueToArr();
        void  operator+=     (Queue &otherFixed);
};

#include"Queue.tpp"

#endif