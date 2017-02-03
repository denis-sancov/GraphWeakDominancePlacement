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

using namespace csd;

Graph::Graph() {
  
    auto nodeA = new Node(0, "A");
    auto nodeB = new Node(1, "B");
    auto nodeC = new Node(2, "C");
    auto nodeD = new Node(3, "D");
    auto nodeE = new Node(4, "E");
    auto nodeF = new Node(5, "F");
    auto nodeG = new Node(6, "G");
    auto nodeH = new Node(7, "H");
    auto nodeI = new Node(8, "I");
    auto nodeJ = new Node(9, "J");
    auto nodeK = new Node(10, "K");

    
    _nodes.push_back(nodeA);
    _nodes.push_back(nodeB);
    _nodes.push_back(nodeC);
    _nodes.push_back(nodeD);

    _nodes.push_back(nodeE);
    _nodes.push_back(nodeF);
    _nodes.push_back(nodeG);
    _nodes.push_back(nodeH);
    _nodes.push_back(nodeI);
    _nodes.push_back(nodeJ);
    _nodes.push_back(nodeK);


    
    
    prepareTransitiveClosureMatrix();
 
    
    
    
    
    addEdge(nodeA, nodeB);
    addEdge(nodeA, nodeC);
    addEdge(nodeA, nodeD);


    addEdge(nodeB, nodeE);
    addEdge(nodeB, nodeF);
    

    addEdge(nodeC, nodeF);
    addEdge(nodeC, nodeG);

    addEdge(nodeD, nodeG);
    
    addEdge(nodeE, nodeH);
    addEdge(nodeE, nodeI);

    
    addEdge(nodeF, nodeI);
    
    addEdge(nodeG, nodeJ);
    addEdge(nodeG, nodeI);

    addEdge(nodeH, nodeK);
    addEdge(nodeI, nodeK);
    addEdge(nodeJ, nodeK);


    
    auto size = _nodes.size();
    
    for (int k = 0; k < size; ++k)
        for (int i = 0; i < size; ++i)
            if (_transitive_closure_matrix[i][k] == 1)
                for (int j = 0; j < size; ++j)
                    _transitive_closure_matrix[i][j] = _transitive_closure_matrix[i][j] || _transitive_closure_matrix[k][j];
    
    
}

Graph::Graph(unsigned long nodes_count, double edge_density) {
    _nodes.reserve(nodes_count);
    for (unsigned int i = 0; i < nodes_count; ++i) {
        _nodes.push_back(new Node(i));
    }
    prepareTransitiveClosureMatrix();

    std::random_device rd;
    std::mt19937 rng(rd());
    
    std::vector<unsigned long> tmp;
    unsigned long child_index = 0;
    
    auto edges_count = (unsigned long)(edge_density * nodes_count);

    unsigned long total_count_of_generated_edges = 0;
    unsigned long edges_per_node = 0;

    
    for (unsigned long i = 0; i < nodes_count - 2; ++i) {
        auto parent_node = _nodes[i];
        
        unsigned long max_range;
        if (edges_count < total_count_of_generated_edges) {
            max_range = 1;
        } else {
            max_range = (edges_count - total_count_of_generated_edges)/2;
        }
        
        std::uniform_int_distribution<unsigned long> edge_uni(1, max_range + 1);

        edges_per_node = edge_uni(rng);
        
        for (unsigned long j = 0; j < edges_per_node;  ++j) {
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
            
            addEdge(parent_node, _nodes[child_index]);
        }
        total_count_of_generated_edges += edges_per_node;
        tmp.clear();
    }

    auto size = _nodes.size();
    
    for (int k = 0; k < size; ++k)
        for (int i = 0; i < size; ++i)
            if (_transitive_closure_matrix[i][k] == 1)
                for (int j = 0; j < size; ++j)
                    _transitive_closure_matrix[i][j] = _transitive_closure_matrix[i][j] || _transitive_closure_matrix[k][j];
    
    
    std::cout << "nodes = " << _nodes.size() << std::endl;
}

void Graph::prepareTransitiveClosureMatrix() {
    auto tmp = _nodes.size();
    _transitive_closure_matrix = new bool*[tmp];
    for (unsigned long i = 0; i < tmp; ++i) {
        _transitive_closure_matrix[i] = new bool[tmp];
        for (unsigned long j = 0; j < tmp; ++j) {
            _transitive_closure_matrix[i][j] = 0;
        }
    }
}

void Graph::addEdge(Node *from, Node *to) {
    from->addEdgeTo(to);
    _transitive_closure_matrix[from->getID()][to->getID()] = true;
}

unsigned long Graph::getNodesCount() const {
    return _nodes.size();
}

std::vector<Node *> Graph::zeroInNodes() const {
    std::vector<Node *> result;
    std::copy_if(_nodes.begin(), _nodes.end(), std::back_inserter(result), [](const Node *node) {
        return (node->getInDegree() == 0 && (!node->isRemoved()));
    });
    return result;
}

std::vector<Node *> Graph::getNodes() const {
    return _nodes;
}

bool Graph::hasPath(Node *from, Node *to) const {
    return _transitive_closure_matrix[from->getID()][to->getID()];
}

void Graph::resetRemoveMarks() const{
    for (auto node : _nodes) {
        node->markAsRemoved(false);
    }
}

std::ostream& csd::operator<<(std::ostream& os, const Graph& graph) {
    os << "Graph info" << std::endl;
    
    os << "Nodes count = " << graph._nodes.size() << std::endl;
    for (auto node : graph._nodes) {
        os << *node;
    }

    os << "Transitive closure matrix" << std::endl;
    for (auto i = 0; i < graph._nodes.size(); ++i) {
        for (auto j = 0; j < graph._nodes.size(); ++j) {
            os << "From [" << i << "][" << j << "] path = "
               << graph._transitive_closure_matrix[i][j] << std::endl;
        }
    }

    return os;
}


Graph::~Graph() {
    for (unsigned long i = 0; i < _nodes.size(); i++) {
        delete[] _transitive_closure_matrix[i];
    }
    delete[] _transitive_closure_matrix;
    
    for (Node *node : _nodes) {
        delete node;
    }
    _nodes.clear();
}

