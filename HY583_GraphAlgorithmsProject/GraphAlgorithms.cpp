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

#pragma mark <BFS to find a path between two nodes>

bool is_there_is_a_path_from(node_ptr_strong from, node_ptr_strong to, Graph &graph) {
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

std::vector<node_ptr_strong> topological_sort_using_local_search(Graph &graph, vector<node_ptr_strong> &t1) {
   // cout << "Performing  topological sort using local search approach" << endl;
    vector<node_ptr_strong> topological_sort(t1);
    unsigned long size = t1.size();
    
    bool **fipsMatrix = new bool*[size];
    for(unsigned long i = 0; i < size; i++) {
        fipsMatrix[i] = new bool[size];
    }
    
    for (unsigned long i = 0; i < size - 1; i++) {
        for (unsigned long j = i + 1; j < size; j++) {
            bool status = is_there_is_a_path_from(t1.at(i), t1.at(j), graph);
            fipsMatrix[i][j] = (status == false && i < j);
        }
    }

    unsigned long i = 0;
    unsigned long j = 1;
    bool reversedIteration = false;
    bool swipe_available = true;

    unsigned long originalI = 0;
    unsigned long originalJ = 0;

    
    while (swipe_available) {
        
    }
    
//
//    bool swipe_was_performed_on_iteration = 0;
//    unsigned long reverse = false;
//    while (1) {
//        t1i = find(t1.begin(), t1.end(), topological_sort.at(i)) - t1.begin();
//        t1j = find(t1.begin(), t1.end(), topological_sort.at(j)) - t1.begin();
//        if (fipsMatrix[t1i][t1j] == 1 || fipsMatrix[t1j][t1i] == 1) {
//            fipsMatrix[t1i][t1j] = 0;
//            fipsMatrix[t1j][t1i] = 0;
//            
//            iter_swap(topological_sort.begin() + i, topological_sort.begin() + j);
//            swipe_was_performed_on_iteration = true;
//        }
//        
//        if (j == 0 && reverse == true) {
//            i = 0;
//            j = i + 1;
//            reverse = false;
//            if (swipe_was_performed_on_iteration == false) {
//                break;
//            }
//            swipe_was_performed_on_iteration = false;
//            continue;
//        } else if (j == (size-1) && reverse == false) {
//            i = (size-1);
//            j = i - 1;
//            reverse = true;
//            if (swipe_was_performed_on_iteration == false) {
//                break;
//            }
//            swipe_was_performed_on_iteration = false;
//            continue;
//        }
//
//        if (reverse == false) {
//            i++;
//            j = i + 1;
//        } else {
//            i--;
//            j = i - 1;
//        }
//    }
    
    delete[] fipsMatrix;
    
//    cout << "Topological sort using Local search approach was performed" << endl;
//    for (node_ptr_strong node : topological_sort) {
//        cout << node->value << " ";
//    }
//    cout << endl;
    return topological_sort;
}

#pragma mark <Topological sort using Max rank>

node_ptr_strong _node_with_max_rank(vector<node_ptr_strong> &nodes, vector<node_ptr_strong> &t1) {
    unsigned long max_rank = 0;
    unsigned long rank = 0;
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
    return t1.at(max_rank);
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
    
//    cout << "Topological sort using Max Rank approach was performed" << endl;
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
            unsigned long i_in_t2 = find(t2.begin(), t2.end(), t1.at(i)) - t2.begin();
            
            unsigned long j_in_t2 = find(t2.begin(), t2.end(), t1.at(j)) - t2.begin();
            
            if (i <= j && i_in_t2 <= j_in_t2) {
                if (is_there_is_a_path_from(t1.at(i), t1.at(j), graph) == false) {
                    number_of_fips += 1;
                }
            }
        }
    }    
    return number_of_fips;
}