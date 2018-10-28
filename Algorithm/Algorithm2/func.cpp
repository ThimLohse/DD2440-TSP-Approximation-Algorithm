//
//  func.cpp
//
//  Created by Thim Lohse on 2018-10-28.
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
#include <vector>

#include "func.hpp"

using namespace std;

// Return the euclidian distance between two coordinates
double Functions::distance(pair<double, double> a, pair<double, double> b) {
  return sqrt(pow((a.first - b.first), 2.0) + pow((a.second - b.second), 2.0));
}

// Calculate the distance matrix to avoid recalculations when performing tour
// optimization
vector<vector<double>>
Functions::createDistMatrix(vector<pair<double, double>> coordinates,
                            int numNodes) {
  vector<vector<double>> distances(numNodes, vector<double>(numNodes));

  for (int i = 0; i < coordinates.size(); i++) {
    for (int j = 0; j < coordinates.size(); j++) {
      distances[i][j] = distance(coordinates[i], coordinates[j]);
      distances[j][i] = distance(coordinates[i], coordinates[j]);
    }
  }
  return distances;
}

// Calculate the distance of a tour
double Functions::tourLength(vector<int> tour,
                             vector<vector<double>> distances) {
  int res = 0;
  for (int i = 0; i < distances.size() - 1; i++) {
    // Add the distance between each node in the tour
    res += distances[tour[i]][tour[i + 1]];
  }
  // Add the last distance to from first node to last node in tour to create
  // cycle
  res += distances[tour[tour.size() - 1]][tour[0]];
  return res;
}

// Generate a greedy tour
vector<int> Functions::greedy(vector<vector<double>> distances, int startNode) {

  // Init best distance
  int best;
  // Set start of tour to first node
  vector<int> tour;
  tour.clear();
  tour.push_back(startNode);
  bool used[distances.size()];
  used[startNode] = true;

  // initialize tour and used
  for (int i = 0; i < distances.size(); i++) {
    if (i != startNode) {
      used[i] = false;
      tour.push_back(-1);
    }
  }
  for (int i = 1; i < distances.size(); i++) {
    best = -1;
    for (int j = 0; j < distances.size(); j++) {

      if (!used[j] && (best == -1 || distances[tour[i - 1]][j] <
                                         distances[tour[i - 1]][best])) {
        best = j;
      }
    }
    tour[i] = best;
    used[best] = true;
  }
  return tour;
}

// Generate multiple greedy tours and return the shortest
vector<int> Functions::minimizeGreedy(vector<vector<double>> distances) {

  clock_t t;
  float end;
  t = clock();
  float limit = float(0.5);

  set<int> used;
  double bestLength = 2147483637;
  double tempLength;
  vector<int> bestTour;
  vector<int> tempTour;
  int numNodes = int(distances.size());
  int startPoint;
  bool isUsed;
  int NODE_MAX = 50;

  // If small number of nodes, calculate all possible greedy tours
  if (numNodes <= NODE_MAX) {
    for (int i = 0; i < numNodes; i++) {
      startPoint = i;
      tempTour = greedy(distances, startPoint);
      tempLength = tourLength(tempTour, distances);
      if (tempLength < bestLength) {
        bestLength = tempLength;
        bestTour = tempTour;
      }
    }
  }
  // Else randomly select startPoint without replacement and calculate greedy
  // tour
  else {
    for (int i = 0; i < NODE_MAX; i++) {

      isUsed = true;
      do {
        startPoint = rand() % (numNodes - 1);
        if (used.emplace(startPoint).second) {
          isUsed = false;
        }
      } while (isUsed);

      tempTour = greedy(distances, startPoint);
      tempLength = tourLength(tempTour, distances);
      if (tempLength < bestLength) {
        bestLength = tempLength;
        bestTour = tempTour;
      }
    }
  }
  return bestTour;
}

void Functions::twoOpt(vector<int> &tour, vector<vector<double>> distances) {

  clock_t start;
  start = clock();
  float limit = float(1.5);

  bool isOptimal = false;
  int tourLen = tour.size();
  int stopAfter;
  int A1, A2, B1, B2;
  do {
  improve:
    isOptimal = true;
    for (int i = 0; i < tourLen - 3; i++) {

      // First node in first pair
      A1 = tour[i];
      // Consecutive node to first node in pair
      A2 = tour[(i + 1) % tourLen];

      stopAfter = (i == 0 ? tourLen - 2 : tourLen - 1);
      for (int j = (i + 2); j < stopAfter; j++) {

        // Abort if too much time has passed
        float time_passed = (float(clock() - start) / CLOCKS_PER_SEC);
        if (time_passed >= limit) {
          // printf("time: %f\n", time_passed);
          goto abort;
        }

        B1 = tour[j];
        B2 = tour[(j + 1) % tourLen];
        // Check if swapping edges gives a decrease in length
        if (improvedBy(A1, A2, B1, B2, distances) > 0) {
          swapEdges(tour, i, j, tourLen);
          isOptimal = false;
          goto improve;
        }
      }
    }
  } while (!isOptimal);

abort:
  return;
}
// Check if an improvement is possible if chaning the edges between two pairs of
// nodes.
double Functions::improvedBy(int A1, int A2, int B1, int B2,
                             vector<vector<double>> distances) {
  // We assume that A1-A2 and B1-B2
  double currentLength = distances[A1][A2] + distances[B1][B2];
  double changedLength = distances[A1][B1] + distances[A2][B2];

  // If changed length is shorter we will return the distance gain as positive,
  // otherwise negative
  return (currentLength - changedLength);
}
void Functions::swapEdges(vector<int> &tour, int i, int j, int tourLen) {

  int LEFT = ((i + 1) % tourLen);
  int RIGHT = j;
  int numSwaps = ((tourLen + (RIGHT - LEFT) + 1) % tourLen) / 2;

  for (int swap = 0; swap < numSwaps; swap++) {
    int temp = tour[LEFT];
    tour[LEFT] = tour[RIGHT];
    tour[RIGHT] = temp;
    LEFT = (LEFT + 1) % tourLen;
    RIGHT = (tourLen + RIGHT - 1) % tourLen;
  }
}
