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

using namespace std;

class ListUDG {
private:
    shared_ptr<unordered_map<string, shared_ptr<Vertex>>> allVertexes;
};


#endif /* ListUDG_hpp */
