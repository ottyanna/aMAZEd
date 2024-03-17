#include "vertex.h"

bool CompareVertexPointersStruct::operator()(const Vertex *v1,
                                             const Vertex *v2) const {
  return (v1->dist > v2->dist);
}