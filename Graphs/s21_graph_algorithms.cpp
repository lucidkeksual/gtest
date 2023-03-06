# include"./s21_graph_algorithms.h"

GraphAlgorithms::GraphAlgorithms(){}

GraphAlgorithms::~GraphAlgorithms(){}

std::vector<int> GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex){
    if(!graph.length() || startVertex <= 0 || startVertex > graph.length())
        throw GraphAlgorithms::emptyGraph();
    std::vector<int>  checkArr(graph.length());
    Queue <int>path;
    std::vector<int> res(graph.length());
    int iter = 0;
    path.push(startVertex);
    checkArr[startVertex - 1]= 1;
    while (path.length())
    {
        const std::vector<int> vertexes = graph.getAllLinks(path.peek());
        for (std::vector<const int>::iterator i = vertexes.begin(); i != vertexes.end(); i++){
            if (!checkArr[*i - 1]){
                path.push(*i);
                checkArr[*i - 1]= 1;
            }
        }
        res[iter] = path.pop();
        iter++;
    }
    return res;
}

std::vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex){
    if(!graph.length() || startVertex <= 0 || startVertex > graph.length())
        throw GraphAlgorithms::emptyGraph();
    std::vector<int>  checkArr(graph.length());
    Stack <int>path;
    std::vector<int> res(graph.length());
    int iter = 0;
    int wasAdded = 0;
    res[0] = startVertex;
    path.push(startVertex);
    checkArr[startVertex - 1]= 1;
    while (iter != graph.length() - 1)
    {
        wasAdded = 0;
        const std::vector<int> vertexes = graph.getAllLinks(path.peek());
        for (std::vector<const int>::iterator i = vertexes.begin(); i != vertexes.end(); i++){
            if (!checkArr[*i - 1]){
                path.push(*i);
                checkArr[*i - 1]= 1;
                iter++;
                res[iter] = path.peek();
                wasAdded = 1;
                break;
            }
        }
        if (!wasAdded)
            path.pop();
        
    }
    return res;
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2){
    if(!graph.length() || vertex1 <= 0 || vertex1 > graph.length() || vertex2 <= 0 || vertex2 > graph.length())
        throw GraphAlgorithms::emptyGraph();
    std::vector<int>    checkedVertexes(graph.length());
    std::vector<int>    paths(graph.length());
    Queue<int>          queue;
    queue.push(vertex1);
    while (queue.length()){
        const std::vector<int> vertexes = graph.getAllLinks(queue.peek());
        for (std::vector<const int>::iterator i = vertexes.begin(); i != vertexes.end(); i++){
            if(!checkedVertexes[*i - 1])
                queue.push(*i);
            if(*i != vertex1 && (paths[*i - 1] == 0 || paths[*i - 1] > paths[queue.peek() - 1] + graph.getPath( queue.peek(), *i)))
                paths[*i - 1] = paths[ queue.peek() - 1] + graph.getPath(queue.peek(), *i);
        }
        checkedVertexes[queue.pop() - 1] = 1;
    }
    return paths[vertex2 - 1];
}

std::vector<std::vector<int> > GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph){
    if(!graph.length())
        throw GraphAlgorithms::emptyGraph();
    std::vector<std::vector<int> > result(graph.length());
    for (int vert = 1; vert <= graph.length(); vert++){
        Queue<int> queue;
        queue.push(vert);
        result[vert - 1] = std::vector<int>(graph.length());
        std::vector<int> checked(graph.length());
        checked[vert - 1] = 1;
        while (queue.length()){
            const std::vector<int> vertexes = graph.getAllLinks(queue.peek());
            for (std::vector<const int>::iterator iter = vertexes.begin(); iter < vertexes.end(); iter++){
                if(vert == *iter)    
                    continue;
                if(!checked[*iter - 1])
                    queue.push(*iter);
                if((result[vert - 1][*iter - 1] == 0 || result[vert - 1][*iter - 1] > graph.getPath(queue.peek(), *iter) + result[vert - 1][queue.peek() - 1]))
                    result[vert - 1][*iter - 1] = graph.getPath(queue.peek(), *iter) + result[vert - 1][queue.peek() - 1];
            }
            checked[queue.pop() - 1] = 1;
        }
    }
    
    return result;
}

int GraphAlgorithms::checkVertexStart(Graph &graph){
    int vertStart = 1;
    while(1){
        const std::vector<int> vertexes = graph.getAllLinks(vertStart);
        if(vertexes.empty()){
            vertStart++;
            if(vertStart > graph.length()){
                vertStart = 0;
                break;
            }
        } else 
            break;
    }
    return vertStart;
}

// не работает на графе 10 ебал рот это фиксик хотя если заебаться то можно после алгоса сделать проверку на целосность графа

std::vector<std::vector<int> > GraphAlgorithms::getLeastSpanningTree(Graph &graph){
    if(!graph.length())
        throw GraphAlgorithms::emptyGraph();
    int vert = 1;
    int edges = 0;
    std::vector<std::vector<int> > result(graph.length());
    for (int i = 0; i < graph.length(); i++)
        result[i] = std::vector<int>(graph.length());
    while(vert <= graph.length() && edges < graph.length() - 1){
        int buf = 0;
        for (int iter = 1; iter <= graph.length(); iter++){
            if((buf == 0 || \
                (graph.getPath(vert, buf) > graph.getPath(vert, iter) && graph.getPath(vert, iter) > 0) \
                || (graph.getPath(buf, vert) > graph.getPath(iter, vert) && graph.getPath(iter, vert) > 0)) \
                && (!result[vert - 1][iter - 1] && (graph.getPath(vert, iter) > 0 || graph.getPath(iter, vert) > 0)))
                    buf = iter;
        }
        // std::cout <<  vert << " - " << buf << " edges = " << edges << "\n";
        if(buf != 0){
            if((graph.getPath(vert, buf) < (graph.getPath(buf, vert) && graph.getPath(vert, buf) > 0)) || graph.getPath(buf, vert) == 0){
                result[vert - 1][buf - 1] = graph.getPath(vert, buf);
                result[buf - 1][vert - 1] = graph.getPath(vert, buf);
            } else {
                result[vert - 1][buf - 1] = graph.getPath(buf, vert);
                result[buf - 1][vert - 1] = graph.getPath(buf, vert);
            }
            edges++;
        }
        vert++;
    }
    return result;
}

