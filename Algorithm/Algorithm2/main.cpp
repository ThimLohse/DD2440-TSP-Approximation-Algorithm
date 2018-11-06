//
//  main.cpp
//  Algorithm
//
//  Created by Thim Lohse on 2018-10-21.
//  Copyright © 2018 Thim Lohse. All rights reserved.
//

// Standard headers
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

// Custom headers
#include "func.hpp"

// run: make tsp_opt or make, then run: ./tsp < "input_file"
using namespace std;
using namespace std::chrono;

int main(void) {

  high_resolution_clock::time_point start_time = high_resolution_clock::now();
  int current_time;
  std::ios::sync_with_stdio(false);
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
  double x;
  double y;
  set<int> used;
  bool isUsed;
  double bestDist = 2147483637;
  double currentDist;
  int startPoint;
  vector<int> tempTour;
  vector<int> bestTour;
  while (id < numNodes) {
    cin >> x;
    cin >> y;
    coordinates.push_back(make_pair(x, y));
    nodes.push_back(id);
    id++;
  }

  // Generate distance matrix
  distances = Functions::createDistMatrix(coordinates, numNodes);
  for (int i = 0; i < numNodes && current_time < 1500000; i++) {
    isUsed = true;
    /*
    do {

      startPoint = rand() % (numNodes - 1);
      if (used.emplace(startPoint).second) {
        isUsed = false;
      }
    } while (isUsed);
    */
    // startPoint = rand() % (numNodes - 1);
    tempTour = Functions::greedy(distances, i);
    Functions::twoOpt(tempTour, distances);
    currentDist = Functions::tourLength(tempTour, distances);
    if (currentDist < bestDist) {
      bestTour = tempTour;
      bestDist = currentDist;
    }
    current_time =
        duration_cast<microseconds>(high_resolution_clock::now() - start_time)
            .count();
  }
  /*
  greedyTour = Functions::minimizeGreedy(distances);
  Functions::twoOpt(greedyTour, distances);
  */
  for (int i : bestTour) {
    cout << i << "\n";
  }
  /*
    cout << current_time << "\n";
    cout << Functions::tourLength(bestTour, distances) << "\n";
  */
  return 0;
}
