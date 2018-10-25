#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph {
private:
  int graphSize;
  // hashmap of neighbours (id, list of neighbours with (id, weight))
  unordered_map<int, vector<pair<int, double>>> edges;

  // vector of nodes (id, (x,y) coodrinates)
  vector<tuple<int, double, double>> nodes;

  unordered_map<int, vector<pair<int, double>>> mstEdges;

  vector<tuple<int, double, double>> mstNodes;

public:
  void createMST();
  void sortNeighbours();
  static bool weightComp(pair<int, double> a, pair<int, double> b);
  void setSize(int size);
  int getSize();
  void addFirst(int node, double x, double y);
  void addNode(int node, double x, double y);
  vector<tuple<int, double, double>> getNodes();
  unordered_map<int, vector<pair<int, double>>> getEdges();
  Graph(); // constructor
};

#endif // GRAPH_H
