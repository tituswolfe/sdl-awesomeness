//
// Created by Titus Wolfe on 3/15/26.
//

#ifndef MY3DENGINE_VERTEX_H
#define MY3DENGINE_VERTEX_H
#include "../math/Vector.h"


class Vertex {
    Vector position;
    // Vector normal;

public:
    explicit Vertex(const Vector &position) : position(position) {};
};


#endif //MY3DENGINE_VERTEX_H