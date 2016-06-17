//
//  Edge.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Edge.hpp"
#include "Node.hpp"

Edge::Edge(node_ptr_strong from, node_ptr_strong to) {
    this->removed = false;
    this->from = from;
    this->to = to;
}