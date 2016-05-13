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
    const std::string *value;
    std::vector<Edge *> out_edges;
    std::vector<Edge *> in_edges;

    unsigned long in_degree() {
        unsigned long tmp = 0;
        for (Edge *edge : in_edges) {
            if (edge->removed == false) {
                tmp += 1;
            }
        }
        return tmp;
    }
    
    unsigned long out_degree() {
        unsigned long tmp = 0;
        for (Edge *edge : out_edges) {
            if (edge->removed == false) {
                tmp += 1;
            }
        }
        return tmp;
    }

    void resetRemovedMarks() {
        for (Edge *edge : in_edges) {
            edge->removed = false;
        }
        for (Edge *edge : out_edges) {
            edge->removed = false;
        }
    }
    
    
    Node(std::string value);   
    void debug();
};
#endif /* Node_hpp */
