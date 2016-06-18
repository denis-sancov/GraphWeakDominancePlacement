//
//  Edge.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Edge.hpp"
#include "Node.hpp"

Edge::Edge(node_ptr_strong from_node, node_ptr_strong to_node) {
    this->removed = false;
    this->from = from_node;
    this->to = to_node;
}