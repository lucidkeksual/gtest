#ifndef S21_GRAPH_ALGORITHMS_HPP
# define S21_GRAPH_ALGORITHMS_HPP
# include <cmath>
# include "../myContainers/Queue.hpp"
# include "../myContainers/Stack.hpp"
# include "./s21_graph.h"
# include "../myContainers/structs.h"

class GraphAlgorithms
{
    private:
        int checkVertexStart(Graph &graph);
        double makeGrade(double num, double grade);
    public:
        GraphAlgorithms();
        ~GraphAlgorithms();
        std::vector<int> depthFirstSearch(Graph &graph, int startVertex);//поиск в глубину возвращает массив интов
        std::vector<int> breadthFirstSearch(Graph &graph, int startVertex);//поиск в ширину массив интов 
        int getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2); //ближайший путь между вершинами возвр длину пути
        std::vector<std::vector<int> > getShortestPathsBetweenAllVertices(Graph &graph);//кратчайшее расстояние от вершины до вершин
        std::vector<std::vector<int> > getLeastSpanningTree(Graph &graph); // наименьший основной граф
        TsmResult solveTravelingSalesmanProblem(Graph &graph); // решение проблемы комивояжера муравьиный алгоритм
        class emptyGraph : std::exception{
            public:
                virtual const char *what () const throw();
        };
};

#endif