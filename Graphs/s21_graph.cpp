#include "s21_graph.h"
#include <fstream>

Graph::Graph(): len(0), dataArr(nullptr){
}

Graph::~Graph(){
    if(this->dataArr)
        this->freeDataArr();
}

int Graph::atoi(std::string::iterator iter, int len){
    int i = 0;
    int res = 0;
    while (i < len){
        if(this->isNum(*iter)){
            res += ((int)*iter) - 48;
        } else
            return -1;
        i++;
        iter++;
        if(i != len)
            res *= 10;
    }
    return res;
}

int Graph::isNum(int n){
    return (n >= 48 && n <= 57);
}

void Graph::loadGraphFromFile(std::string fileName){
    int lenBuf;
    std::string buf;
    std::ifstream file(fileName);
    if(file.is_open()){
        int i = 0;
        std::getline(file, buf);
        lenBuf = this->atoi(buf.begin(), buf.length());
        if(lenBuf == -1)
            throw Graph::unvalidFile();
        this->freeDataArr();
        this->len = lenBuf;
        this->dataArr = this->bzero();
        while (std::getline(file, buf)){
            if(i == this->len){
                this->freeDataArr();
                throw Graph::unvalidFile();
            }
            if(this->parseRow(buf, i)){
                this->freeDataArr();
                throw Graph::unvalidFile();
            }
            i++;
        }
        if(i != this->len){
            this->freeDataArr();
            throw Graph::unvalidFile();
        }
    } else
       throw  Graph::unvalidFile();
    
}

int Graph::parseRow(std::string str, int i){
    int wordLen = 0;
    int wordsCount = 0;
    std::vector<int> linksArr;
    this->dataArr[i] = new int[this->len];
    for (std::string::iterator iter = str.begin(); iter <= str.end(); iter++)
    {
        if((*iter == ' ' || iter == str.end()) && wordLen > 0){
            int buf = this->atoi(iter - wordLen, wordLen);
            if(buf == -1 || wordsCount == this->len)
                return 1;
            if(buf)
                linksArr.push_back(wordsCount + 1);
            this->dataArr[i][wordsCount] = buf;
            wordLen = 0;
            wordsCount++;
        } else if (*iter != ' ')
            wordLen++;
    }
    this->links.push_back(linksArr);
    if(wordsCount != this->len)
        return 1;
    return 0;
}

void Graph::freeDataArr(){
    if(this->dataArr){
        int i = 0;
        while (i < this->len && this->dataArr[i])
        {
            delete [] this->dataArr[i];
            if(!this->links.empty() && !this->links[i].empty())
                this->links[i].clear();
            i++;
        }
        delete [] this->dataArr;
        this->links.clear();
        this->dataArr = nullptr;
    }
}


int **Graph::bzero(){
    int i = 0;
    int **arr = new int*[this->len];
    while (i < this->len)
    {
        arr[i] = nullptr;
        i++;
    }
    return arr;
}


void Graph::showGraph(){
    int i = 0;
    int iter = 0;
    std::string space = "";
    while (i < this->len)
    {
        iter =0;
        while (iter < this->len)
        {
            space = "";
            if(this->dataArr[i][iter] < 10)
                space += " ";
            if(this->dataArr[i][iter] < 100)
                space += " ";
            if(this->dataArr[i][iter] < 1000)
                space += " ";
            if(this->dataArr[i][iter] < 10000)
                space += " ";
            std::cout << this->dataArr[i][iter] << space << "  ";
            iter++;
        }
        std::cout<< "\n";
        i++;
    }
}

void Graph::exportGraphToDot(std::string fileName){
    std::ofstream newFile(fileName + ".dot");
    if(newFile.is_open()){
        int isDigGrah = 0;
        int isStrStarted;
        int graphCopy[this->len][this->len];
        std::string objData = "someGraph {\n";
        for (int rootIter = 0; rootIter < this->len; rootIter++){
            for (int iter = 0; iter < this->len; iter++)
                graphCopy[rootIter][iter] = this->dataArr[rootIter][iter];
        }

        for (int rootIter = 0; rootIter < this->len; rootIter++){
            isStrStarted = 0;
            for (int iter = 0; iter < this->len; iter++){
                if (graphCopy[rootIter][iter]){
                    if(!isStrStarted){
                        objData += "    " + std::to_string(rootIter + 1);
                        isStrStarted = 1;
                    }
                    objData += " -";
                    if (graphCopy[iter][rootIter]){
                        objData += '-';
                        graphCopy[iter][rootIter] = 0;
                    } else {
                        isDigGrah = 1;
                        objData += '>';
                    }
                    objData +=  " ";
                    objData += std::to_string(iter + 1);
                    graphCopy[rootIter][iter] = 0;
                }
            }
            if (isStrStarted)
                objData += ";\n";
        }
        if(isDigGrah)
            newFile << "di";
        newFile << "graph ";
        newFile << objData;
        newFile << "}";
        newFile.close();
    } else 
        throw Graph::unvalidFile();
}

int Graph::getPath(int from, int to){
    if(from < 1 || from > this->len || to < 1 || to > this->len)
        throw Graph::unkownRoot();
    return this->dataArr[from - 1][to - 1];
}

int Graph::length(){
    return this->len;
}

const std::vector<int> Graph::getAllLinks(int root) const{
    if(root < 1 || root  > this->len)
        throw Graph::unkownRoot();
    return this->links[root - 1];
}

const char * Graph::unvalidFile::what() const throw() {
    return "there is an error in your file\n";
}


const char * Graph::unkownRoot::what() const throw() {
    return "there is not such root\n";
}