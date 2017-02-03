//
//  Edge.hpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef Edge_hpp
#define Edge_hpp

namespace csd {
   
    class Node;
    
    class Edge {
    public:
        Edge(Node *const from, Node *const to);
        
        bool isRemoved() const;
        void setRemoved(bool removed);
        
        Node *from() const;
        Node *to() const;
    private:
        Node *const _from, *const _to;
        bool _removed = false;
    };
}
#endif /* Edge_hpp */
