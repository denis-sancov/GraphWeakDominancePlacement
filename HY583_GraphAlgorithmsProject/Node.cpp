//
//  Node.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Node.hpp"
#include <iostream>

Node::Node(unsigned int node_value) {
    this->value = node_value;
}

void Node::debug() {
    std::cout << "Debug Node " << this->value << std::endl;
    std::cout << "memory = " << this << std::endl;
    if (out_edges.size() > 0) {
        std::cout << "Out nodes" << std::endl;
        for (edge_ptr_strong edge : out_edges) {
            if (node_ptr_strong spt = edge->to.lock()) {
                std::cout << "node = " << spt->value << std::endl;
            }
        }
    }
    if (in_edges.size() > 0) {
        std::cout << "In nodes" << std::endl;
        for (edge_ptr_strong edge : in_edges) {
            if (node_ptr_strong spt = edge->from.lock()) {
                std::cout << "node = " << spt->value << std::endl;
            }
        }
    }
    std::cout << std::endl;
}
