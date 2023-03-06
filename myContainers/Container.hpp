#ifndef CONTAINER_HPP
# define CONTAINER_HPP
# include"./ContainerList.hpp"

template<typename T>
class Container
{
protected:
    ContainerList<T> *head;
    int     len;
public:
    Container();
    virtual ~Container();
    virtual int         length();
    virtual void        showData();
    virtual T           peek();
    virtual T           pop();   
    class zeroLength : std::exception{
        public:
            virtual const char *what () const throw();
    };
};

#include"Container.tpp"


#endif