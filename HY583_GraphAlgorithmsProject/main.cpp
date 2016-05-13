//
//  main.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov on 28.04.16.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Graph.hpp"
#include "GraphAlgorithms.hpp"


int main(int argc, const char * argv[]) {
        
    Graph *graph = new Graph(200);
    std::vector<Node *> *t1 = topological_sort_using_kanhs_algorithm(graph);
    
//    std::vector<Node *> *local_search_topological_search = topological_sort_using_local_search(graph, t1);
//    topological_sort_number_of_fips(graph, t1, local_search_topological_search);
//    
//    std::vector<Node *> *max_rank_topological_sort = topological_sort_using_max_rank(graph, t1);
//    topological_sort_number_of_fips(graph, t1, max_rank_topological_sort);

  
    std::vector<Node *> *path_cover_topological_sort =  topological_sort_using_path_cover(graph, t1);
    //topological_sort_number_of_fips(graph, t1, path_cover_topological_sort);
    
    return 0;
}
