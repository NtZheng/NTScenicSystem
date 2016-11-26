//
//  ListUDG.cpp
//  NTScenicSystem
//
//  Created by Nineteen on 11/18/16.
//  Copyright © 2016 Nineteen. All rights reserved.
//

#include "ListUDG.hpp"

#include <fstream>
#include <iostream>
#include <stack>

// public

void ListUDG::creatGraph() {
    
    auto& tempAllVertexes = *this->allVertexes;

    ifstream in("/Users/Nineteen/Documents/SourceTree/NTScenicSystem/NTScenicSystem/test.txt");
    
    in >> this->vertexNumber >> this->edgeNumber;
    
    // 读取顶点和边的数量
    
    cout << "请输入节点个数: " << this->vertexNumber << " 请输入边的条数: " << this->edgeNumber << endl;
    
    cout << "请输入节点的信息: " << endl;
    
    string name;
    unsigned welcomeStar;
    string introduction;
    
    // 读取每个节点的信息
    for (unsigned i = 0; i < this->vertexNumber; i++) {
        // 分别读取一行中的三个部分
        
        in >> name >> welcomeStar >> introduction;
        
        cout << name << "  ";
        
        // 将这一个节点存入到allVertexes中
        tempAllVertexes[name] = make_shared<Vertex>(name, i, welcomeStar, introduction);
        // 将节点名字存入到vertexNames中
        vertexNames->push_back(name);
    }
    
    cout << endl;
    
    cout << "请输入边的信息: " << endl;
    
    // 分别读取一行中的三个部分
    string from;
    string to;
    int distance;
    
    // 读取每条边的信息
    for (int i = 0; i < this->edgeNumber; i++) {
        
        in >> from >> to >> distance;
        
        cout << from << "  " << to << "  " << distance << endl;
        
        // 将定点与边建立联系
        shared_ptr<Vertex> fromVertex = tempAllVertexes[from];
        shared_ptr<Vertex> toVertex = tempAllVertexes[to];
        shared_ptr<Edge> fromVertexEdge = make_shared<Edge>(fromVertex, toVertex, distance);
        shared_ptr<Edge> toVertexEdge = make_shared<Edge>(toVertex, fromVertex, distance);
        fromVertex->addEdge(fromVertexEdge);
        toVertex->addEdge(toVertexEdge);
        
        // 将边存入到allEdges中
        this->allEdges->push_back(fromVertexEdge);
        this->allEdges->push_back(toVertexEdge);
    }
    in.close();
    cout << endl<<"创建景点图成功！请继续选择操作:" << endl;
}

void ListUDG::outputGraph() {
    if (this->isGraphEmpth()) {
        return;
    }
    this->adjacentMatrix = make_shared<Matrix>(vertexNumber + 1, vector<unsigned>(vertexNumber + 1, 32767));
    auto& tempAdjacentMatrix = *adjacentMatrix;
    this->adjacentListToAdjacentMatrix(tempAdjacentMatrix);
    auto& tempVertexNames = *vertexNames;
    auto size = allVertexes->size();
    
    // 打印输出
    printf("%8s","");
    for (int i = 0; i < size; i++) {
        printf("%8s   ",tempVertexNames[i].c_str());
    }
    cout << endl;
    
    for (size_t j = 0; j < size; j++) {
        printf("%8s", tempVertexNames[j].c_str());
        for (size_t k = 0; k < size; k++) {
            printf("%8d", tempAdjacentMatrix[j][k]);
        }
        cout << endl;
    }
    cout << endl << "成功输出图的邻接矩阵！请继续选择操作"<< endl;
    
}

void ListUDG::outputTourGuideLine() {
    if (this->isGraphEmpth()) {
        return;
    }
    auto& tempTourGuideLine = *this->tourGuideLine;
    this->DFSTraverse(tempTourGuideLine);
    auto firstSpot = tempTourGuideLine.begin();
    auto lastSpot = tempTourGuideLine.end();
    cout << (*firstSpot)->getName();
    while (++firstSpot != lastSpot) {
        cout << "->" << (*firstSpot)->getName();
    }
    cout << endl;
    cout << endl << "成功输出导游路线图！请继续选择操作"<< endl;
}

void ListUDG::topoSort() {
    if (isGraphEmpth()) {
        return;
    }
    if (this->tourGuideLine->empty()) {
        DFSTraverse(*this->tourGuideLine);
    }
    vector<int> result(this->vertexNumber);
    topoSort(result);
    for (unsigned i = 0; i < this->vertexNumber; i++) {
        if (result[i] > 0) {
            cout << "图中有回路" << endl;
            
            auto& tempVertexNames = *this->vertexNames;
            for (unsigned j = i; j < this->vertexNumber; j++) {
                if (result[j] > 0) {
                    cout << tempVertexNames[j] << " ";
                }
            }
            cout << endl;
            cout << endl << "请继续选择操作："<< endl;
            return;
        }
    }
    cout << "图中没有回路" << endl;
    cout << endl << "请继续选择操作："<< endl;
}

