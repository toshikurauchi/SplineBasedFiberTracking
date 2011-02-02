#ifndef SBFT_VECTOR
#define SBFT_VECTOR

#include "pbge/gfx/Model.h"
#include "math3d/math3d.h"

public class Vector {
public:
    Vector(math3d::vector4 position_, math3d::vector4 vector_) {
        position = position_;
        vector = vector_;
    }
    pbge::ModelInstance * createVectorInstance();
private:
    math3d::vector4 position;
    math3d::vector4 vector;
}

#endif