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
    cout << endl << endl << "成功输出图的邻接矩阵！请继续选择操作"<< endl;
    
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
            return;
        }
    }
    cout << "图中没有回路" << endl;
}

// private

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
