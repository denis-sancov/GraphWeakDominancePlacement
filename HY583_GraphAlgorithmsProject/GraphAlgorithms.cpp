//
//  GraphAlgorithms.cpp
//  HY583_GraphAlgorithmsProject
//
//  Created by Denis Sancov.
//  Copyright © 2016 University of Crete. All rights reserved.
//

#include "GraphAlgorithms.hpp"
#include <stack>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#pragma mark <BFS to find a path between two nodes>

bool _is_there_is_a_path_from(node_ptr_strong from, node_ptr_strong to, Graph &graph) {
    if (from->value > to->value) {
        return false;
    }
    if (from->value == to->value) {
        return true;
    }
    graph.resetRemoveMarks();
    
    stack<node_ptr_strong> nodes_stack;
    nodes_stack.push(from);
    while (!nodes_stack.empty()) {
        node_ptr_strong node = nodes_stack.top();
        nodes_stack.pop();
        for (edge_ptr_strong edge : node->out_edges) {
            node_ptr_strong toNode = edge->to.lock();
            if (toNode->value == to->value) {
                return true;
            }
            if (edge->removed == false) {
                edge->removed = true;
                if (toNode->value < to->value) {
                    nodes_stack.push(toNode);
                }
            }
        }
    }
    return false;
}

#pragma mark <Topological sort using Kahn's algorithm>

vector<node_ptr_strong> topological_sort_using_kanhs_algorithm(Graph &graph) {
    stack<node_ptr_strong> zero_in_nodes_stack;
    
    for (node_ptr_strong node : graph.nodes()) {
        if (node->in_degree() == 0) {
            zero_in_nodes_stack.push(node);
        }
    }

    vector<node_ptr_strong> topological_sort;
    topological_sort.reserve(graph.nodes().size());

    while (!zero_in_nodes_stack.empty()) {
        node_ptr_strong node = zero_in_nodes_stack.top();
        
        zero_in_nodes_stack.pop();
        topological_sort.push_back(node);

        for (edge_ptr_strong edge : node->out_edges) {
            edge->removed = true;
            node_ptr_strong toNode = edge->to.lock();
            if (toNode->in_degree() == 0) {
                zero_in_nodes_stack.push(toNode);
            }
        }
    }

    graph.resetRemoveMarks();

//    cout << "Topological sort using Kahn's algorithm was performed" << endl;
//    for (node_ptr_weak node : topological_sort) {
//        cout << node.lock()->value << " ";
//    }
//    cout << endl;
    return topological_sort;
}

#pragma mark <Topological sort using local search>

typedef unordered_multimap<node_ptr_strong, node_ptr_strong> FipsMultimap;

bool _perform_swipe(unsigned long from, unsigned long to,
                    std::vector<node_ptr_strong> &topological_sort,
                    FipsMultimap &fipsMultimap) {
    
    node_ptr_strong fromNode = topological_sort.at(from);
    node_ptr_strong toNode = topological_sort.at(to);
    
    pair<FipsMultimap::iterator, FipsMultimap::iterator> iterpair = fipsMultimap.equal_range(fromNode);
    
    FipsMultimap::iterator it = iterpair.first;
    for (; it != iterpair.second; ++it) {
        if (it->second->value == toNode->value) {
            fipsMultimap.erase(it);
            iter_swap(topological_sort.begin() + (long)from, topological_sort.begin() + (long)to);
            return true;
        }
    }
    return false;
}

