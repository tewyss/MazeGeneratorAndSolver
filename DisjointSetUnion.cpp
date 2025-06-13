#include "DisjointSetUnion.h"

DisjointSetUnion::DisjointSetUnion(int size) : parent(size), rank(size, 0) {
  for (int i = 0; i < size; ++i) {
    parent[i] = i;
  }
}
void DisjointSetUnion::makeSet(int vertex) {
  parent[vertex] = vertex;
  rank[vertex] = 0;
}

int DisjointSetUnion::findSet(int vertex) {
  if (vertex not_eq parent[vertex]) {
    parent[vertex] = findSet(parent[vertex]);
  }
  return parent[vertex];
}

void DisjointSetUnion::unionSets(int a, int b) {
  a = findSet(a);
  b = findSet(b);
  if (a not_eq b) {
    if (rank[a] < rank[b]) {
      std::swap(a, b);
    }
    parent[b] = a;
    if (rank[a] == rank[b]) {
      ++rank[a];
    }
  }
}