void ListUDG::miniDistance() {
    if (isGraphEmpth()) {
        return;
    }
    cout << "请输入要查询的两个景点的名称：";
    string from, to;
    cin >> from >> to;
    if (from == to) {
        cout << from << "->" << to << endl;
        cout << "最短路径：" << 0 << endl;
        return;
    }
    unsigned int startIndex = this->allVertexes->at(from)->getIndex();
    unsigned int endIndex = this->allVertexes->at(to)->getIndex();
    vector<unsigned int> shortestPathTable(this->vertexNumber);
    vector<unsigned int> path(this->vertexNumber);
    shortestPathDijkstra(startIndex, path, shortestPathTable);
    outputShortestPath(endIndex, path, shortestPathTable);
}

void ListUDG::outputRoadPlanning() {
    vector<unsigned> newVertexes(this->vertexNumber, 0);
    vector<shared_ptr<Edge>> newEdgeSet;
    auto& tempAllVertexes = *this->allVertexes;
    auto& tempVertexNames = *this->vertexNames;
    unsigned count = 0;
    newVertexes[0] = 1; // 将第一个点标记为已经构建路线
    while (++count < this->vertexNumber) {
        unsigned index, distance = 32767;
        shared_ptr<Edge> minPowerEdge = nullptr;
        for (int i = 0; i < this->vertexNumber; i++) {
            if (newVertexes[i] == 1){
                auto& tempListAdj = *tempAllVertexes[tempVertexNames[i]]->getListAdj();
                for (weak_ptr<Edge> edge : tempListAdj) {
                    index = edge.lock()->getToVertex()->getIndex();
                    if (newVertexes[index] == 0 && edge.lock()->getDistance() < distance) {
                        distance = edge.lock()->getDistance();
                        minPowerEdge = edge.lock();
                    }
                }
            }
        }
        newVertexes[minPowerEdge->getToVertex()->getIndex()] = 1;
        newEdgeSet.push_back(minPowerEdge);
    }
    
    for (shared_ptr<Edge> edge : newEdgeSet) {
        cout << "从" << edge->getFromVertex()->getName() << "到" << edge->getToVertex()->getName() << "修一条路" << endl;
    }
    
    cout << endl << "请继续选择操作:" << endl;
}

void ListUDG::sortedByPopularity() {
    vector<shared_ptr<Vertex>> sortedVertexes;
    // from和to均代表了序号
    unsigned from = 0;
    unsigned to = 3;
    if (to - from < 4) {
        int count = 0;
        for (auto& vertex : *this->allVertexes) {
            if (count++ < to - from + 1) {
                sortedVertexes.push_back(vertex.second);
            } else {
                break;
            }
        }
    } else {
        for (auto& vertex : *this->allVertexes) {
            sortedVertexes.push_back(vertex.second);
        }
    }
    quickSort(sortedVertexes, from, to);
    for_each(sortedVertexes.begin(), sortedVertexes.end(), [](shared_ptr<Vertex> vertex) {
        cout << vertex->getName() << " " << vertex->getWelcomeStar() << endl;
    });
    cout << endl << "请继续选择操作:" << endl;
}

void ListUDG::searchWithKeyWords() {
    if (isGraphEmpth()) {
        return;
    }
    cout << "请输入你要查找的关键字：" << endl;
    string key;
    cin >> key;
    vector<shared_ptr<Vertex>> resultVertexes;
    queryWords(key, resultVertexes);
    if (resultVertexes.empty()) {
        cout << "没有与" << key << "相关的内容" << endl;
        cout << endl << "请继续选择操作：" << endl;
        return;
    }
    cout << "含有相关信息的有：" << endl;
    for (shared_ptr<Vertex> vertex : resultVertexes) {
        cout << "景点：" << vertex->getName() << endl;
        cout << "景点介绍：" << vertex->getIntroduction() << endl;
    }
    cout << endl << "请继续选择操作：" << endl;
}

void ListUDG::parkingLotManagement() {
    this->parkingLot->management();
}

// private

void ListUDG::queryWords(const string& key, vector<shared_ptr<Vertex>>& resultVertexes) {
    for (auto& vertex : *this->allVertexes) {
        const string& name = vertex.first;
        const string& introduction = vertex.second->getIntroduction();
        if (KMP(key, name) || KMP(key, introduction)) {
            resultVertexes.push_back(vertex.second);
        }
    }
}

