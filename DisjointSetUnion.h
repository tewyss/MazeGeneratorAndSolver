#pragma once
#include <vector>

class DisjointSetUnion {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DisjointSetUnion(int size);
  void makeSet(int vertex);
  int findSet(int vertex);
  void unionSets(int a, int b);
};