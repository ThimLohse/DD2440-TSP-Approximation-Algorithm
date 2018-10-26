#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm> // std::sort
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <set> // for set operations
#include <stdio.h>
#include <string>
#include <tuple>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Functions {
  // Class member functions definitions
public:
  //** Compute the euclidian distance between two nodes in the plane **/
  static double computeDist(pair<double, double> a, pair<double, double> b);

  //** Compute the length of a tour **/
  static int tourLength(vector<int> tour,
                        vector<pair<double, double>> vertices);

  //** Compute the greedy algorithm for shortest cycle from given startnode**/
  static vector<int> greedy(vector<pair<double, double>> vertices,
                            int startNode);

  //** Minimize the shortest cycle trying all or random set of startnodes **/
  static vector<int> minimizeGreedy(vector<pair<double, double>> vertices);

  //** 2opt functions for edge swapping optimization **/
  static vector<int> twoOpt(vector<int> path,
                            vector<pair<double, double>> vertices);
  static vector<int> twoOptUtil(vector<int> current_path, int i, int k,
                                bool debug = false);
};

#endif // FUNCTIONS_H