bool ListUDG::KMP(const string& target, const string& content) {
    unsigned targetLength = (unsigned)target.size();
    unsigned contentLength = (unsigned)content.size();
    if (targetLength > contentLength) {
        return false;
    }
    vector<int> vi;
    computePrefixFunction(vi, target);
    int q = -1;
    for (unsigned i = 0; i < contentLength; i++) {
        while (q > -1 && target[q + 1] != content[i]) {
            q = vi[q];
        }
        if (target[q + 1] == content[i]) {
            ++q;
        }
        if (q == targetLength - 1) {
            return true;
        }
    }
    return false;
}

void ListUDG::computePrefixFunction(vector<int>& vi, const string& str) {
    vi.resize(str.size());
    unsigned m = (unsigned)str.size();
    vi[0] = -1;
    int k = -1;
    for (unsigned q = 1; q < m; ++q) {
        while (k >= 0 && str[k + 1] != str[q])
            k = vi[k];
        if (str[k + 1] == str[q])
            ++k;
        vi[q] = k;
    }
}

void ListUDG::quickSort(vector<shared_ptr<Vertex>>& vertexes, unsigned from, unsigned to) {
    if (to - from < 4) {
        insertSort(vertexes, from, to);
        return;
    }
    unsigned flagIndex;
    if (from < to) {
        flagIndex = this->partitionForQuickSort(vertexes, from, to);
        this->quickSort(vertexes, from, flagIndex - 1);
        this->quickSort(vertexes, flagIndex + 1, to);
    }
}

unsigned ListUDG::partitionForQuickSort(vector<shared_ptr<Vertex>>& vertexes, unsigned left, unsigned right) {
    shared_ptr<Vertex> mark = vertexes[left];
    unsigned flag = mark->getWelcomeStar();
    while (left < right) { // 依次往中间收缩
        while (left < right && vertexes[right]->getWelcomeStar() >= flag) { // 右边的收缩
            right--;
        }
        if (left < right) {
            vertexes[left++] = vertexes[right];
        }
        while (left < right && vertexes[left]->getWelcomeStar() <= flag) { // 左边的收缩
            left++;
        }
        if (left < right) {
            vertexes[right--] = vertexes[left];
        }
    }
    vertexes[left] = mark;
    return left;
}

void ListUDG::insertSort(vector<shared_ptr<Vertex>>& vertexes, unsigned from, unsigned to) {
    if (to - from <= 1) {
        return;
    }
    for (unsigned i = from + 1; i < to + 1; i++) {
        for (unsigned j = i; j > from && vertexes[j - 1]->getWelcomeStar() > vertexes[j]->getWelcomeStar(); j--) {
            swap(vertexes[j-1], vertexes[j]);
        }
    }
}

void ListUDG::shortestPathDijkstra(unsigned startIndex, vector<unsigned>& path, vector<unsigned> & shortestPathTable) {
    this->adjacentMatrix = make_shared<Matrix>(this->vertexNumber, vector<unsigned>(this->vertexNumber ,32767));
    this->adjacentListToAdjacentMatrix(*this->adjacentMatrix);
    auto& tempMatrix = *this->adjacentMatrix;
    unsigned i, j;
    unsigned confirmedIndex = 0;
    unsigned minDistance;
    unsigned vertexNumber = this->vertexNumber;
    
    // 初始化操作
    vector<int> final(vertexNumber);
    for (i = 0; i < vertexNumber; i++) {
        final[i] = 0;
        shortestPathTable[i] = tempMatrix[startIndex][i];
        path[i] = startIndex;
    }
    final[startIndex] = 1;
    path[startIndex] = -1;
    
    // 主循环
    for (i = 0; i < vertexNumber; i++) {
        minDistance = 32767;
        for (j = 0; j < vertexNumber; j++) {
            if (!final[j] && shortestPathTable[j] < minDistance) {
                confirmedIndex = j;
                minDistance = shortestPathTable[j];
            }
        }
        final[confirmedIndex] = 1;
        for (j = 0; j < vertexNumber; j++) {
            if (!final[j] && (minDistance + tempMatrix[confirmedIndex][j]) < shortestPathTable[j]) {
                shortestPathTable[j] = minDistance + tempMatrix[confirmedIndex][j];
                path[j] = confirmedIndex;
            }
        }
    }
}

