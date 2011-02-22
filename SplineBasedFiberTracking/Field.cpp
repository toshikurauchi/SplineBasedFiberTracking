#include "pbge/gfx/SceneGraph.h"
#include "math3d/math3d.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

#include "Field.h"

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
                math3d::vector4 pos = *(vector.position);
                pbge::ModelInstance * vectorModel = vector.createVectorInstance();
                pbge::Node * vecPosNode = scene->appendChildTo(pbge::SceneGraph::ROOT, pbge::TransformationNode::translation(pos[0],pos[1],pos[2]));
                scene->appendChildTo(vecPosNode, vectorModel);
            }
        }
    }
}

void addIndices(std::vector<int> *indices, int f, int c) {
    if(f == c){
        indices->push_back(c);
    }
    else{
        indices->push_back(c);
        indices->push_back(f);
    }
}

math3d::vector4 * calculateMeanVec(std::vector<Vector> vectors, math3d::vector4 * pos) {
    float x_sum, y_sum, z_sum;
    x_sum = y_sum = z_sum = 0.0;

    for(std::vector<Vector>::iterator it = vectors.begin(); it < vectors.end(); it++){
        math3d::vector4 dist = math3d::Abs((*it->position) - *pos);
        x_sum += (*it->vector)[0] * (1 - dist[0]);
        y_sum += (*it->vector)[1] * (1 - dist[1]);
        z_sum += (*it->vector)[2] * (1 - dist[2]);
    }
    math3d::vector4 * meanVec = new math3d::vector4(x_sum, y_sum, z_sum);
    (*meanVec) /= (float)(vectors.size()/2);
    return meanVec;
}

Vector * Field::getInterpolatedVector(float x, float y, float z) {
    int x_f = static_cast<int>(floor(x));
    int y_f = static_cast<int>(floor(y));
    int z_f = static_cast<int>(floor(z));
    
    int x_c = static_cast<int>(ceil(x));
    int y_c = static_cast<int>(ceil(y));
    int z_c = static_cast<int>(ceil(z));

    std::vector<int> x_indices;
    std::vector<int> y_indices;
    std::vector<int> z_indices;
    addIndices(&x_indices, x_f, x_c);
    addIndices(&y_indices, y_f, y_c);
    addIndices(&z_indices, z_f, z_c);

    std::vector<Vector> vectors;
    for(std::vector<int>::iterator it_x = x_indices.begin(); it_x < x_indices.end(); it_x++){
        for(std::vector<int>::iterator it_y = y_indices.begin(); it_y < y_indices.end(); it_y++){
            for(std::vector<int>::iterator it_z = z_indices.begin(); it_z < z_indices.end(); it_z++){
                vectors.push_back(this->field[*it_x][*it_y][*it_z]);
            }
        }
    }

    math3d::vector4 * pos = new math3d::vector4((float)x, (float)y, (float)z);
    math3d::vector4 * vec = calculateMeanVec(vectors, pos);

    return new Vector(*pos, *vec);
}