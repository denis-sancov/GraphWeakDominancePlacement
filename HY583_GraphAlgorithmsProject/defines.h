//
//  defines.h
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef defines_h
#define defines_h

#include <memory>

class Node;
class Edge;

typedef std::shared_ptr<Node> node_ptr_strong;
typedef std::weak_ptr<Node> node_ptr_weak;

typedef std::shared_ptr<Edge> edge_ptr_strong;
typedef std::weak_ptr<Edge> edge_ptr_weak;


#endif /* defines_h */
