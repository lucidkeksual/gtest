#ifndef STACK_HPP
#define STACK_HPP

template<typename T> 
class Stack: public Container<T>
{

    public:
        Stack();
        virtual ~Stack();
        void    push(T value);
        Stack   *init();
    
};

#include"Stack.tpp"

#endif