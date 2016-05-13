//
//  GraphAlgorithms.hpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#ifndef GraphAlgorithms_hpp
#define GraphAlgorithms_hpp

#include "Graph.hpp"
#include <vector>

bool is_there_is_a_path_from(Node *from, Node *to);

std::vector<Node *>* topological_sort_using_kanhs_algorithm(Graph *graph);

std::vector<Node *>* topological_sort_using_local_search(Graph *graph, std::vector<Node *> *t1);

std::vector<Node *>* topological_sort_using_max_rank(Graph *graph, std::vector<Node *> *t1);

std::vector<Node *>* topological_sort_using_path_cover(Graph *graph, std::vector<Node *> *t1);

unsigned long topological_sort_number_of_fips(Graph *graph, std::vector<Node *> *t1,
                                                            std::vector<Node *> *t2);

#endif /* GraphAlgorithms_hpp */
