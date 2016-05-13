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

bool is_there_is_a_path_from(Node *from, Node *to) {
    if (from == to) {
        return true;
    }
    for (Edge *edge : from->out_edges) {
        if (is_there_is_a_path_from(edge->to, to)) {
            return true;
        }
    }
    return false;
}

vector<pair<Node *, Node *>>* find_potential_fips(Graph *graph, vector<Node *> *t1) {
    vector<pair<Node *, Node *>> *potential_fips = new vector<pair<Node *, Node *>>;
//    for (unsigned long i = 0; i < t1->size(); i++) {
//        for (unsigned long j = (i+1); j < t1->size(); j++) {
//            Node *from = t1->at(i);
//            Node *to = t1->at(j);
//            if (is_there_is_a_path_from(from, to) == false) {
//                cout << "potential fip from " << from->value() << " to " << to->value() << endl;
//            }
//            graph->reset_all_remove_marks();
//        }
//    }
    return potential_fips;
}

vector<Node *>* topological_sort_using_kanhs_algorithm(Graph *graph) {
    cout << "Performing Kahn's algorithm" << endl;
    stack<Node *> *zero_in_nodes_stack = new stack<Node *>;
    
    for (Node *node : graph->nodes()) {
        if (node->in_degree() == 0) {
            zero_in_nodes_stack->push(node);
        }
    }

    vector<Node *> *topological_sort = new vector<Node *>;
    topological_sort->reserve(graph->nodes().size());

    while (!zero_in_nodes_stack->empty()) {
        Node *node = zero_in_nodes_stack->top();
        
        zero_in_nodes_stack->pop();
        topological_sort->push_back(node);

        for (Edge *edge : node->out_edges) {
            edge->removed = true;
            Node *toNode = edge->to;
            if (toNode->in_degree() == 0) {
                zero_in_nodes_stack->push(toNode);
            }
        }
    }

    graph->resetRemoveMarks();
    
    delete zero_in_nodes_stack;
    cout << "Topological sort using Kahn's algorithm was performed" << endl;
//    for (Node *node : *topological_sort) {
//        cout << *node->value << " ";
//    }
//    cout << endl;
    return topological_sort;
}


vector<Node *>* topological_sort_using_local_search(Graph *graph, vector<Node *> *t1) {
    cout << "Performing  topological sort using local search approach" << endl;

    vector<Node *> *topological_sort = new vector<Node *>(*t1);
    unsigned long size = t1->size();
    
    bool **fipsMatrix = new bool*[size];
    for(unsigned long i = 0; i < size; i++) {
        fipsMatrix[i] = new bool[size];
    }
    
    for (unsigned long i = 0; i < size; i++) {
        for (unsigned long j = i; j < size; j++) {
            fipsMatrix[i][j] = (is_there_is_a_path_from(t1->at(i), t1->at(j)) == false && i < j);
        }
    }
    unsigned long i = 0;
    unsigned long j = 1;
    unsigned long t1i = 0;
    unsigned long t1j = 0;

    bool swipe_was_performed_on_iteration = 0;
    unsigned long reverse = false;
    while (1) {
        t1i = find(t1->begin(), t1->end(), topological_sort->at(i)) - t1->begin();
        t1j = find(t1->begin(), t1->end(), topological_sort->at(j)) - t1->begin();
        if (fipsMatrix[t1i][t1j] == 1 || fipsMatrix[t1j][t1i] == 1) {
            fipsMatrix[t1i][t1j] = 0;
            fipsMatrix[t1j][t1i] = 0;
            
            iter_swap(topological_sort->begin() + i, topological_sort->begin() + j);
            swipe_was_performed_on_iteration = true;
        }
        
        if (j == 0 && reverse == true) {
            i = 0;
            j = i + 1;
            reverse = false;
            if (swipe_was_performed_on_iteration == false) {
                break;
            }
            swipe_was_performed_on_iteration = false;
            continue;
        } else if (j == (size-1) && reverse == false) {
            i = (size-1);
            j = i - 1;
            reverse = true;
            if (swipe_was_performed_on_iteration == false) {
                break;
            }
            swipe_was_performed_on_iteration = false;
            continue;
        }

        if (reverse == false) {
            i++;
            j = i + 1;
        } else {
            i--;
            j = i - 1;
        }
    }
    
    delete[] fipsMatrix;
    
    cout << "Topological sort using Local search approach was performed" << endl;
//    for (Node *node : *topological_sort) {
//        cout << *node->value << " ";
//    }
//    cout << endl;
    return topological_sort;
}


