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
#include <unordered_map>

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
    }
    in.close();
    cout << endl<<"创建景点图成功！请继续选择操作:" << endl;
}
