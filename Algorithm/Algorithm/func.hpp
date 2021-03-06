#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm> // std::sort
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <set> // for set operations
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

class Functions {
  // Class member functions definitions
public:
  //** Compute the euclidian distance between two nodes in the plane **/
  static int computeDist(pair<double, double> a, pair<double, double> b);

  //** Compute the length of a tour **/
  static int tourLength(vector<int> tour,
                        vector<pair<double, double>> vertices);

  //** Compute the greedy algorithm for shortest cycle from given startnode**/
  static vector<int> greedy(vector<pair<double, double>> vertices,
                            int startNode);

  //** Minimize the shortest cycle trying all or random set of startnodes **/
  static vector<int> minimizeGreedy(vector<pair<double, double>> vertices);
};

#endif // FUNCTIONS_H
