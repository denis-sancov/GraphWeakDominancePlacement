//
//  Node.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Node.hpp"
#include <iostream>

using namespace csd;

Node::Node(unsigned long id):_id(id) { }

Node::Node(unsigned long id, std::string const &label):_id(id), _label(label) { }

unsigned long Node::getID() const {
    return _id;
}

std::string Node::getLabel() const {
    return _label;
}

bool Node::isRemoved() const {
    return _removed;
}

void Node::markAsRemoved(bool removed) {
    _removed = removed;
    
    for (auto edge : _inEdges) {
        edge->setRemoved(removed);
    }
    
    for (auto edge : _outEdges) {
        edge->setRemoved(removed);
    }
}

unsigned long Node::getInDegree() const {
    unsigned long tmp = 0;
    for (auto edge : _inEdges) {
        if (!edge->isRemoved()) {
            tmp += 1;
        }
    }
    return tmp;
}

unsigned long Node::getOutDegree() const {
    unsigned long tmp = 0;
    for (auto edge : _outEdges) {
        if (!edge->isRemoved()) {
            tmp += 1;
        }
    }
    return tmp;

}

std::vector<Edge *> Node::getOutEdges() const {
    return _outEdges;
}

std::vector<Edge *> Node::getInEdges() const {
    return _inEdges;
}

void Node::addEdgeTo(Node *to) {
    Edge *edge = new Edge(this, to);
    _outEdges.push_back(edge);
    to->_inEdges.push_back(edge);
}

Node::~Node() {
    _inEdges.clear();
    for (auto edge : _outEdges) {
        delete edge;
    }
    _outEdges.clear();
}

std::ostream& csd::operator<<(std::ostream& os, const Node& node) {
    os << "Debug Node with id = " << node._id << std::endl;
    
    if (node._outEdges.size() > 0) {
        os << "Out nodes" << std::endl;
        for (auto edge : node._outEdges) {
            os << "node = " << edge->to()->getID() << std::endl;
        }
    }
    
    if (node._inEdges.size() > 0) {
        os << "In nodes" << std::endl;
        for (auto edge : node._inEdges) {
            os << "node = " << edge->from()->getID() << std::endl;
        }
    }
    os << std::endl;
    
    return os;
}

