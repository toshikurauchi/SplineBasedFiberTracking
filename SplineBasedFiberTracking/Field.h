#ifndef field_h
#define field_h

#include "pbge/gfx/SceneGraph.h"

#include <string>
#include <iterator>

#include "Vector.h"

class Field
{
public:
    static Field * fromFile(std::string fileName, pbge::OpenGL * ogl);
    void insertIntoScene(pbge::SceneGraph *scene, pbge::OpenGL * ogl);
private:
    Field(int x, int y, int z);
    Vector ***field;
    int x_axis;
    int y_axis;
    int z_axis;
};

#endif