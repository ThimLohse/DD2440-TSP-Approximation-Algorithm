#include "func.hpp"
#include "graph.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

Graph::Graph() {
  // Constructor
  // cout << "New Graph Constructed!" << endl;
}

// Prims Algorithm
void Graph::createMST() {
  set<int> used;
  int index = 0;
  try {
    // Start with any node
    mstNodes.push_back(nodes.at(0));
    used.insert(0);
    mstEdges[0];

    // We should only add edges after we have found the nearest node outside of
    // the cut!
    mstEdges.at(0).insert(mstEdges.at(0).end(), edges.at(0).begin(),
                          edges.at(0).end());

    // Add nodes that has the minimum weight out of the cut
    for (auto it = mstEdges.at(index).begin(); it != mstEdges.at(index).end();
         ++it) {
      if (used.emplace(get<0>(*it)).second) {
        mstNodes.push_back(nodes.at(get<0>(*it)));

        index = 0;

      } else {
        index++;
      }
      // MST can't have more nodes than the nodes in the graph so we can finish
      // early
      if (mstNodes.size() == graphSize) {
        break;
      }
    }

  } catch (exception &exc) {
    cerr << exc.what() << endl;
  }
}
void Graph::setSize(int size) {

  // Set number of nodes in graph
  graphSize = size;

  // Reserve capacity (pre-allocate memory) for nodes vector for faster insert
  nodes.reserve(size);

  // Initalize edges structure
  edges.reserve(size);
}
int Graph::getSize() { return graphSize; }
bool Graph::weightComp(pair<int, double> a, pair<int, double> b) {
  return (get<1>(a) < get<1>(b));
}
void Graph::sortNeighbours() {
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    sort(edges.at(get<0>(*it)).begin(), edges.at(get<0>(*it)).end(),
         weightComp);
  }
}

void Graph::addFirst(int id, double x, double y) {
  nodes.push_back(make_tuple(id, x, y));
  edges[id];
}
void Graph::addNode(int id, double x, double y) {
  edges[id];
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {

    // Extract pairs (TODO: this can be inside the function call to compute dist
    // to save memory, but will be messy)
    pair<double, double> a = make_pair(get<1>(*it), get<2>(*it));
    pair<double, double> b = make_pair(x, y);

    // Add new neighbour to adjecencylist both of new node and nodes already
    // represented in graph.
    edges.at(get<0>(*it))
        .push_back(make_pair(id, Functions::computeDist(a, b)));
    edges.at(id).push_back(
        make_pair(get<0>(*it), Functions::computeDist(a, b)));
  }
  nodes.push_back(make_tuple(id, x, y));
}
vector<tuple<int, double, double>> Graph::getNodes() { return nodes; }
unordered_map<int, vector<pair<int, double>>> Graph::getEdges() {
  return edges;
}
