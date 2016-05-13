//
//  Edge.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov on 11.05.16.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Edge.hpp"

Edge::Edge(Node *from, Node *to) {
    this->removed = false;
    this->from = from;
    this->to = to;
}
