//
//  Edge.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Edge.hpp"
#include <iostream>

using namespace csd;

Edge::Edge(Node *const from, Node *const to):_from(from), _to(to) { }

Node *Edge::from() const {
    return _from;
}

Node *Edge::to() const {
    return _to;
}

bool Edge::isRemoved() const {
    return _removed;
}

void Edge::setRemoved(bool removed) {
    _removed = removed;
}
