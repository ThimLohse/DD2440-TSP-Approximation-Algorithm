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

// Calculate the total distance of a tour
double distance(int *tour, double **distances);
// Calculate the greedy tour
int *greedyTour(double **distances, int startPoint);

double improvedBy(int A1, int A2, int B1, int B2, double **distances);
int *swapEdges(int *tour, int i, int j);
int *twoOpt(int *tour, double **distances,
            high_resolution_clock::time_point start_time);

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
  double bestDist = __DBL_MAX__;
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

  srand((unsigned long)(time(NULL)));
  int limit = 1995000;
  int limit2 = 500000;

  for (int i = 0; i < numNodes; i++) {
    if (current_time >= limit2) {
      break;
    }
    currentTour = greedyTour(distances, i);
    currentDist = distance(currentTour, distances);
    if (currentDist < bestDist) {
      bestDist = currentDist;
      bestTour = currentTour;
    }
    current_time =
        duration_cast<microseconds>(high_resolution_clock::now() - start_time)
            .count();
  }
  currentTour = twoOpt(bestTour, distances, start_time);
  for (int i = 0; i < numNodes; i++) {
    cout << currentTour[i] << "\n";
  }
  /*
  for (int i = 0; i < numNodes; i++) {
    if (current_time >= limit) {
      break;
    }

    currentTour = greedyTour(distances, rand() % numNodes);
    currentTour = twoOpt(currentTour, distances, start_time);
    currentDist = distance(currentTour, distances);

    if (currentDist < bestDist) {
      bestDist = currentDist;
      bestTour = currentTour;
    }
    current_time =
        duration_cast<microseconds>(high_resolution_clock::now() - start_time)
            .count();
  }
  for (int i = 0; i < numNodes; i++) {
    cout << bestTour[i] << "\n";
  }
  */
  /*
    current_time =
        duration_cast<microseconds>(high_resolution_clock::now() - start_time)
            .count();

    cout << "time: " << current_time << " microseconds"
         << "\n";

    cout << "time: " << (current_time / (pow(10, 6))) << " seconds"
         << "\n";
    cout << "Best distance: " << distance(bestTour, distances) << "\n";
  */
  return 0;
}

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
double distance(int *tour, double **distances) {
  double res = 0;
  for (int i = 0; i < numNodes - 1; i++) {
    res += distances[tour[i]][tour[i + 1]];
  }
  return res;
}
int *swapEdges(int *tour, int i, int j) {
  int *newTour = new int[numNodes];
  /*
  1. take route[0] to route[i - 1] and add them in order to new_route
  2. take route[i] to route[k] and add them in reverse order to new_route
  3. take route[k + 1] to end and add them in order to new_route
  */
  /*
    for (int k = 0; k < i; k++) {
      newTour[k] = tour[k];
    }
    int decrement = 0;
    for (int k = i; k <= j; k++) {
      newTour[k] = tour[j - decrement];
      decrement++;
    }
    for (int k = j + 1; k < numNodes; k++) {
      newTour[k] = tour[k];
    }
  */

  int LEFT = ((i + 1) % numNodes);
  int RIGHT = j;
  int numSwaps = ((numNodes + (RIGHT - LEFT) + 1) % numNodes) / 2;

  for (int swap = 0; swap < numSwaps; ++swap) {
    int temp = tour[LEFT];
    tour[LEFT] = tour[RIGHT];
    tour[RIGHT] = temp;
    LEFT = (LEFT + 1) % numNodes;
    RIGHT = (numNodes + RIGHT - 1) % numNodes;
  }

  return tour;
}
// Check if an improvement is possible if chaning the edges between two pairs of
// nodes.
double improvedBy(int A1, int A2, int B1, int B2, double **distances) {
  // We assume that A1-A2 and B1-B2
  double currentLength = distances[A1][A2] + distances[B1][B2];
  double changedLength = distances[A1][B1] + distances[A2][B2];

  // If changed length is shorter we will return the distance gain as positive,
  // otherwise negative
  return (currentLength - changedLength);
}
// Two opt with swap and reverse in same function for efficiency
int *twoOpt(int *startTour, double **distances,
            high_resolution_clock::time_point start_time) {

  int best_i;
  int best_j;
  double best_improvement = __DBL_MAX__;
  double current_improvement = distance(startTour, distances);
  int *tour = startTour;
  int *globalBest = startTour;

  bool isOptimal = false;
  int stopAfter;
  int A1, A2, B1, B2;
  do {
  improve:

    isOptimal = true;
    for (int i = 0; i < numNodes - 3; i++) {
      // First node in first pair
      A1 = tour[i];
      // Consecutive node to first node in pair
      A2 = tour[(i + 1) % numNodes];

      stopAfter = (i == 0 ? numNodes - 2 : numNodes - 1);
      for (int j = (i + 2); j < stopAfter; j++) {

        B1 = tour[j];
        B2 = tour[(j + 1) % numNodes];

        if (duration_cast<microseconds>(high_resolution_clock::now() -
                                        start_time)
                .count() > 1995000) {
          return tour;
        }
        // Check if swapping edges gives a decrease in length
        double currentLength = distances[A1][A2] + distances[B1][B2];
        double changedLength = distances[A1][B1] + distances[A2][B2];

        if ((currentLength - changedLength) > 1) {
          // tour = swapEdges(tour, i, j);

          // Swap edges
          int LEFT = ((i + 1) % numNodes);
          int RIGHT = j;
          int numSwaps = ((numNodes + (RIGHT - LEFT) + 1) % numNodes) / 2;

          for (int swap = 0; swap < numSwaps; ++swap) {
            int temp = tour[LEFT];
            tour[LEFT] = tour[RIGHT];
            tour[RIGHT] = temp;
            LEFT = (LEFT + 1) % numNodes;
            RIGHT = (numNodes + RIGHT - 1) % numNodes;
          }

          // current_improvement = distance(tour, distances);
          /*
          if (current_improvement < best_improvement) {

            best_improvement = current_improvement;
            globalBest = tour;
          }
          */
          isOptimal = false;
          goto improve;
        }
      }
    }
  } while (!isOptimal);
  return tour;
}
