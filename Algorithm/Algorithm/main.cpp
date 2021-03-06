//
//  main.cpp
//  Algorithm
//
//  Created by Thim Lohse on 2018-10-21.
//  Copyright © 2018 Thim Lohse. All rights reserved.
//

// Standard headers
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

// Custom headers
#include "func.hpp"

using namespace std;

int main() {

  // test command in terminal for c++11 features
  // g++ -std=c++11 -stdlib=libc++ -Wno-c++98-compat main.cpp func.cpp func.hpp
  // ./a.out < tsp.in

  //** The line we read from std **/
  string line;

  /** Checking if we are reading number of nodes or coordinate pair **/
  bool first = true;

  //** Counter of number of nodes **/
  int numNodes = 0;

  //** Size class used to convert strings to numbers **/
  string::size_type sz; // alias of size_t

  //** Vector to hold coordinate pairs **/
  vector<pair<double, double>> vertices;

  //** Vector to hold the calculated tour **/
  vector<int> greedyTour;

  //** Id of each node pair on input. Needed for graph construction later on **/
  int id = 0;

  //** Initialize the random generator used for calculating random possible
  // starting points for MinimizeGreedy **/
  srand((unsigned int)(time(NULL)));

  //** Read in all the vertices **/
  while (getline(cin, line)) {

    //** Extract number of nodes **/
    if (first) {
      numNodes = std::stod(line, &sz);
      first = false;
    }
    //** Deconstruct each consecutive line into (x,y)-coordinates and store in
    // vector
    else {
      double x = std::stod(line, &sz);
      double y = std::stod(line.substr(sz));
      vertices.push_back(make_pair(x, y));
      id++;
    }
  }

  //** Calculate greedy tour **/
  greedyTour = Functions::minimizeGreedy(vertices);

  for (int i : greedyTour) {
    cout << i << endl;
  }

  //** Output length of greedy tour **/
  // cout << tourLength(greedyTour, vertices) << endl;

  return 0;
}
