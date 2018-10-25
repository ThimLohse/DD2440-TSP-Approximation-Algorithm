#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class Graph {
private:
  int graphSize;
  vector<pair<int, vector<tuple<int, int>>>> nodeVector;

public:
  void addNode(int node);
  Graph(int size); // constructor
};

#endif // GRAPH_H
