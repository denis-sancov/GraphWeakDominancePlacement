//
//  Graph.hpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include "Node.hpp"

class Graph {
    std::vector<Node *> _nodes;
public:
    Graph(unsigned long nodes_count);
//    Graph(const Graph& graph) {
//        _nodes.reserve(graph._nodes.size());
//        for (Node *node : graph._nodes) {
//             Node *node_copy = new Node(*node);
//            _nodes.push_back(node_copy);
//        }
//    }
    const std::vector<Node *> nodes() {
        return _nodes;
    }
    
    void addEdge(Node *from, Node *to);
    
    void markNodeAsRemoved(Node *node);
    
    void resetRemoveMarks();
    
    void debug();

 };

#endif /* Graph_hpp */