Node* _node_with_max_rank(const vector<Node *> *nodes, vector<Node *> *t1) {
    unsigned long max_rank = 0;
    unsigned long rank = 0;
    for (Node *node : *nodes) {
        if (node->removed == true) {
            continue;
        }
        if (node->in_degree() == 0) {
            rank = find(t1->begin(), t1->end(), node) - t1->begin();
            if (rank > max_rank) {
                max_rank = rank;
            }
        }  
    }
    return t1->at(max_rank);
}

vector<Node *>* topological_sort_using_max_rank(Graph *graph, vector<Node *> *t1) {
    cout << "Performing Max Rank approach" << endl;
    const vector<Node *> nodes = graph->nodes();
    unsigned long nodes_count = nodes.size();
    vector<Node *> *topological_sort = new vector<Node *>;
    topological_sort->reserve(nodes_count);
    
   // cout << "Progress:" << endl;
    for (unsigned long i = 0; i < nodes_count; i++) {
        Node *node = _node_with_max_rank(&nodes, t1);
        graph->markNodeAsRemoved(node);
        topological_sort->push_back(node);
       // cout << ((float)i / nodes_count) * 100 << "%" << endl;
    }

    graph->resetRemoveMarks();
    
    cout << "Topological sort using Max Rank approach was performed" << endl;
//    for (Node *node : *topological_sort) {
//        cout << *node->value << " ";
//    }
//    cout << endl;
    return topological_sort;
}

std::vector<Node *>* topological_sort_using_path_cover(Graph *graph, std::vector<Node *> *t1) {
    cout << "Topological sort using Path cover approach" << endl;
 //   const vector<Node *> *nodes = graph->nodes();
//    vector<Node *> *topological_sort = new vector<Node *>;
//    
//    
//    vector<Node *> *border = new vector<Node *>;
    
    
//    topological_sort->reserve(nodes->size());
//    
//    vector<pair<Node *, Node *>> *potential_fips = find_potential_fips(graph, t1);
//    
//    for (unsigned long j = 0; j < t1->size(); j++) {
//        for (unsigned long i = 0; i < potential_fips->size(); i++) {
//            
//        }
//    }
//    
//
//    
//    cout << "Topological sort using Path cover approach : " << endl;
//    for (Node *node : *topological_sort) {
//        cout << node->value() << " ";
//    }
//    cout << endl;
    return nullptr;
}

unsigned long topological_sort_number_of_fips(Graph *graph, std::vector<Node *> *t1,
                                              std::vector<Node *> *t2) {
    cout << "Calculating number of fips" << endl;
//    cout << "T1 : " << endl;
//    for (Node *node : *t1) {
//        cout << *node->value << " ";
//    }
//    cout << endl;
//    cout << "T2 : " << endl;
//    for (Node *node : *t2) {
//        cout << *node->value << " ";
//    }
//    cout << endl;
    
  //  cout << "Progress:" << endl;
    unsigned long size = t1->size();
    unsigned long number_of_fips = 0;
    for (unsigned long i = 0; i < size; i++) {
        for (unsigned long j = (i+1); j < size; j++) {
            unsigned long i_in_t2 = find(t2->begin(), t2->end(), t1->at(i)) - t2->begin();
            unsigned long j_in_t2 = find(t2->begin(), t2->end(), t1->at(j)) - t2->begin();
            
            if (i <= j && i_in_t2 <= j_in_t2) {
                if (is_there_is_a_path_from(t1->at(i), t1->at(j)) == false) {
//                    cout << "No path from " << *t1->at(i)->value << " to " << *t2->at(j)->value << endl;
                    number_of_fips += 1;
                }
            }
        }
       // cout << ((float)i / size) * 100 << "%" << endl;
    }
    
    cout << "number of fips = " << number_of_fips << endl;
    return number_of_fips;
}