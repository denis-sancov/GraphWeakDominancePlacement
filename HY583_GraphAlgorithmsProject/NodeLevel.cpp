//
//  NodeLevel.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov on 03.05.16.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "NodeLevel.hpp"
#include <string>
#include <random>
#include <iostream>

NodeLevel::NodeLevel(unsigned long level,unsigned long nodes_count) {
    nodes.reserve(nodes_count);
    std::string tmp;
    tmp.reserve(std::to_string(nodes_count).length() + 2);
    for (unsigned long i = 0; i < nodes_count; i++) {
        tmp = std::to_string(level).append("_").append(std::to_string(i));
        Node *node = new Node(tmp);
        nodes.push_back(node);
    }
}

void NodeLevel::add_edges_to_level(const NodeLevel *level) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<unsigned long> uni(0, level->nodes.size()-1);
    for (Node *from : nodes) {
        Node *to = level->nodes.at(uni(rng));
        Edge *edge = new Edge(from, to);
        from->out_edges.push_back(edge);
        to->in_edges.push_back(edge);

    }
}