const char * GraphAlgorithms::emptyGraph::what() const throw() {
    return "emptyGraph\n";
}

double GraphAlgorithms::makeGrade(double num, double grade){
    return std::exp(std::log(num) * grade);
}


TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph){
    TsmResult res;
    double alf = 1; // mark 2.3 - 261 2.4 - 256 2.5 - 257
    double bet = 2; // distance 2.7 - 261 2.7 - 256 2.7 - 257
    double Q = 10;
    int sameCount = 0;
    int minDist = -1;
    std::vector<int> path(graph.length() + 1);
    std::vector<std::vector<double> > labels(graph.length());
    for (int i = 0; i < graph.length(); i++)
        labels[i] = std::vector<double>(graph.length());
    std::vector<antData> ants(graph.length());
    for (int i = 0; i < graph.length(); i++){
        ants[i].checked.resize(graph.length());
        ants[i].res.vertices.resize(graph.length() + 1);
        for (int iter = 0; iter < graph.length(); iter++)
            ants[i].res.vertices[iter] = 0;
        ants[i].res.vertices[0] = i + 1;
        ants[i].checked[i] = 1;
        if (i % 10 == 0){
            ants[i].isElit = true;
        }
    }
    for (int some = 0; some <= 2000; some++){
        for (int i = 0; i < graph.length(); i++){
            ants[i].res.distance = 0;
            for (int ii = 0; ii < graph.length(); ii++){                
                ants[i].checked[ii] = i == ii ? 1 : 0;
            }
        }
        for(int step = 1; step <= graph.length(); step++){
            for (int antNum = 0; antNum < graph.length(); antNum++){
                if(ants[antNum].res.vertices[step - 1] == 0)
                    continue;
                const std::vector<int> vertexes = graph.getAllLinks(ants[antNum].res.vertices[step - 1]);
                std::vector<double> hArr(vertexes.size());
                double hSum = 0;
                for (int iter = 0; iter < (int)vertexes.size(); iter++){
                    double H = 0;
                    if(!ants[antNum].checked[vertexes[iter] - 1] || (step == graph.length() && vertexes[iter] == ants[antNum].res.vertices[0])){
                        if(labels[ants[antNum].res.vertices[step - 1] - 1][vertexes[iter] - 1] < 1){
                            labels[ants[antNum].res.vertices[step - 1] - 1][vertexes[iter] - 1] = 1;
                            labels[vertexes[iter] - 1][ants[antNum].res.vertices[step - 1] - 1] = 1;
                        }
                        double N = (double)1 / (double)graph.getPath(ants[antNum].res.vertices[step - 1], vertexes[iter]);
                        H =  this->makeGrade(N, bet) * this->makeGrade(labels[ants[antNum].res.vertices[step - 1] - 1][vertexes[iter] - 1], alf);
                    }
                    hSum += H;
                    hArr[iter] = H;
                    
                }
                int vertToGo = -1;
                if (ants[antNum].isElit)
                {
                    double max = 0;
                    for (int i = 0; i < (int)hArr.size(); i++){
                        if(hArr[i] / hSum * 100 > max || (max == 0 && hArr[i] != 0)){
                            vertToGo = i;
                        }
                    }
                } else{
                    int num = 1 + rand() % (100 - 1);
                    double roulette = 0;
                    for (int i = 0; i < (int)hArr.size(); i++){
                        roulette += hArr[i] / hSum * 100;
                        if(roulette > num){
                            vertToGo = i;
                            break;
                        }
                    }
                }
                if(vertToGo != -1){
                    ants[antNum].checked[vertexes[vertToGo] - 1] = 1;
                    labels[ants[antNum].res.vertices[step - 1] - 1][vertexes[vertToGo] -1] += Q / graph.getPath(ants[antNum].res.vertices[step - 1], vertexes[vertToGo]);
                    labels[vertexes[vertToGo] -1][ants[antNum].res.vertices[step - 1] - 1] += Q / graph.getPath(ants[antNum].res.vertices[step - 1], vertexes[vertToGo]);
                    ants[antNum].res.vertices[step] = vertexes[vertToGo];
                    ants[antNum].res.distance += graph.getPath(ants[antNum].res.vertices[step - 1], vertexes[vertToGo]);
                }
                
            }
            for (std::vector< std::vector<double> >::iterator i = labels.begin(); i < labels.end(); i++){
                for (std::vector<double>::iterator iter = (*i).begin(); iter < (*i).end(); iter++){
                    *iter *= 0.5;
                }
            }
        }
        int min = 0;
        for(int iter = 0; iter < graph.length(); iter++){
            if (ants[iter].res.distance < ants[min].res.distance)
                min = iter;
        }
        if (minDist == ants[min].res.distance )
            sameCount++; 
        if (ants[min].res.distance < minDist || minDist == -1){
            sameCount = 0;
            minDist = ants[min].res.distance;
            for (int i = 0; i <= graph.length(); i++)
                path[i] = ants[min].res.vertices[i];
        }
        if (sameCount >= 5){
            break ;
        }
        
    }
    res.distance = minDist;
    res.vertices = path;
    return res;
}