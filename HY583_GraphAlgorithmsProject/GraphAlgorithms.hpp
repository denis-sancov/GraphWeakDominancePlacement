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

std::vector<node_ptr_strong> topological_sort_using_kanhs_algorithm(Graph &graph);

std::vector<node_ptr_strong> topological_sort_using_local_search(Graph &graph, std::vector<node_ptr_strong> &t1);

std::vector<node_ptr_strong> topological_sort_using_max_rank(Graph &graph, std::vector<node_ptr_strong> &t1);

unsigned long topological_sort_number_of_fips(Graph &graph, std::vector<node_ptr_strong> &t1,
                                                            std::vector<node_ptr_strong> &t2);

#endif /* GraphAlgorithms_hpp */
