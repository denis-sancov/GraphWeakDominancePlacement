//
//  main.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "Graph.hpp"
#include "GraphAlgorithms.hpp"
#include <iostream>
#include <thread>
#include <mutex>

static unsigned long amount_of_graphs = 100;
static unsigned long amount_of_nodes = 1000;
static unsigned short edge_density = 20;


typedef struct _result {
    unsigned long local_search_fips;
    unsigned long max_rank_fips;
} Result;

std::mutex *mtx;
unsigned long completed_graphs = 0;

void graph_thread(unsigned long amount_of_graphs_to_generate, std::vector<Result> *results) {
    Result resultStruct;
    resultStruct.local_search_fips = 0;
    resultStruct.max_rank_fips = 0;
    for (unsigned long i = 0; i < amount_of_graphs_to_generate; i++) {
        Graph graph = Graph(amount_of_nodes, edge_density);
      //  unsigned long number_of_incomparable_pairs = graph_number_of_incomparable_pairs(graph);
        
        
        std::vector<node_ptr_strong> t1 = topological_sort_using_kanhs_algorithm(graph);
        
        std::vector<node_ptr_strong> local_search_topological_sort = topological_sort_using_local_search(graph, t1);
        resultStruct.local_search_fips += topological_sort_number_of_fips(graph, t1, local_search_topological_sort);
        local_search_topological_sort.clear();

        std::vector<node_ptr_strong> max_rank_topological_sort = topological_sort_using_max_rank(graph, t1);
        resultStruct.max_rank_fips += topological_sort_number_of_fips(graph, t1, max_rank_topological_sort);
        max_rank_topological_sort.clear();
        
        t1.clear();
        
        mtx->lock();
        
        completed_graphs += 1;
//        std::cout << "max number of incomparable pairs " << number_of_incomparable_pairs << std::endl;
        std::cout << completed_graphs << " of " << amount_of_graphs << std::endl;
        
        
        mtx->unlock();
    }
    results->push_back(resultStruct);
}



int main(int argc, const char * argv[]) {
    mtx = new std::mutex();
    std::vector<Result> results;
    
    results.reserve(amount_of_graphs);

    std::vector<std::thread> threads;
    
    unsigned long threads_count = std::thread::hardware_concurrency();
    if (threads_count == 0) {
        threads_count = 2;
    }
    unsigned long amount_of_graphs_per_thread = amount_of_graphs / threads_count;

    std::cout << "Progress: " << std::endl;
    for (unsigned long i = 0; i < threads_count; i++) {
        threads.push_back(std::thread(graph_thread, amount_of_graphs_per_thread, &results));
    }
    for (auto& th : threads) {
        th.join();
    }
    
    unsigned long total_fips_local_search = 0;
    unsigned long total_fips_max_rank = 0;
    
    for (Result result : results) {
        total_fips_local_search += result.local_search_fips;
        total_fips_max_rank += result.max_rank_fips;
    }
    
    std::cout << "fips are :" << std::endl;
    std::cout << "local search = " << total_fips_local_search / amount_of_graphs << std::endl;
    std::cout << "max rank = " << total_fips_max_rank / amount_of_graphs << std::endl;

    delete mtx;
    
    return 0;
}
