//
//  func.cpp
//
//  Created by Thim Lohse on 2018-10-28.
//  Copyright © 2018 Thim Lohse. All rights reserved.
//
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm> // std::sort
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
  static double distance(pair<double, double> from, pair<double, double> to);
  static vector<vector<double>>
  createDistMatrix(vector<pair<double, double>> coordinates, int numNodes);
  static vector<int> greedy(vector<vector<double>> distances, int startNode);
  static vector<int> minimizeGreedy(vector<vector<double>> distances);
  static double tourLength(vector<int> tour, vector<vector<double>> distances);
};

#endif // FUNCTIONS_H
