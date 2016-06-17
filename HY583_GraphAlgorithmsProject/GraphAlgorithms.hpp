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

bool is_there_is_a_path_from(node_ptr_strong from, node_ptr_strong to, Graph &graph);

std::vector<node_ptr_strong> topological_sort_using_kanhs_algorithm(Graph &graph);

std::vector<node_ptr_strong> topological_sort_using_local_search(Graph &graph, std::vector<node_ptr_strong> &t1);

std::vector<node_ptr_strong> topological_sort_using_max_rank(Graph &graph, std::vector<node_ptr_strong> &t1);

unsigned long topological_sort_number_of_fips(Graph &graph, std::vector<node_ptr_strong> &t1,
                                                            std::vector<node_ptr_strong> &t2);

#endif /* GraphAlgorithms_hpp */
