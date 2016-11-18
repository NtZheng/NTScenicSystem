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

void ListUDG::creatGraph() {
    auto &tempAllVertexes = *this->allVertexes;
    // 用于读取资源
    char tempNumber[16];
    char tempString[128];
    
    ifstream in("info.txt");
    
    // 读取顶点和边的数量
    memset(tempNumber, '\0', 16);// 清空数组内容,达到复用效果
    in.getline(tempNumber, 16, ' ');
    this->vertexNumber = atoi(tempNumber);
    
    memset(tempNumber, '\0', 16);
    in.getline(tempNumber, 16, '\n');
    this->edgeNumber = atoi(tempNumber);
    
    cout << "请输入节点个数: " << this->vertexNumber << "请输入边的条数: " << this->edgeNumber << endl;
    
    // 读取每个节点的信息
    for (int i = 0; i < this->vertexNumber; i++) {
        // 分别读取一行中的三个部分
        memset(tempString, 128, '\0');
        in.getline(tempString, 128, ' ');
        string name(tempString);
        memset(tempNumber, 16, '\0');
        in.getline(tempNumber, 16, ' ');
        int welcomeStar = atoi(tempNumber);
        memset(tempString, 128, '\0');
        in.getline(tempString, 128, '\n');
        string information(tempString);
        
        // 将这一个节点存入到allVertexes中
        
        
        
    }
    
    
}
