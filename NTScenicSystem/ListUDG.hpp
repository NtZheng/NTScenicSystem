//
//  ListUDG.hpp
//  NTScenicSystem
//
//  Created by Nineteen on 11/18/16.
//  Copyright © 2016 Nineteen. All rights reserved.
//

#ifndef ListUDG_hpp
#define ListUDG_hpp

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

#include "Vertex.hpp"
#include "Edge.hpp"

using namespace std;

class ListUDG {
private:
    shared_ptr<unordered_map<string, shared_ptr<Vertex>>> allVertexes;
    shared_ptr<vector<shared_ptr<Edge>>> allEdges;
    unsigned vertexNumber;
    unsigned edgeNumber;
    
public:
    // 构造函数（对allVertexes河allEdges进行初始化）
    ListUDG() : allVertexes(make_shared<unordered_map<string, shared_ptr<Vertex>>>()), allEdges(make_shared<vector<shared_ptr<Edge>>>()){}
    
    void creatGraph();
};


#endif /* ListUDG_hpp */
