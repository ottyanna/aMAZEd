#ifndef VERTEX_H
#define VERTEX_H // include guards

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

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
  int heuristicLengthToFinish;

  // BFS attribute
  int dist;

  Vertex(int _id, Color _color = WHITE, VertexType _type = NONE,
         Vertex *_parent = nullptr, int _dist = INF,
         int _heuristicLengthToFinish = 0) {
    id = _id;
    color = _color;
    type = _type;
    parent = _parent;
    dist = _dist;
    heuristicLengthToFinish = _heuristicLengthToFinish;
  }

  void print() {
    cout << "id= " << id << " ";
    cout << "color= " << color << " ";
    cout << "type= " << type << " ";
    cout << "dist= " << dist;
  }
};

#endif