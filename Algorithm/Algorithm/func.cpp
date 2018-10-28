//
//  func.cpp
//  Algorithm
//
//  Created by Thim Lohse on 2018-10-21.
//  Copyright © 2018 Thim Lohse. All rights reserved.
//

#include <algorithm> // std::sort
#include <cmath>
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

#include "func.hpp"

using namespace std;

double Functions::computeDist(pair<double, double> a, pair<double, double> b) {
  // Euclidian distance rounded to nearest integer
  //-> sqrt( [x1 - x2]^2 + [y1 - y2]^2 )
  return double(
      sqrt(pow(a.first - b.first, 2.0) + pow(a.second - b.second, 2.0)));
}
double Functions::tourLength(vector<int> tour,
                             vector<pair<double, double>> vertices) {
  int res = 0;
  for (auto it = tour.begin(); it != tour.end() - 1; it++) {
    res += computeDist(vertices.at((*it)), vertices.at((*(it + 1))));
  }
  res += computeDist(vertices.at(tour.at(0)),
                     vertices.at(tour.at(tour.size() - 1)));
  return res;
}

vector<int> Functions::twoOpt(vector<int> path,
                              vector<pair<double, double>> vertices) {

  // Todo: Determine how long this can be done on larger graph before time runs
  // out.
  clock_t start;
  start = clock();
  clock_t end;
  float diff;
  vector<int> new_path;
  vector<int> best_path = path;
  double best_dist;
  double new_dist;
  srand(time(NULL));

  int ELIGABLE_NODES = best_path.size();
/*
  if (ELIGABLE_NODES > 150) {
    ELIGABLE_NODES = 150;
  }
  */

// Repeat until no improvement (Implementation of wikipedia pseudocode)
// url: (https://en.wikipedia.org/wiki/2-opt)
swapping:

  best_dist = tourLength(best_path, vertices);
  for (int i = 0; i < ELIGABLE_NODES - 2; i++) {
    for (int k = (i + 2); k < ELIGABLE_NODES - 1; k++) {
      new_path = twoOptUtil(best_path, i, k);
      new_dist = tourLength(new_path, vertices);
      end = clock() - start;
      diff = (((float)end) / CLOCKS_PER_SEC);
      if (diff >= float(1.8)) {

        return best_path;
      }
      if (new_dist < best_dist) {
        cout << "Best Dist: " << new_dist << endl;
        best_path = new_path;
        goto swapping;
      }
    }
  }
  goto swapping;

  return best_path;
}
vector<int> Functions::twoOptUtil(vector<int> current_path, int i, int k,
                                  bool debug) {

  // TODO: improve reversal and use reference to current_path to avoid creating
  // new temporary vectors all the time.
  int switch_element = k;

  for (auto it = (current_path.begin() + i); it != (current_path.begin() + k);
       ++it) {
    iter_swap(it, (current_path.begin() + switch_element));
    switch_element--;
  }

  return current_path;
}
vector<int> Functions::greedy(vector<pair<double, double>> vertices,
                              int startNode) {

  // Init best distance
  int best;

  // Set start of tour to first node
  vector<int> tour;
  tour.clear();
  tour.push_back(startNode);
  bool used[vertices.size()];
  used[startNode] = true;

  // initialize tour and used
  for (int i = 0; i < vertices.size(); i++) {
    if (i != startNode) {
      used[i] = false;
      tour.push_back(-1);
    }
  }
  for (int i = 1; i < vertices.size(); i++) {
    best = -1;

    for (int j = 0; j < vertices.size(); j++) {

      if (!used[j] &&
          (best == -1 ||
           (computeDist(vertices.at(tour.at(i - 1)), vertices.at(j)) <
            computeDist(vertices.at(tour.at(i - 1)), vertices.at(best))))) {
        best = j;
      }
    }
    tour.at(i) = best;
    used[best] = true;
  }
  return tour;
}
vector<int> Functions::minimizeGreedy(vector<pair<double, double>> vertices) {

  vector<int> bestTour;
  int numberOfSamples = int(vertices.size());
  double bestLength = 129319872833351231;
  double tempLength;
  std::set<int> used;
  vector<int> tempTour;
  int SAMPLE_MAX = 100;

  if (numberOfSamples > SAMPLE_MAX) {
    numberOfSamples = SAMPLE_MAX;
  }
  for (int i = 0; i < numberOfSamples; i++) {
    bool search = true;
    int startPoint;
    if (numberOfSamples <= SAMPLE_MAX) {
      startPoint = i;
    } else {
      startPoint = rand() % (vertices.size() - 1);
      while (search) {
        if (used.emplace(startPoint).second) {
          search = false;
        }
        startPoint = rand() % (vertices.size() - 1);
      }
    }
    tempTour = greedy(vertices, rand() % vertices.size());
    tempLength = tourLength(tempTour, vertices);

    if (tempLength < bestLength) {
      bestLength = tempLength;
      bestTour = tempTour;
    }
  }
  return bestTour;
}
