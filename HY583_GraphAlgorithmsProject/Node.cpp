//
//  Node.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Node.hpp"
#include <iostream>

Node::Node(std::string value) {
    this->value = new std::string(value);
}

void Node::debug() {
    std::cout << "Debug Node " << *this->value << std::endl;
    std::cout << "memory = " << this << std::endl;
    if (out_edges.size() > 0) {
        std::cout << "Out nodes" << std::endl;
        for (Edge *edge : out_edges) {
            std::cout << "node = " << edge->to->value << std::endl;
        }
    }
    if (in_edges.size() > 0) {
        std::cout << "In nodes" << std::endl;
        for (Edge *edge : in_edges) {
            std::cout << "node = " << edge->to->value << std::endl;
        }
    }
    std::cout << std::endl;
}