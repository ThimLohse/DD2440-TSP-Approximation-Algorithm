// Standard headers
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

// Global variable numNodesT;
int numNodesT = 0;
// run: make tsp_opt or make, then run: ./tsp < "input_file"
using namespace std;
using namespace std::chrono;

int *swapEdges(int *tour, int i, int j);

int main(void) {

  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> numNodesT;

  return 0;
}

int *swapEdges(int *tour, int i, int j) {

  int *newTour = new int[numNodesT];
  /*
  1. take route[0] to route[i - 1] and add them in order to new_route
  2. take route[i] to route[k] and add them in reverse order to new_route
  3. take route[k + 1] to end and add them in order to new_route
  */

  int LEFT = ((i + 1) % numNodesT);
  int RIGHT = j;
  int numSwaps = ((numNodesT + (RIGHT - LEFT) + 1) % numNodesT) / 2;

  for (int swap = 0; swap < numSwaps; swap++) {
    int temp = tour[LEFT];
    tour[LEFT] = tour[RIGHT];
    LEFT = (LEFT + 1) % numNodesT;
    RIGHT = (numNodesT + RIGHT - 1) % numNodesT;

    temp = tour[LEFT];

    tour[LEFT] = tour[RIGHT];
    tour[RIGHT] = temp;
    LEFT = (LEFT + 1) % numNodesT;
    RIGHT = (numNodesT + RIGHT - 1) % numNodesT;
  }

  return newTour;
}
