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
    
    cout << "请输入节点的信息: " << endl << endl;
    
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
    
    cout << endl << endl;
    
    cout << "请输入边的信息: " << endl << endl;
    
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
    for (string tempString : tempVertexNames) {
        printf("%8s", tempString.c_str());
    }
    cout << endl;
    
    for (size_t j = 0; j < size; j++) {
        printf("%8s", tempVertexNames[j].c_str());
        for (size_t k = 0; k < size; k++) {
            printf("%8d", tempAdjacentMatrix[j][k]);
        }
        cout << endl;
    }
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

// private

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
        auto firstVertex = tempListAdj->begin();
        auto lastVertex = tempListAdj->end();
        
        // 遍历节点的每一条边
        while (firstVertex != lastVertex) {
            if (!(*firstVertex).lock()->getToVertex()->visited()) {
                currentVertex = (*firstVertex).lock()->getToVertex();
                currentVertex->setVisited(true);
                stackVertexes.push(currentVertex);
                tempTourGuideLine.push_back(currentVertex);
                
                if (++count >= allVertexes->size()) {
                    return;
                }
                
                break;
                
            } else {
                ++firstVertex; // 迭代器迭代
            }
        }
        
        if (firstVertex == lastVertex) {
            stackVertexes.pop();
            if (!stackVertexes.empty()) {
                tempTourGuideLine.push_back(stackVertexes.top());
            }
        }
    }
    
}
