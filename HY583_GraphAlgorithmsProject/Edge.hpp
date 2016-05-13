//
//  Edge.hpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov on 11.05.16.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>

class Node;

class Edge {

public:
    Node *from, *to;
    bool removed;
    Edge(Node *from, Node *to);
};

#endif /* Edge_hpp */
