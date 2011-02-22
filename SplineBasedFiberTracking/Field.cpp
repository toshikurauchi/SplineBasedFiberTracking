#include "pbge/gfx/SceneGraph.h"
#include "math3d/math3d.h"

#include <iostream>
#include <fstream>

#include "Field.h"
#include "Vector.h"

Field::Field(int x, int y, int z){
    this->x_axis = x;
    this->y_axis = y;
    this->z_axis = z;
    this->field = (Vector ***)malloc(sizeof(Vector**)*x);
    for(int i=0; i < x; i++){
        this->field[i] = (Vector **)malloc(sizeof(Vector*)*y);
        for(int j=0; j < y; j++){
            this->field[i][j] = (Vector *)malloc(sizeof(Vector)*z);
        }
    }
}

Field * Field::fromFile(std::string fileName, pbge::OpenGL * ogl){
    std::ifstream inputFile(fileName.c_str(), std::ifstream::in);
    
    int x_axis, y_axis, z_axis;
    inputFile >> x_axis;
    inputFile >> y_axis;
    inputFile >> z_axis;
    int numberOfVectors = x_axis * y_axis * z_axis;

    Field * f = new Field(x_axis,y_axis,z_axis);
    
    while(numberOfVectors--) {
        int pos_x, pos_y, pos_z;
        int vec_x, vec_y, vec_z;
        inputFile >> pos_x;
        inputFile >> pos_y;
        inputFile >> pos_z;
        inputFile >> vec_x;
        inputFile >> vec_y;
        inputFile >> vec_z;

        math3d::vector4 pos = math3d::vector4((float)pos_x,(float)pos_y,(float)pos_z);
        math3d::vector4 vec = math3d::vector4((float)vec_x,(float)vec_y,(float)vec_z);

        Vector vector(pos, vec, ogl);
            
        f->field[pos_x][pos_y][pos_z] = vector;
    }
    inputFile.close();

    return f;
}

void Field::insertIntoScene(pbge::SceneGraph *scene, pbge::OpenGL * ogl) {
    for(int i = 0; i < this->x_axis; i++) {
        for(int j = 0; j < this->y_axis; j++) {
            for(int k = 0; k < this->z_axis; k++) {
                Vector vector = this->field[i][j][k];
                math3d::vector4 * pos = vector.getPosition();
                pbge::ModelInstance * vectorModel = vector.createVectorInstance();
                pbge::Node * vecPosNode = scene->appendChildTo(pbge::SceneGraph::ROOT, pbge::TransformationNode::translation((*pos)[0],(*pos)[1],(*pos)[2]));
                scene->appendChildTo(vecPosNode, vectorModel);
            }
        }
    }
}