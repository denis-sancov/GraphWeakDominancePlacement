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
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

namespace csd {
    
    static inline unsigned long graph_number_of_fips(Graph const& graph,
                                                     std::vector<Node *> const &t1,
                                                     std::vector<Node *> const &t2) {
        unsigned long number_of_fips = 0;
        
        for (unsigned long i = 0; i < t2.size(); ++i) {
            for (unsigned long j = i + 1; j < t2.size(); ++j) {
               
            
                auto first_in_t1 = find(t1.begin(), t1.end(), t2.at(i)) - t1.begin();
                auto second_in_t1 = find(t1.begin(), t1.end(), t2.at(j)) - t1.begin();
            
                if (i <= j && first_in_t1 <= second_in_t1) {
                    if (!graph.hasPath(t2.at(i), t2.at(j))) {
                        number_of_fips += 1;
                    }
                }
            }
        }
        
        return number_of_fips;
    }
    
    static inline void graph_debug_topological_sort(std::vector<Node *> const &topologicalSort) {
        for (auto node : topologicalSort) {
            std::cout << node->getID() << " ";
        }
        std::cout << std::endl;
    }
    
    
    static inline std::vector<Node *> graph_kanhs_topological_sort(Graph const &graph) {
        
        auto zero_in_nodes = graph.zeroInNodes();
                
        std::vector<Node *> topological_sort;
        topological_sort.reserve(graph.getNodesCount());

        while (!zero_in_nodes.empty()) {
            auto node = zero_in_nodes.back();
            zero_in_nodes.pop_back();
            topological_sort.push_back(node);
    
            for (auto edge : node->getOutEdges()) {
                edge->setRemoved(true);
                
                if (edge->to()->getInDegree() == 0) {
                    zero_in_nodes.push_back(edge->to());
                }
            }
        }
        graph.resetRemoveMarks();
        
        
        return topological_sort;
    }
    
#pragma mark <Topological sort using local search>
    
    static inline std::vector<Node *> graph_local_search_topological_sort(Graph const &graph,
                                                                          std::vector<Node *> const &t1) {
        std::vector<Node *> topological_sort(t1);
        auto size = t1.size();
    
        bool **_fipsMatrix = new bool*[size];
        for(int i = 0; i < size; ++i) {
            _fipsMatrix[i] = new bool[size];
            for (int j = 0; j < size; ++j) {
                _fipsMatrix[i][j] = false;
            }
        }
    
    
        for (unsigned long i = 0; i < size - 1; ++i) {
            for (unsigned long j = i; j < size; ++j) {
                auto from = t1.at(i);
                auto to = t1.at(j);
                
                _fipsMatrix[from->getID()][to->getID()] = !graph.hasPath(from, to);
            }
        }
        
        auto swipePerformed = [_fipsMatrix, &topological_sort](unsigned long from, unsigned long to) mutable {
            auto fromNode = topological_sort.at(from);
            auto toNode = topological_sort.at(to);

            if (_fipsMatrix[fromNode->getID()][toNode->getID()]) {
                
                _fipsMatrix[fromNode->getID()][toNode->getID()] = false;
                iter_swap(topological_sort.begin() + (long)from, topological_sort.begin() + (long)to);

                return true;
            }
            return false;
        };
        
        bool swipe_available = true;
    
        while (swipe_available) {
            swipe_available = false;
    
            for (unsigned long i = 0; i < size-1; i++) {
                swipe_available = swipePerformed(i, i+1);
            }
    
            for (unsigned long i = size-1; i > 0; i--) {
                swipe_available = swipePerformed(i-1, i);
            }
        }
    
        for (unsigned long i = 0; i < size; i++) {
            delete[] _fipsMatrix[i];
        }
        delete[] _fipsMatrix;
    
        return topological_sort;
    }
    
    
#pragma mark - <Max Rank topological sort>
    
    static inline std::vector<Node *> graph_max_rank_topological_sort(Graph const &graph,
                                                                      std::vector<Node *> const &t1) {
        auto nodes = graph.getNodes();
        
        auto maxRankNode = [&nodes, &t1]() {
            long max_rank = 0;
            long rank = 0;
            for (auto node : nodes) {
                if (node->isRemoved() == true) {
                    continue;
                }
                if (node->getInDegree() == 0) {
                    rank = find(t1.begin(), t1.end(), node) - t1.begin();
                    if (rank > max_rank) {
                        max_rank = rank;
                    }
                }
            }
            return t1.at((unsigned long)max_rank);
        };
        
        unsigned long nodes_count = nodes.size();
        
        std::vector<Node *> topological_sort;
        topological_sort.reserve(nodes_count);


        for (unsigned long i = 0; i < nodes_count; i++) {
            auto node = maxRankNode();
            node->markAsRemoved(true);
            topological_sort.push_back(node);
        }
        graph.resetRemoveMarks();
        return topological_sort;
    }
    
    
    
#pragma mark - <Optimal topological sort>
    
    
    static inline void graph_find_optimal_topological_sort(Graph const& graph,
                                                           std::vector<Node *> const &t1,
                                                           std::vector<std::vector<Node *>> &candidates,
                                                           long &threshold) {
        std::vector<std::vector<Node *>> newCandidates;
        
        for (auto topSort : candidates) {
            
            for (auto node : topSort) {
                node->markAsRemoved(true);
            }
            
            auto candidateNodes = graph.zeroInNodes();
            
            if (candidateNodes.size() == 0) {
                return;
            }
        
            
            for (auto node : candidateNodes) {
                topSort.push_back(node);
                unsigned long fips = graph_number_of_fips(graph, t1, topSort);
                if (fips <= (t1.size() % 11)) {
                    std::vector<Node *> newCandidate(topSort);
                    newCandidates.push_back(newCandidate);
                } else {
                    threshold += 1;
                }
                topSort.pop_back();
            }
            
            for (auto node : topSort) {
                node->markAsRemoved(false);
            }
        }
        candidates.clear();
        candidates.insert(candidates.end(), newCandidates.begin(), newCandidates.end());
        
        if (candidates.size() > 0) {
            graph_find_optimal_topological_sort(graph, t1, candidates, threshold);
        }
    }
    
    static inline std::vector<std::vector<Node *>> graph_optimal_topological_sorts(Graph const &graph,
                                                                                   std::vector<Node *> const &t1) {
        auto zero_in_nodes = graph.zeroInNodes();
        std::cout << "zero in node " << std::endl;
        graph_debug_topological_sort(zero_in_nodes);
                
        std::vector<std::vector<Node *>> result;
        
        std::vector<std::vector<Node *>> tmp;
        
        
        long threshold = 0;

        auto numberOfSourceNodes = zero_in_nodes.size();
        
        for (auto node : zero_in_nodes) {
            
            std::cout << "performing node " << node->getID() << std::endl;
            
            std::vector<Node *> candidate;
            candidate.push_back(node);
            tmp.push_back(candidate);
            
            graph_find_optimal_topological_sort(graph, t1, tmp, threshold);
        
            for (auto item : tmp) {
                if (item.size() == t1.size()) {
                    result.push_back(item);
                }
            }
            tmp.clear();
            
            numberOfSourceNodes -= 1;
        }

        return result;
    }

}

#endif /* GraphAlgorithms_hpp */
