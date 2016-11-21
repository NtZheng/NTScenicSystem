//
//  Edge.hpp
//  NTScenicSystem
//
//  Created by Nineteen on 11/18/16.
//  Copyright © 2016 Nineteen. All rights reserved.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>
#include <memory>

using std::shared_ptr;

class Vertex;

class Edge {
private:
    shared_ptr<Vertex> from;
    shared_ptr<Vertex> to;
    unsigned distance;
public:
    Edge(shared_ptr<Vertex> from, shared_ptr<Vertex> to, unsigned distance) : from(from), to(to), distance(distance){}
};

#endif /* Edge_hpp */
