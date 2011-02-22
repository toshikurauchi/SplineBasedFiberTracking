#ifndef SBFT_VECTOR
#define SBFT_VECTOR

#include "pbge/gfx/Model.h"
#include "math3d/math3d.h"

class Vector {
public:
    Vector(const math3d::vector4 & position_, const math3d::vector4 & vector_, pbge::OpenGL * ogl_) {
        position = new math3d::vector4(position_);
        vector = new math3d::vector4(vector_);
        ogl = ogl_;
    }
    pbge::ModelInstance * createVectorInstance();
    math3d::vector4 * getPosition() {return this->position;}
private:
    math3d::vector4 * position;
    math3d::vector4 * vector;
    pbge::OpenGL * ogl;
};

#endif