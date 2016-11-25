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
    typedef vector<vector<unsigned>> Matrix;
    
    shared_ptr<unordered_map<string, shared_ptr<Vertex>>> allVertexes;
    shared_ptr<vector<shared_ptr<Edge>>> allEdges;
    shared_ptr<Matrix> adjacentMatrix;
    shared_ptr<vector<string>> vertexNames;
    shared_ptr<list<shared_ptr<Vertex>>> tourGuideLine;
    unsigned vertexNumber;
    unsigned edgeNumber;
    
    void adjacentListToAdjacentMatrix(Matrix&);
    bool isGraphEmpth();
    void DFSTraverse(list<shared_ptr<Vertex>>&);
    void topoSort(vector<int>&);
    void shortestPathDijkstra(unsigned, vector<unsigned>&, vector<unsigned>&);
    void outputShortestPath(unsigned, vector<unsigned>&, vector<unsigned>&);
    void quickSort(vector<shared_ptr<Vertex>>&, unsigned, unsigned);
    void insertSort(vector<shared_ptr<Vertex>>&, unsigned, unsigned);
    unsigned partitionForQuickSort(vector<shared_ptr<Vertex>>&, unsigned, unsigned);

public:
    // 构造函数（对allVertexes和allEdges进行初始化）
    ListUDG() : allVertexes(make_shared<unordered_map<string, shared_ptr<Vertex>>>()), allEdges(make_shared<vector<shared_ptr<Edge>>>()), vertexNames(make_shared<vector<string>>()), tourGuideLine(make_shared<list<shared_ptr<Vertex>>>()){}
    
    void creatGraph();
    void outputGraph();
    void outputTourGuideLine();
    void topoSort();
    void miniDistance();
    void outputRoadPlanning();
    void sortedByPopularity();
};


#endif /* ListUDG_hpp */
