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
    std::vector<node_ptr_strong> _nodes;
public:    
    Graph(unsigned long nodes_count, unsigned short edge_density);
        
    const std::vector<node_ptr_strong> nodes() {
        return _nodes;
    }
    
    void addEdge(node_ptr_strong from, node_ptr_strong to);
    
    void markNodeAsRemoved(node_ptr_strong node);
    
    void resetRemoveMarks();
    
    void debug();
 };

#endif /* Graph_hpp */