std::vector<node_ptr_strong> topological_sort_using_local_search(Graph &graph, vector<node_ptr_strong> &t1) {
    vector<node_ptr_strong> topological_sort(t1);
    unsigned long size = t1.size();
    
    FipsMultimap fipsMultimap;
    
    for (unsigned long i = 0; i < size - 1; i++) {
        for (unsigned long j = i + 1; j < size; j++) {
            node_ptr_strong from = t1.at(i);
            node_ptr_strong to = t1.at(j);
            if (_is_there_is_a_path_from(from, to, graph) == false && i < j) {
                fipsMultimap.insert(pair<node_ptr_strong, node_ptr_strong>(from, to));
            }
        }
    }

    bool swipe_available = true;
    
    while (swipe_available) {
        swipe_available = false;

        for (unsigned long i = 0; i < size-1; i++) {
            if (_perform_swipe(i, i+1, topological_sort, fipsMultimap)) {
                swipe_available = true;
            }
        }
    
        for (unsigned long i = size-1; i > 0; i--) {
            if (_perform_swipe(i, i-1, topological_sort, fipsMultimap)) {
                swipe_available = true;
            }
        }
    }
    
    fipsMultimap.clear();
    
//    cout << "Topological sort using Local search approach was performed" << endl;
//    for (node_ptr_strong node : topological_sort) {
//        cout << node->value << " ";
//    }
//    cout << endl;
    return topological_sort;
}

#pragma mark <Topological sort using Max rank>

node_ptr_strong _node_with_max_rank(vector<node_ptr_strong> &nodes, vector<node_ptr_strong> &t1) {
    long max_rank = 0;
    long rank = 0;
    for (node_ptr_strong node : nodes) {
        if (node->removed == true) {
            continue;
        }
        if (node->in_degree() == 0) {
            rank = find(t1.begin(), t1.end(), node) - t1.begin();
            if (rank > max_rank) {
                max_rank = rank;
            }
        }  
    }
    return t1.at((unsigned long)max_rank);
}

std::vector<node_ptr_strong> topological_sort_using_max_rank(Graph &graph, std::vector<node_ptr_strong> &t1) {
    vector<node_ptr_strong> nodes = graph.nodes();
    
    unsigned long nodes_count = nodes.size();
   
    vector<node_ptr_strong> topological_sort;
    topological_sort.reserve(nodes_count);
    
    for (unsigned long i = 0; i < nodes_count; i++) {
        node_ptr_strong node = _node_with_max_rank(nodes, t1);
        graph.markNodeAsRemoved(node);
        topological_sort.push_back(node);
    }
    graph.resetRemoveMarks();
    
//    cout << "Topological sort using Max rank" << endl;
//    for (node_ptr_strong node : topological_sort) {
//        cout << node->value << " ";
//    }
//    cout << endl;

    
    return topological_sort;
}


std::vector<std::pair<Node *, Node *> *> pairs_that_cover_topological_sort(std::vector<Node *> *t1) {
    std::vector<std::pair<Node *, Node *> *> pairs;
//    unsigned long size = t1->size();
//    pairs.reserve(size/2);
//    for (unsigned int i = 0; i < size; i++) {
//        for (unsigned int j = i; j < size; j++) {
//            if(is_there_is_a_path_from(t1->at(i), t1->at(j), graph) == false && i < j) {
//                std::pair<Node *, Node *> *pair = new std::pair<Node *, Node *>(t1->at(i), t1->at(j));
//                pairs.push_back(pair);
//            }
//        }
//    }
//    pairs.shrink_to_fit();
    return pairs;
}

#pragma mark <Fips counting>

unsigned long topological_sort_number_of_fips(Graph &graph, std::vector<node_ptr_strong> &t1,
                                              std::vector<node_ptr_strong> &t2) {
    unsigned long size = t1.size();
    unsigned long number_of_fips = 0;
    for (unsigned long i = 0; i < size; i++) {
        for (unsigned long j = (i+1); j < size; j++) {
            long i_in_t2 = find(t2.begin(), t2.end(), t1.at(i)) - t2.begin();
            
            long j_in_t2 = find(t2.begin(), t2.end(), t1.at(j)) - t2.begin();
            
            if (i <= j && i_in_t2 <= j_in_t2) {
                if (_is_there_is_a_path_from(t1.at(i), t1.at(j), graph) == false) {
                    number_of_fips += 1;
                }
            }
        }
    }    
    return number_of_fips;
}