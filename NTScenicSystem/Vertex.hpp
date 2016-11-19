//
//  Vertex.hpp
//  NTScenicSystem
//
//  Created by Nineteen on 11/18/16.
//  Copyright © 2016 Nineteen. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "Edge.hpp"

using namespace std;

class Vertex {
private:
    string name;
    unsigned index;
    unsigned welcomeStar;
    string introduction;
    bool isVisited;
    shared_ptr<list<weak_ptr<Edge>>> listAdj;
public:
    // 构造器
    Vertex(string name, unsigned index, unsigned welcomeStar = 0, string introduction = "")
    : name(name), index(index), isVisited(false), introduction(introduction),
		  listAdj(make_shared<list<weak_ptr<Edge>>>()), welcomeStar(welcomeStar) {}
    
    // 添加节点到邻接链表
    void addEdge(const shared_ptr<Edge> edge) {
        this->listAdj->push_back(edge);
    }
};

#endif /* Vertex_hpp */
