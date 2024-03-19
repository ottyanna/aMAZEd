#ifndef VERTEX_H
#define VERTEX_H // include guards

#include <boost/heap/binomial_heap.hpp>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
using namespace boost::heap;

struct Vertex;

struct CompareVertexPointersStruct {
  bool operator()(const Vertex *v1, const Vertex *v2) const;
};

// use CompareVertexPointersStruct to implement a minHeap and not a maxHeap
using MinHeap = binomial_heap<Vertex *, compare<CompareVertexPointersStruct>>;

enum { INF = numeric_limits<int>::max() };

enum Color { WHITE, GREY, BLACK };

enum VertexType {
  START = 3,
  NONE = 4,
  FINISH = 5,
  PATH = 6
}; // to distinguish them from the colors that are 0,1,2

struct Vertex {

  int id;

  Color color;

  // Solving attributes
  VertexType type;
  Vertex *parent;
  int f; // for BFS and Dijkstra read as distance field
  int g;

  MinHeap::handle_type handle;

  Vertex(int _id, Color _color = WHITE, VertexType _type = NONE,
         Vertex *_parent = nullptr, int _f = INF, int _g = INF) {
    id = _id;
    color = _color;
    type = _type;
    parent = _parent;
    f = _f;
    g = _g;
  }

  void print() const {
    cout << "id= " << id << " ";
    cout << "color= " << color << " ";
    cout << "type= " << type << " ";
    cout << "f= " << f << " ";
    cout << "g= " << g;
  }
};

#endif