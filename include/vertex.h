#ifndef VERTEX_H
#define VERTEX_H // include guards

#include <iostream>
#include <vector>

using namespace std;

enum Color { WHITE, GREY, BLACK };
enum VertexType {
  START = 3,
  NONE = 4,
  FINISH = 5
}; // to distinguish them from the colors that are 0,1,2

struct Vertex {

  int id;
  Color color;
  VertexType type;

  Vertex(int _id, Color _color = WHITE, VertexType _type = NONE) {
    id = _id;
    color = _color;
    type = _type;
  }

  void print() {
    cout << "id=" << id << " ";
    cout << "color=" << color << " ";
    cout << "type=" << type << " ";
  }
};

#endif