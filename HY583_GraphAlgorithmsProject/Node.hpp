//
//  Node.hpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <string>
#include <vector>
#include "Edge.hpp"

class Node {

public:
    bool removed;
    unsigned int value;
    std::vector<edge_ptr_strong> out_edges;
    std::vector<edge_ptr_strong> in_edges;

    unsigned long in_degree() {
        unsigned long tmp = 0;
        for (edge_ptr_strong edge : in_edges) {
            if (edge->removed == false) {
                tmp += 1;
            }
        }
        return tmp;
    }
    
    unsigned long out_degree() {
        unsigned long tmp = 0;
        for (edge_ptr_strong edge : out_edges) {
            if (edge->removed == false) {
                tmp += 1;
            }
        }
        return tmp;
    }

    void resetRemovedMarks() {
        for (edge_ptr_strong edge : in_edges) {
            edge->removed = false;
        }
        for (edge_ptr_strong edge : out_edges) {
            edge->removed = false;
        }
    }
    
    Node(unsigned int value);
    void debug();
    
};
#endif /* Node_hpp */
