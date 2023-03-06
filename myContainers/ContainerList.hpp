#ifndef CONTAINERLIST_HPP
# define CONTAINERLIST_HPP
# include<iostream>

template<typename T> 
class ContainerList
{
private:
    // ContainerList *prev;
    ContainerList *next;
    const T       data;
public:
    T       getData();
    // void    setPrev(ContainerList *prev);
    void    setNext(ContainerList *next);
    // ContainerList *getPrev();
    ContainerList *getNext();
    ContainerList(T data);
    class NullPointerException : std::exception{
        public:
           virtual const char *what () const throw();
    };
};

#include "ContainerList.tpp"

#endif