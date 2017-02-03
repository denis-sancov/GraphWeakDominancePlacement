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

namespace csd {

    class Graph {
    public:
        Graph();
        Graph(unsigned long nodesCount, double edge_density);
        ~Graph();
        
        unsigned long getNodesCount() const;
        
        std::vector<Node *> zeroInNodes() const;
        std::vector<Node *> getNodes() const;

        bool hasPath(Node *from, Node *to) const;
        
        void resetRemoveMarks() const;
    private:
        std::vector<Node *> _nodes;
        bool **_transitive_closure_matrix;
        
        void prepareTransitiveClosureMatrix();
        
        void addEdge(Node *from, Node *to);
        
        friend std::ostream& operator<<(std::ostream&, const Graph&);
    };
}
#endif /* Graph_hpp */
