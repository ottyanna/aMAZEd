#ifndef VERTEX_H
#define VERTEX_H // include guards

#include <boost/heap/binomial_heap.hpp>
#include <boost/heap/policies.hpp>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
using namespace boost::heap;

// struct CompareVertexPointersStruct;
struct Vertex;

struct CompareVertexPointersStruct {
  bool operator()(const Vertex *v1, const Vertex *v2) const;
};

using MinHeap = binomial_heap<Vertex *, compare<CompareVertexPointersStruct>>;

// functor to compare Vertex* as a min heap so the funct needs to invert the
// sign
// struct CompareVertexPointersStruct {
//  bool operator()(const Vertex *v1, const Vertex *v2) const; //{
//
//  //  return (v1->dist > v2->dist);
//  //}
//};

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
  VertexType type;
  Vertex *parent;

  // BFS attribute
  int dist; // for AStar is f
  int g;

  MinHeap::handle_type handle;

  // namespace std {
  // template <> struct less<Vertex *> {
  //  bool operator()(const Vertex *lhs, const Vertex *rhs) const {
  //    return lhs->dist < rhs->dist;
  //  }
  //};
  //} // namespace std

  Vertex(int _id, Color _color = WHITE, VertexType _type = NONE,
         Vertex *_parent = nullptr, int _dist = INF, int _g = INF) {
    id = _id;
    color = _color;
    type = _type;
    parent = _parent;
    dist = _dist;
    g = _g;
  }

  void print() const {
    cout << "id= " << id << " ";
    cout << "color= " << color << " ";
    cout << "type= " << type << " ";
    cout << "dist= " << dist << " ";
    cout << "g= " << g;
  }

  // bool operator<(Vertex const &rhs) const { return dist > rhs.dist; }
};

#endif