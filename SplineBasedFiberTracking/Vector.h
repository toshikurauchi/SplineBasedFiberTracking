#ifndef SBFT_VECTOR
#define SBFT_VECTOR

#include "pbge/gfx/Model.h"
#include "math3d/math3d.h"

class Vector {
public:
    Vector(const math3d::vector4 & position_, const math3d::vector4 & vector_) {
        position = new math3d::vector4(position_);
        vector = new math3d::vector4(vector_);
    }
    pbge::ModelInstance * createVectorInstance();
private:
    math3d::vector4 * position;
    math3d::vector4 * vector;
};

#endif