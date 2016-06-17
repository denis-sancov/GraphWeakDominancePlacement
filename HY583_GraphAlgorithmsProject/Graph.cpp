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

Graph::Graph(unsigned long nodes_count, unsigned short edge_density) {
//    node_ptr_strong a(new Node(0));
//    node_ptr_strong b(new Node(1));
//    node_ptr_strong c(new Node(2));
//    node_ptr_strong d(new Node(3));
//    node_ptr_strong e(new Node(4));
//    node_ptr_strong f(new Node(5));
//    
//    _nodes.push_back(a);
//    _nodes.push_back(b);
//    _nodes.push_back(c);
//    _nodes.push_back(d);
//    _nodes.push_back(e);
//    _nodes.push_back(f);
//
//    addEdge(a, d);
//    addEdge(a, e);
//    addEdge(b, d);
//    addEdge(b, f);
//    addEdge(c, e);
//    addEdge(c, f);
    
    
    _nodes.reserve(nodes_count);
    for (unsigned int i = 0; i < nodes_count; i++) {
        node_ptr_strong node(new Node(i));
        _nodes.push_back(node);
    }    
    std::random_device rd;
    std::mt19937 rng(rd());
    
    std::vector<unsigned long> tmp;
    unsigned long child_index = 0;
    
    unsigned long edges_count = edge_density * nodes_count;

    unsigned long total_count_of_generated_edges = 0;
    unsigned long edges_per_node = 0;

    
    for (unsigned long i = 0; i < nodes_count - 2; i++) {
        node_ptr_strong parent_node = _nodes[i];
        unsigned long max_range;
        if (edges_count < total_count_of_generated_edges) {
            max_range = 1;
        } else {
            max_range = (edges_count - total_count_of_generated_edges)/9;
        }
        
        std::uniform_int_distribution<unsigned long> edge_uni(1, max_range + 1);

        edges_per_node = edge_uni(rng);
        
        for (unsigned long j = 0; j < edges_per_node;  j++) {
            std::uniform_int_distribution<unsigned long> uni(i+1, nodes_count-1);
            child_index = uni(rng);
            
            unsigned int attempts = 0;
            while(std::find(tmp.begin(), tmp.end(), child_index) != tmp.end() == true) {
                child_index = uni(rng);
                attempts += 1;
                if (attempts > 3) {
                    break;
                }
            }
            if (attempts > 3) {
                break;
            }
            tmp.push_back(child_index);
            node_ptr_strong node = _nodes[child_index];
            
            addEdge(parent_node, node);
        }
        total_count_of_generated_edges += edges_per_node;
        tmp.clear();
    }
}

void Graph::markNodeAsRemoved(node_ptr_strong node) {
    for (edge_ptr_strong edge : node->out_edges) {
        edge->removed = true;
    }
    for (edge_ptr_strong edge : node->in_edges) {
        edge->removed = true;
    }
    node->removed = true;
}

void Graph::addEdge(node_ptr_strong from, node_ptr_strong to) {
    edge_ptr_strong edge(new Edge(from, to));
    from->out_edges.push_back(edge);
    to->in_edges.push_back(edge);
}

void Graph::resetRemoveMarks() {
    for (node_ptr_strong node : _nodes) {
        node->removed = false;
        node->resetRemovedMarks();
    }
}


void Graph::debug() {
    std::cout << "Graph info" << std::endl;
    std::cout << "Nodes count = " << _nodes.size() << std::endl;
    for (node_ptr_strong node : _nodes) {
        node->debug();
    }
}

