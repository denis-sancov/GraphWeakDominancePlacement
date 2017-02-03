//
//  Node.hpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <vector>
#include <string>
#include "Edge.hpp"

namespace csd {
    class Node {
    public:
        Node(unsigned long id);
        Node(unsigned long id, std::string const &label);
        ~Node();
        
        unsigned long getID() const;
        std::string getLabel() const;

        bool isRemoved() const;
        void markAsRemoved(bool removed);
        
        
        unsigned long getInDegree() const;
        unsigned long getOutDegree() const;

        std::vector<Edge *> getOutEdges() const;
        std::vector<Edge *> getInEdges() const;

        void addEdgeTo(Node *to);
    private:
        const unsigned long _id;
        const std::string _label;

        bool _removed = false;
       
        std::vector<Edge *> _outEdges;
        std::vector<Edge *> _inEdges;

        friend std::ostream& operator<<(std::ostream&, const Node&);
    };
}
#endif /* Node_hpp */
