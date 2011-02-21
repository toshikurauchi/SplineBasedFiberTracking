#include "Vector.h"
#include "pbge/gfx/VBO.h"
#include "pbge/gfx/Model.h"
#include "math3d/math3d.h"


void createIndices(std::vector<unsigned short> & i) {
    unsigned short indices[] = {0,1};
    i = std::vector<unsigned short>(indices, indices + 8);
}

pbge::ModelInstance * Vector::createVectorInstance() {
    pbge::VertexBufferBuilder builder(2);
    pbge::VertexAttribBuilder vertex = builder.addAttrib(3, pbge::VertexAttrib::VERTEX);
    pbge::VertexAttribBuilder color = builder.addAttrib(3, pbge::VertexAttrib::COLOR);
    
    std::vector<unsigned short> indices;
    createIndices(indices);

    builder.on(vertex)
            .pushValue(0,0,0)
            .pushValue((*vector)[0],(*vector)[1],(*vector)[2]).setAttribIndex(indices);
    builder.on(color)
            .pushValue(0,1,0)
            .pushValue(0,1,0).setAttribIndex(indices);

    pbge::VertexBuffer * vbo = builder.done(GL_STATIC_DRAW, this->ogl);
    return new pbge::ModelInstance(new pbge::VBOModel(vbo, GL_LINES));
}