void ListUDG::outputShortestPath(unsigned endIndex, vector<unsigned>& path, vector<unsigned>& shortestPathTable) {
    vector<unsigned int> result;
    auto& tempVertexNames = *this->vertexNames;
    unsigned int i = endIndex;
    // 从endIndex位置切断，保存前面的数组到result中（逆序保存）
    do {
        result.push_back(i);
        i = path[i];
    } while (i != -1);
    
    // 逆序打印
    i = (unsigned int)(result.size() - 1);
    while (i > 0) {
        cout << tempVertexNames[result[i]] << "->";
        i--;
        cout << tempVertexNames[result[i]] << endl;
    }
    cout << "最短距离：" << shortestPathTable[endIndex] << endl;
    cout << endl << "请继续选择操作：" << endl;
}

void ListUDG::topoSort(vector<int>& result) {
    shared_ptr<Matrix> matrix = make_shared<Matrix>(this->vertexNumber, vector<unsigned>(this->vertexNumber, 0)); // 存储连接关系的矩阵
    shared_ptr<vector<int>> inDegree = make_shared<vector<int>>(this->vertexNumber, 0); // 存储入度
    
    auto& tempMatrix = *matrix;
    auto& tempInDegree = *inDegree;
    auto begin = this->tourGuideLine->begin();
    auto after = begin;
    auto end = this->tourGuideLine->end();
    unsigned startIndex = (*begin)->getIndex();
    while (++after != end) {
        unsigned from = (*begin++)->getIndex();
        unsigned in = (*after)->getIndex();
        ++tempMatrix[from][in]; // 保存连接关系
        ++tempInDegree[in]; // 保存入度
    }
    
    // 特殊代码（由于这个景点图中的每个顶点都入度不为1，所以需要事先处理一个顶点）
    tempInDegree[startIndex] = -1;
    for (unsigned i = 0; i < this->vertexNumber; i++) {
        if (tempMatrix[startIndex][i] == 1) {
            --tempInDegree[i];
        }
        tempMatrix[i][startIndex] = 0;
    }

    for (unsigned j = 0; j < this->vertexNumber; j++) {
        if (tempInDegree[j] == 0) {
            tempInDegree[j]--;
            for (unsigned k = 0; k < this->vertexNumber; k++) {
                if (tempMatrix[j][k] == 1) {
                    tempInDegree[k]--;
                }
            }
        }
    }
    result = tempInDegree;
}

void ListUDG::adjacentListToAdjacentMatrix(Matrix& tempMatrix) {
    for (shared_ptr<Edge> tempEdge : *this->allEdges) {
        unsigned int fromIndex = tempEdge->getFromVertex()->getIndex();
        unsigned int toIndex = tempEdge->getToVertex()->getIndex();
        tempMatrix[fromIndex][toIndex] = tempEdge->getDistance();
        tempMatrix[fromIndex][fromIndex] = 0;
    }
}

bool ListUDG::isGraphEmpth() {
    if (!this->allVertexes->empty()) {
        return false;
    } else {
        cout << "您还没有创建图，请输入菜单选项“1”进行创建" << "请重新进行输入: " << endl;
        return true;
    }
}

void ListUDG::DFSTraverse(list<shared_ptr<Vertex>>& tempTourGuideLine) {
    stack<shared_ptr<Vertex>> stackVertexes; // 使用栈存储路线节点
    size_t count = 1; // 目前已经遍历的节点数量
    shared_ptr<Vertex> currentVertex = (*this->allVertexes)[(*this->vertexNames)[0]]; // 将定点集中的第一个节点作为导游图的起始点
    currentVertex->setVisited(true);
    stackVertexes.push(currentVertex);
    tempTourGuideLine.push_back(currentVertex);
    
    while (!stackVertexes.empty()) {
        const shared_ptr<list<weak_ptr<Edge>>> tempListAdj = stackVertexes.top()->getListAdj();
        auto firstEdge = tempListAdj->begin();
        auto lastEdge = tempListAdj->end();
        
        // 遍历节点的每一条边
        while (firstEdge != lastEdge) {
            if (!(*firstEdge).lock()->getToVertex()->visited()) {
                currentVertex = (*firstEdge).lock()->getToVertex();
                currentVertex->setVisited(true);
                stackVertexes.push(currentVertex);
                tempTourGuideLine.push_back(currentVertex);
                
                // 防止回路一直绕
                if (++count >= allVertexes->size()) {
                    return;
                }
                
                // 深度遍历，需要一直往下遍历
                break;
                
            } else {
                ++firstEdge; // 迭代器迭代
            }
        }
        
        // 某一层遍历结束的临界条件
        if (firstEdge == lastEdge) {
            stackVertexes.pop();
            if (!stackVertexes.empty()) {
                tempTourGuideLine.push_back(stackVertexes.top());
            }
        }
    }
    // 恢复所有节点的访问状态
    for (auto& tempVertex : *allVertexes) {
        tempVertex.second->setVisited(false);
    }
}
