//
//  Graph.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Graph.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include "NodeLevel.hpp"
#include "GraphAlgorithms.hpp"

Graph::Graph(unsigned long nodes_count) {
//    Node *a = new Node("A");
//    Node *b = new Node("B");
//    Node *c = new Node("C");
//    Node *d = new Node("D");
//    Node *e = new Node("E");
//    Node *f = new Node("F");
//    Node *g = new Node("G");
//    Node *h = new Node("H");
//    Node *i = new Node("I");
//    Node *j = new Node("J");
//    Node *k = new Node("K");
//
//    this->addEdge(a, b);
//
//    
//    this->addEdge(a, c);
//    this->addEdge(a, d);
//    
//    this->addEdge(b, e);
//    this->addEdge(b, f);
//    this->addEdge(e, h);
//    this->addEdge(e, i);
//
//    this->addEdge(h, k);
//    this->addEdge(c, f);
//    this->addEdge(f, i);
//    this->addEdge(i, k);
//    this->addEdge(c, g);
//    this->addEdge(d, g);
//    this->addEdge(g, i);
//    this->addEdge(g, j);
//    this->addEdge(j, k);
//    
//    _nodes.push_back(a);
//    _nodes.push_back(b);
//    _nodes.push_back(c);
//    _nodes.push_back(d);
//    _nodes.push_back(e);
//    _nodes.push_back(f);
//    _nodes.push_back(g);
//    _nodes.push_back(h);
//    _nodes.push_back(i);
//    _nodes.push_back(j);
//    _nodes.push_back(k);

    
        Node *a = new Node("A");
        Node *b = new Node("B");
        Node *c = new Node("C");
        Node *d = new Node("D");
        Node *e = new Node("E");
        Node *f = new Node("F");
    
    
        this->addEdge(a, d);
        this->addEdge(a, e);
    
        this->addEdge(b, d);
        this->addEdge(b, f);
    
        this->addEdge(c, e);
        this->addEdge(c, f);
    
    
    
        _nodes.push_back(c);
        _nodes.push_back(d);
        _nodes.push_back(e);
        _nodes.push_back(f);
        _nodes.push_back(a);
        _nodes.push_back(b);
    
    
//    std::vector<NodeLevel> levels;
//    
//    std::random_device rd;
//    std::mt19937 rng(rd());
//    
//    unsigned long count_total_generated_nodes = 0;
//    unsigned long nodes_count_per_level = 0;
//    unsigned long level = 0;
//    unsigned long max_range = sqrt(nodes_count);
//    std::cout << "progress:" << std::endl;
//    while (count_total_generated_nodes < nodes_count) {
//        std::uniform_int_distribution<unsigned long> uni(0, max_range);
//        nodes_count_per_level = uni(rng);
//        if (nodes_count_per_level == 0) {
//            continue;
//        }
//        NodeLevel node_level = NodeLevel(level, nodes_count_per_level);
//        levels.push_back(node_level);
//        if (level > 0) {
//            std::uniform_int_distribution<unsigned long> uni(0, level-1);
//            NodeLevel parent_level = levels.at(uni(rng));
//            parent_level.add_edges_to_level(&node_level);
//        }
//        count_total_generated_nodes += nodes_count_per_level;
//        level += 1;
//        std::cout << ((float)count_total_generated_nodes / nodes_count) * 100 << "%" << std::endl;
//    }
//    
//    std::cout << "Reserving memory for " << nodes_count << " nodes" << std::endl;
//    _nodes.reserve(nodes_count);
//    for (NodeLevel level : levels) {
//        _nodes.insert(_nodes.end(), level.nodes.begin(), level.nodes.end());
//        level.nodes.clear();
//    }
//    levels.clear();
}

void Graph::markNodeAsRemoved(Node *node) {
    for (Edge *edge : node->out_edges) {
        edge->removed = true;
    }
    for (Edge *edge : node->in_edges) {
        edge->removed = true;
    }
    node->removed = true;
}

void Graph::addEdge(Node *from, Node *to) {
    Edge *edge = new Edge(from, to);
    from->out_edges.push_back(edge);
    to->in_edges.push_back(edge);
}

void Graph::resetRemoveMarks() {
    for (Node *node : _nodes) {
        node->removed = false;
        node->resetRemovedMarks();
    }
}


void Graph::debug() {
    std::cout << "Graph info" << std::endl;
    std::cout << "Nodes count = " << _nodes.size() << std::endl;
    for (Node *node : _nodes) {
         node->debug();
    }
}
