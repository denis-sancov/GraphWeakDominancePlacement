//
//  Node.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Node.hpp"
#include <iostream>

Node::Node(unsigned long id, std::string str_label):identifier(id),label(std::string(str_label)) {

}

void Node::debug() {
    std::cout << "Debug Node with id = " << this->identifier << std::endl;
    
    std::cout << "memory = " << this << std::endl;
    if (out_edges.size() > 0) {
        std::cout << "Out nodes" << std::endl;
        for (edge_ptr_strong edge : out_edges) {
            if (node_ptr_strong spt = edge->to.lock()) {
                std::cout << "node = " << spt->identifier << std::endl;
            }
        }
    }
    if (in_edges.size() > 0) {
        std::cout << "In nodes" << std::endl;
        for (edge_ptr_strong edge : in_edges) {
            if (node_ptr_strong spt = edge->from.lock()) {
                std::cout << "node = " << spt->identifier << std::endl;
            }
        }
    }
    std::cout << std::endl;
}
