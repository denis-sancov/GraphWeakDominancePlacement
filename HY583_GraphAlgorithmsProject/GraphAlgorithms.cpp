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

using namespace std;

#pragma mark - incomparable pairs count

unsigned long graph_number_of_incomparable_pairs(Graph &graph) {
    unsigned long e = 0;
    for (unsigned long i = 0; i < graph.nodes().size()-1; i++) {
        node_ptr_strong from = graph.nodes()[i];
        for (unsigned long j = i+1; j < graph.nodes().size(); j++) {
            node_ptr_strong to = graph.nodes()[j];
            if (graph.transitiveClosureMatrix()[from->identifier][to->identifier] == true) {
                e += 1;
            }
        }
    }
    return graph.nodes().size() * (graph.nodes().size() - 1) / 2 - e;
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
//
//    cout << "Topological sort using Kahn's algorithm was performed" << endl;
//    for (node_ptr_weak node : topological_sort) {
//        cout << node.lock()->label << " ";
//    }
//    cout << endl;
    return topological_sort;
}

#pragma mark <Topological sort using local search>


bool _perform_swipe(unsigned long from, unsigned long to,
                    std::vector<node_ptr_strong> &topological_sort,
                    bool **fipsMatrix) {
    node_ptr_strong fromNode = topological_sort.at(from);
    node_ptr_strong toNode = topological_sort.at(to);
    
    
    if (fipsMatrix[fromNode->identifier][toNode->identifier] == true) {
        fipsMatrix[fromNode->identifier][toNode->identifier] = false;
        iter_swap(topological_sort.begin() + (long)from, topological_sort.begin() + (long)to);
        return true;
    }
    return false;
}

std::vector<node_ptr_strong> topological_sort_using_local_search(Graph &graph, vector<node_ptr_strong> &t1) {
    vector<node_ptr_strong> topological_sort(t1);
    unsigned long size = t1.size();
    
    bool **_fipsMatrix = new bool*[size];
    for(int i = 0; i < size; i++) {
        _fipsMatrix[i] = new bool[size];
    }
    
    
    for (unsigned long i = 0; i < size - 1; i++) {
        for (unsigned long j = i; j < size; j++) {
            node_ptr_strong from = t1.at(i);
            node_ptr_strong to = t1.at(j);
            _fipsMatrix[from->identifier][to->identifier] = !graph.transitiveClosureMatrix()[from->identifier][to->identifier];
        }
    }

    bool swipe_available = true;
    
    while (swipe_available) {
        swipe_available = false;

        for (unsigned long i = 0; i < size-1; i++) {
            if (_perform_swipe(i, i+1, topological_sort, _fipsMatrix)) {
                swipe_available = true;
            }
        }
        
        for (unsigned long i = size-1; i > 0; i--) {
            if (_perform_swipe(i-1, i, topological_sort, _fipsMatrix)) {
                swipe_available = true;
            }
        }
    }
    
    for (unsigned long i = 0; i < size; i++) {
        delete[] _fipsMatrix[i];
    }
    delete[] _fipsMatrix;
//    
//    cout << "Topological sort using Local search approach was performed" << endl;
//    for (node_ptr_strong node : topological_sort) {
//        cout << node->label << " ";
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
//    
//    cout << "Topological sort using Max rank" << endl;
//    for (node_ptr_strong node : topological_sort) {
//        cout << node->label << " ";
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
                node_ptr_strong from = t1.at(i);
                node_ptr_strong to = t1.at(j);
                if (graph.transitiveClosureMatrix()[from->identifier][to->identifier] == false) {
                    number_of_fips += 1;
                }
            }
        }
    }
   // std::cout << "fips count = " << number_of_fips << std::endl;
    return number_of_fips;
}