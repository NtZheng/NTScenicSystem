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

// public

void ListUDG::creatGraph() {
    auto& tempAllVertexes = *this->allVertexes;
    // 用于读取资源
    char tempNumber[16];
    char tempString[128];
    
    ifstream in("/Users/Nineteen/Documents/SourceTree/NTScenicSystem/NTScenicSystem/info.txt");
    
    // 读取顶点和边的数量
    memset(tempNumber, '\0', 16);// 清空数组内容,达到复用效果
    in.getline(tempNumber, 16, ' ');
    this->vertexNumber = atoi(tempNumber);
    
    memset(tempNumber, '\0', 16);
    in.getline(tempNumber, 16, '\n');
    this->edgeNumber = atoi(tempNumber);
    
    cout << "请输入节点个数: " << this->vertexNumber << " 请输入边的条数: " << this->edgeNumber << endl;
    
    cout << "请输入节点的信息: " << endl;
    
    // 读取每个节点的信息
    for (unsigned i = 0; i < this->vertexNumber; i++) {
        // 分别读取一行中的三个部分
        memset(tempString, '\0', 128);
        in.getline(tempString, 128, ' ');
        string name(tempString);
        cout << name << ' ';
        memset(tempNumber, '\0', 16);
        in.getline(tempNumber, 16, ' ');
        unsigned welcomeStar = atoi(tempNumber);
        memset(tempString, '\0', 128);
        in.getline(tempString, 128);
        string introduction(tempString);
        
        // 将这一个节点存入到allVertexes中
        tempAllVertexes[name] = make_shared<Vertex>(name, i, welcomeStar, introduction);
        // 将节点名字存入到vertexNames中
        vertexNames->push_back(name);
    }
    
    cout << endl << endl;
    
    cout << "请输入边的信息: " << endl;
    
    // 读取每条边的信息
    for (int i = 0; i < this->edgeNumber; i++) {
        // 分别读取一行中的三个部分
        memset(tempString, 128, '\0');
        in.getline(tempString, 128, ' ');
        string from(tempString);
        cout << from << ' ';
        memset(tempString, 128, '\0');
        in.getline(tempString, 128, ' ');
        string to(tempString);
        cout << to << ' ';
        memset(tempNumber, 16, '\0');
        in.getline(tempNumber, 16);
        int distance = atoi(tempNumber);
        cout << distance << endl;
        
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
