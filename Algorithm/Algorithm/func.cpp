//
//  func.cpp
//  Algorithm
//
//  Created by Thim Lohse on 2018-10-21.
//  Copyright © 2018 Thim Lohse. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <cmath>
#include <vector>
#include <limits>
#include <unistd.h>
#include <algorithm>    // std::sort
#include<set> // for set operations

using namespace std;

class Functions{
    
    //Class member functions definitions
public:
    //** Compute the euclidian distance between two nodes in the plane **/
    int computeDist(pair<double, double> a, pair<double, double> b);
    
    //** Compute the length of a tour **/
    int tourLength(vector<int> tour, vector<pair<double, double>> vertices);
    
    //** Compute the greedy algorithm for shortest cycle from given startnode**/
    vector<int> greedy(vector<pair<double, double>> vertices, int startNode);
    
    //** Minimize the shortest cycle trying all or random set of startnodes **/
    vector<int> minimizeGreedy(vector<pair<double, double>> vertices);
    
    
    
};
int computeDist(pair<double, double> a, pair<double, double> b){
    //Euclidian distance rounded to nearest integer
    //-> sqrt( [x1 - x2]^2 + [y1 - y2]^2 )
    return int(round(sqrt(pow(a.first - b.first, 2.0) + pow(a.second - b.second, 2.0))));
}
int tourLength(vector<int> tour, vector<pair<double, double>> vertices){
    int res = 0;
    for(auto it = tour.begin(); it != tour.end()-1; it++){
        res += computeDist(vertices.at((*it)), vertices.at((*(it+1))));
    }
    res += computeDist(vertices.at(tour.at(0)), vertices.at(tour.at(tour.size()-1)));
    return res;
}
vector<int> greedy(vector<pair<double, double>> vertices, int startNode){
    
    //Init best distance
    int best;
    
    //Set start of tour to first node
    vector<int> tour;
    tour.clear();
    tour.push_back(startNode);
    bool used[vertices.size()];
    used[startNode] = true;
    
    //initialize tour and used
    for (int i = 0; i < vertices.size(); i++) {
        if(i != startNode){
            used[i] = false;
            tour.push_back(-1);
        }
    }
    for (int i = 1; i < vertices.size(); i++) {
        best = -1;
        
        for (int j = 0; j < vertices.size(); j++) {
            
            
            if (!used[j] && (best == -1 || (computeDist(vertices.at(tour.at(i-1)), vertices.at(j)) < computeDist(vertices.at(tour.at(i-1)), vertices.at(best))))) {
                best = j;
                
            }
        }
        tour.at(i) = best;
        used[best] = true;
    }
    return tour;
}
vector<int> minimizeGreedy(vector<pair<double, double>> vertices){
    
    vector<int> bestTour;
    int numberOfSamples = int(vertices.size());
    long bestLength = 129319872833351231;
    long tempLength;
    std::set<int> used;
    vector<int> tempTour;
    
    if(numberOfSamples > 200){
        numberOfSamples = 200;
    }
    for(int i = 0; i < numberOfSamples; i++){
        bool search = true;
        int startPoint = rand()%vertices.size();
        while(search){
            if(used.emplace(startPoint).second){
                search = false;
            }
            startPoint = rand()%vertices.size();
        }
        tempTour = greedy(vertices, rand()%vertices.size());
        tempLength = tourLength(tempTour, vertices);
        
        if(tempLength < bestLength){
            bestLength = tempLength;
            bestTour = tempTour;
            
        }
        
    }
    return bestTour;
}
