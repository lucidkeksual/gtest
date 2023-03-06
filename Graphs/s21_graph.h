#ifndef S21_GRAPH_H
# define S21_GRAPH_H
# include "../myContainers/Queue.hpp"
# include <vector>



class Graph
{
    private:
        int                             len;
        int                             **dataArr;
        int                             isNum(int n);
        int                             parseRow(std::string str, int i);
        std::vector<std::vector<int> >  links;
        void                            freeDataArr();
        int                             **bzero();
    public:
        Graph();
        ~Graph();

        int                       atoi(std::string::iterator iter, int len);
        int                       getPath(int from, int to);
        int                       length();
        const std::vector<int>    getAllLinks(int root) const;
        void                      showGraph();
        void                      loadGraphFromFile(std::string fileName);
        void                      exportGraphToDot(std::string fileName);
        class unvalidFile : std::exception{
            public:
                virtual const char *what () const throw();
        };
        class unkownRoot : std::exception{
            public:
                virtual const char *what () const throw();
        };
};

#endif