//
//  main.cpp
//  Algorithm
//
//  Created by Thim Lohse on 2018-10-21.
//  Copyright © 2018 Thim Lohse. All rights reserved.
//

// Standard headers
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <chrono>
#include <math.h>
#include <limits.h>

// Custom headers
#include "func.hpp"

// run: make tsp_opt or make, then run: ./tsp < "input_file"
using namespace std;
using namespace std::chrono;

int main() {

  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // Initalize timer

  // Initalize line to read from std
  string line;

  // Check if we are reading first line --> number of nodes or coordinate pairs
  bool first = true;

  // Size type used to convert strings to numbers
  string::size_type sz; // alias of size_t

  // Number of nodes
  int numNodes = 0;

  // Counter to give each node an ID
  int id = 0;

  // Vector to hold the nodes
  vector<int> nodes;

  // Vector to hold the coordinates until distances are calculated
  vector<pair<double, double>> coordinates;

  // Vector matrix to hold the distances between nodes (Adjeceny matrix)
  vector<vector<double>> distances;

  // Vector to hold the calculated greedy tour
  vector<int> greedyTour;

  // Vector to hold the 2-opt tour
  vector<int> optTour;

  // Initalize the random generator used for calculating random possible
  // starting points for minimize greedy. Using current time of the device.
  srand((unsigned int)(time(NULL)));

  cin >> numNodes;

  // Read in all the vertices
  int id = 0;
  double x;
  double y;
  while (id < numNodes) {
    cin >> x;
    cin >> y;
    coordinates.push_back(make_pair(x, y));
    nodes.push_back(id);
    id++;
  }
  /*
  while (getline(cin, line)) {

    // Extract number of nodes
    if (first) {
      numNodes = stod(line, &sz);
      // reserve size for each vector to avoid time for allocating more space
      // during read in
      coordinates.reserve(numNodes);
      nodes.reserve(numNodes);
      first = false;
    }
    // Deconstruct line into (x,y)-coordinates
    else {
      double x = stod(line, &sz);
      double y = stod(line.substr(sz));
      coordinates.push_back(make_pair(x, y));
      nodes.push_back(id);
      id++;
    }
  }
  */
  distances = Functions::createDistMatrix(coordinates, numNodes);
  greedyTour = Functions::minimizeGreedy(distances);
  Functions::twoOpt(greedyTour, distances);
  for (int i : greedyTour) {
    cout << i << "\n";
  }
  return 0;
}
