//
//  NodeLevel.hpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov on 03.05.16.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef NodeLevel_hpp
#define NodeLevel_hpp

#include <vector>
#include "Node.hpp"

class NodeLevel {
public:
    std::vector<Node *> nodes;
    NodeLevel(unsigned long level, unsigned long nodes_count);
    void add_edges_to_level(const NodeLevel *level);
};

#endif /* NodeLevel_hpp */
