//
//  main.cpp
//  Algorithm
//
//  Created by Thim Lohse on 2018-10-21.
//  Copyright © 2018 Thim Lohse. All rights reserved.
//

// Standard headers
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

// Global variable numNodes;
int numNodes = 0;
// run: make tsp_opt or make, then run: ./tsp < "input_file"
using namespace std;
using namespace std::chrono;
int *greedyTour(double **distances, int startPoint) {
  int *tour = new int[numNodes];
  bool used[numNodes];
  int best = -1;
  tour[0] = startPoint;
  for (int i = 0; i < numNodes; i++) {
    if (i == startPoint) {
      used[i] = true;
    } else {
      used[i] = false;
    }
  }
  for (int i = 1; i < numNodes; i++) {
    best = -1;
    for (int j = 0; j < numNodes; j++) {
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
double distance(double **distances, int *tour) {
  double res = 0;
  for (int i = 0; i < numNodes - 1; i++) {
    res += distances[tour[i]][tour[i + 1]];
  }
  return res;
}
int main() {

  high_resolution_clock::time_point start_time = high_resolution_clock::now();
  int current_time;
  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  // Initalize timer

  // Counter to give each node an ID
  int id = 0;

  // Vector to hold the coordinates until distances are calculated
  vector<pair<double, double>> coordinates;

  cin >> numNodes;
  // Vector matrix to hold the distances between nodes (Adjeceny matrix)
  // int distances[numNodes * numNodes];

  // Vector to hold the calculated greedy tour
  int *currentTour;

  // Read in all the vertices
  double x;
  double y;
  bool isUsed;
  double bestDist = 2147483637;
  double currentDist;
  int startPoint;
  int *bestTour;

  while (id < numNodes) {
    cin >> x;
    cin >> y;
    coordinates.push_back(make_pair(x, y));
    id++;
  }

  // Generate distance matrix
  double *distances[numNodes];
  for (int i = 0; i < numNodes; i++) {
    distances[i] = new double[numNodes];
    for (int j = 0; j < numNodes; j++) {
      distances[i][j] =
          sqrt(pow(coordinates[i].first - coordinates[j].first, 2) +
               pow(coordinates[i].second - coordinates[j].second, 2));
    }
  }
  coordinates.clear();
  // point to first element of distances
  for (int i = 0; i < numNodes; i++) {
    currentTour = greedyTour(distances, i);

    currentDist = distance(distances, currentTour);
    if (currentDist < bestDist) {
      bestDist = currentDist;
      bestTour = currentTour;
    }
  }
  for (int i = 0; i < numNodes; i++) {
    cout << *bestTour << "\n";
    bestTour++;
  }

  /*
    for (int i = 0; i < numNodes && current_time < 1500000; ++i) {

      tempTour = Functions::greedy(distances, i);
      Functions::twoOpt(tempTour, distances);
      currentDist = Functions::tourLength(tempTour, distances);
      if (currentDist < bestDist) {
        bestTour = tempTour;
        bestDist = currentDist;
      }

      current_time =
          duration_cast<microseconds>(high_resolution_clock::now() -
    start_time) .count();
    }
    */

  /*
    cout << current_time << "\n";
    cout << Functions::tourLength(bestTour, distances) << "\n";
  */
  current_time =
      duration_cast<microseconds>(high_resolution_clock::now() - start_time)
          .count();
  cout << "time: " << current_time << " microseconds" << endl;
  cout << "time: " << (current_time / (pow(10, 6))) << " seconds" << endl;
  return 0;
}
