//
//  Edge.hpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef Edge_hpp
#define Edge_hpp

#include "defines.h"

class Edge {
    
public:
    node_ptr_weak from, to;
    bool removed;
    Edge(node_ptr_strong from, node_ptr_strong to);
};

#endif /* Edge_hpp */
