#include"./myContainers/Queue.hpp"
#include"./myContainers/Stack.hpp"
#include"./Graphs/s21_graph.h"
#include"./Graphs/s21_graph_algorithms.h"
#include<string>

int checkReq(std::string str, Graph &graph){
    std::string input;
    GraphAlgorithms worker;
    try{
        if (str.length() != 1)
            return 0;
        if(str[0] == '1'){
            std::cout << "введите путь до файла \n";
            std::getline(std::cin, input);
            graph.loadGraphFromFile(input);
            std::cout << "граф был загружен успешно\n";
        } else if(str[0] == '3' || str[0] == '2') {
            std::cout << "введите начальную вершину\n";
            std::getline(std::cin, input);
            int startVertex = graph.atoi(input.begin(), input.length());
            std::vector<int> (GraphAlgorithms::*funcsArr[])(Graph &graph, int startVertex) = {
                &GraphAlgorithms::breadthFirstSearch,
                &GraphAlgorithms::depthFirstSearch
            };
            std::vector<int> (GraphAlgorithms::*somethingToUseFuncs)(Graph &graph, int startVertex) = funcsArr[(int)str[0] - 50];
            std::vector<int> res = (worker.*somethingToUseFuncs)(graph, startVertex);
            std::cout << "результат : ";
            for (std::vector<int>::iterator i = res.begin(); i < res.end(); i++){
                std::cout << *i << (*i == *(res.end() - 1) ? "\n" : " -> ");
            }
            
        } else if(str[0] == '4'){
            std::cout << "введите начальную вершину\n";
            std::getline(std::cin, input);
            int startVertex = graph.atoi(input.begin(), input.length());
            std::cout << "введите конечную вершину\n";
            std::getline(std::cin, input);
            int endVertex = graph.atoi(input.begin(), input.length());
            std::cout << "результат : " << worker.getShortestPathBetweenVertices(graph, startVertex, endVertex) << "\n";
        } else if (str[0] == '5' || str[0] == '6'){
            std::vector<std::vector<int> > (GraphAlgorithms::*funcsArr[])(Graph &graph) = {
                &GraphAlgorithms::getShortestPathsBetweenAllVertices,
                &GraphAlgorithms::getLeastSpanningTree
            };
            std::cout << "\n " << (int)str[0] << "\n";
            std::vector<std::vector<int> > (GraphAlgorithms::*somethingToUseFuncs)(Graph &graph) = funcsArr[(int)str[0] - 53];
            std::vector<std::vector<int> > res = (worker.*somethingToUseFuncs)(graph);
            for (std::vector<std::vector<int> >::iterator i = res.begin(); i < res.end(); i++){
                for (std::vector<int>::iterator iter = (*i).begin(); iter < (*i).end(); iter++)
                    std::cout << *iter << (iter == (*i).end() -1 ? "\n" : "   ");
            }
            
        } else if (str[0] == '7'){
            TsmResult res = worker.solveTravelingSalesmanProblem(graph);
            std::cout << "наименьший путь = " << res.distance << "\n";
            for (std::vector<int>::iterator i = res.vertices.begin(); i < res.vertices.end(); i++)
                std::cout << *i << ( i == res.vertices.end() - 1 ? "\n" :" -> ");
            
        } else 
            return 0;
    } catch(const Graph::unvalidFile& e) {
        std::cerr << "ошибка при загрузке графа" << '\n';
    } catch(const GraphAlgorithms::emptyGraph& e) {
        std::cerr << "ошибка при загрузке графа" << '\n';
    }
    return 1;
}

int main()
{

    std::cout << "Hellow here you can test some graph algorithms\n" << "print 'help' to see command list\n";
    std::string helperText = "Введите номер команды из списка \n \
        1. загрузка исходного графа из файла\n \
        2. обход графа в ширину с выводом результата обхода в консоль\n \
        3. обход графа в глубину с выводом результата обхода в консоль\n \
        4. поиск кратчайшего пути между произвольными двумя вершинами с выводом результата в консоль\n \
        5. поиск кратчайших путей между всеми парами вершин в графе с выводом результирующей матрицы в консоль\n \
        6. поиск минимального остовного дерева в графе с выводом результирующей матрицы смежности в консоль\n \
        7. решение задачи комивояжера с выводом результирующего маршрута и его длины в консоль \n";
    std::string request;
    Graph mainGraph;
    while (1){
        std::getline(std::cin, request);
        if (!request.compare("help"))
            std::cout << helperText;
        else if(!checkReq(request, mainGraph))
            std::cout << "unknown command\n";
    }
    
    return 0;
}
