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
#include <iostream>
#include <stdio.h>
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

int *twoOpt(int *tour, double **distances,
            high_resolution_clock::time_point start_time);
int *twoHOpt(int *tour, double **distances,
             high_resolution_clock::time_point start_time);

int main() {

  // Initalize timer and standard input
  high_resolution_clock::time_point start_time = high_resolution_clock::now();
  int current_time;
  std::ios::sync_with_stdio(false);
  cin.tie(NULL);

  // Vector to hold the coordinates until distances are calculated
  vector<pair<double, double>> coordinates;

  cin >> numNodes;
  // Vector matrix to hold the distances between nodes (Adjeceny matrix)
  // int distances[numNodes * numNodes];
  coordinates.reserve(numNodes);

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

  while (cin >> x && cin >> y) {
    coordinates.push_back(make_pair(x, y));
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
  int limit = 1998805;
  // 1998805

  for (int i = 0; i < numNodes; i++) {
    current_time =
        duration_cast<microseconds>(high_resolution_clock::now() - start_time)
            .count();
    if (current_time >= limit) {
      break;
    }
    // currentTour = greedyTour(distances, i);
    currentTour = greedyTour(distances, rand() % numNodes);
    currentTour = twoOpt(currentTour, distances, start_time);
    // currentTour = twoHOpt(currentTour, distances, start_time);
    currentDist = distance(currentTour, distances);

    if (currentDist < bestDist) {
      bestDist = currentDist;
      bestTour = currentTour;
    }
  }
  for (int i = 0; i < numNodes; i++) {
    cout << bestTour[i] << "\n";
  }
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
  res += distances[tour[0]][tour[numNodes - 1]];
  return res;
}
// Two opt with swap and reverse in same function for efficiency
int *twoOpt(int *startTour, double **distances,
            high_resolution_clock::time_point start_time) {

  int *tour = startTour;
  bool isOptimal = false;
  int stopAfter;
  int A1, A2, B1, B2;
  do {
  improve:

    isOptimal = true;
    for (int i = 0; i < numNodes - 3; i++) {
      if (duration_cast<microseconds>(high_resolution_clock::now() - start_time)
              .count() > 1998805) {

        return tour;
      }
      // First node in first pair
      A1 = tour[i];
      // Consecutive node to first node in pair
      A2 = tour[(i + 1) % numNodes];

      stopAfter = (i == 0 ? numNodes - 2 : numNodes - 1);
      // stopAfter = numNodes - 1;
      for (int j = (i + 2); j < stopAfter; j++) {
        B1 = tour[j];
        B2 = tour[(j + 1) % numNodes];

        if (duration_cast<microseconds>(high_resolution_clock::now() -
                                        start_time)
                .count() > 1998805) {
          return tour;
        }
        // Check if swapping edges gives a decrease in length
        double currentLength = distances[A1][A2] + distances[B1][B2];
        double changedLength = distances[A1][B1] + distances[A2][B2];

        if ((currentLength - changedLength) > 0) {

          // Swap edges
          int _LEFT = i;
          int _RIGHT = j;
          int LEFT = ((_LEFT + 1) % numNodes);
          int RIGHT = _RIGHT;

          int numSwaps = ((numNodes + (RIGHT - LEFT) + 1) % numNodes) / 2;

          for (int swap = 0; swap < numSwaps; ++swap) {
            int temp = tour[LEFT];
            tour[LEFT] = tour[RIGHT];
            tour[RIGHT] = temp;
            LEFT = (LEFT + 1) % numNodes;
            RIGHT = (numNodes + RIGHT - 1) % numNodes;
          }

          isOptimal = false;
          // goto improve;
          // break;
        }
      }
    }
  } while (!isOptimal);
  return tour;
}
// Two opt with swap and reverse in same function for efficiency
int *twoHOpt(int *startTour, double **distances,
             high_resolution_clock::time_point start_time) {

  int *tour = startTour;

  bool isOptimal = false;
  int stopAfter;
  int A1, A2, B1, B2, SwapNode;

  double first_switch_dist = 0;
  double dA1B1, dA2B2, dA2B1 = 0;
  do {
  improve:

    isOptimal = true;
    for (int i = 0; i < numNodes - 3; i++) {
      if (duration_cast<microseconds>(high_resolution_clock::now() - start_time)
              .count() > 1998805) {
        return tour;
      }
      // First node in first pair
      A1 = tour[i];
      // Consecutive node to first node in pair
      A2 = tour[(i + 1) % numNodes];

      // stopAfter = (i == 0 ? numNodes - 2 : numNodes - 1);
      stopAfter = numNodes - 1;
      for (int j = (i + 2); j < stopAfter; j++) {
        B1 = tour[j];
        B2 = tour[(j + 1) % numNodes];

        if (duration_cast<microseconds>(high_resolution_clock::now() -
                                        start_time)
                .count() > 1998805) {
          return tour;
        }
        // Check if swapping edges gives a decrease in length
        double currentLength = distances[A1][A2] + distances[B1][B2];
        dA1B1 = distances[A1][B1];
        dA2B2 = distances[A2][B2];

        if ((currentLength - (dA1B1 + dA2B2)) > 0) {

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

          isOptimal = false;
          break;
          // goto improve;
        }

        else {
          dA2B1 = distances[A2][B1];
          SwapNode = tour[(i + 2) % numNodes];
          if (SwapNode != B1) {
            if (((currentLength + distances[A2][SwapNode]) -
                 (dA2B2 + dA2B1 + distances[A1][SwapNode])) > 0) {
              // Swap edges
              int _LEFT = ((i + 1) % numNodes);
              int _RIGHT = j;
              int LEFT = ((_LEFT + 1) % numNodes);
              int RIGHT = _RIGHT;
              int numSwaps = ((numNodes + (RIGHT - LEFT) + 1) % numNodes) / 2;

              for (int swap = 0; swap < numSwaps; ++swap) {
                int temp = tour[LEFT];
                tour[LEFT] = tour[RIGHT];
                tour[RIGHT] = temp;
                LEFT = (LEFT + 1) % numNodes;
                RIGHT = (numNodes + RIGHT - 1) % numNodes;
              }

              isOptimal = false;
              break;
            }
          } else {
            SwapNode = tour[(numNodes + j - 1) % numNodes];
            if (SwapNode != A2) {
              if (((currentLength + distances[B1][SwapNode]) -
                   (dA1B1 + dA2B1 + distances[B2][SwapNode])) > 0) {
                // Swap edges
                int _LEFT = j;
                int _RIGHT = i;
                int LEFT = ((_LEFT + 1) % numNodes);
                int RIGHT = _RIGHT;
                int numSwaps = ((numNodes + (RIGHT - LEFT) + 1) % numNodes) / 2;

                for (int swap = 0; swap < numSwaps; ++swap) {
                  int temp = tour[LEFT];
                  tour[LEFT] = tour[RIGHT];
                  tour[RIGHT] = temp;
                  LEFT = (LEFT + 1) % numNodes;
                  RIGHT = (numNodes + RIGHT - 1) % numNodes;
                }

                isOptimal = false;
                break;
              }
            }
          }
        }
      }
    }
  } while (!isOptimal);
  return tour;
}
