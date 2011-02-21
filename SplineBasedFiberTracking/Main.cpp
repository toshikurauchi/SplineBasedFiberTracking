

#include <iostream>
#include <fstream>

#include "pbge/core/Manager.h"
#include "pbge/gfx/Light.h"
#include "pbge/gfx/Buffer.h"
#include "pbge/gfx/SceneGraph.h"
#include "pbge/gfx/Node.h"
#include "pbge/gfx/Renderer.h"
#include "pbge/gfx/StateSet.h"
#include "pbge/gfx/SceneInitializer.h"

#include <GL/glut.h>

#include "Vector.h"
#include "FieldGenerator.h"

int cam_node_name;

void createVectorFieldFromFile(pbge::SceneGraph *scene, pbge::OpenGL * ogl) {
    std::ifstream inputFile("inputField.txt", std::ifstream::in);
    
    int max_x = 0;
    int max_y = 0;
    int max_z = 0;
    inputFile >> max_x >> max_y >> max_z;
    int numberOfVectors = max_x * max_y * max_z;
    while(numberOfVectors--) {
        int pos_x, pos_y, pos_z;
        int vec_x, vec_y, vec_z;
        inputFile >> pos_x;
        inputFile >> pos_y;
        inputFile >> pos_z;
        inputFile >> vec_x;
        inputFile >> vec_y;
        inputFile >> vec_z;

        math3d::vector4 pos = math3d::vector4(pos_x,pos_y,pos_z);
        math3d::vector4 vec = math3d::vector4(vec_x,vec_y,vec_z);

        pbge::ModelInstance * vectorModel = Vector(pos, vec, ogl).createVectorInstance();
    
        pbge::Node * vectorPosNode = scene->appendChildTo(pbge::SceneGraph::ROOT, pbge::TransformationNode::translation(pos[0],pos[1],pos[2]));
        scene->appendChildTo(vectorPosNode, vectorModel);
    }
    inputFile.close();
}

class CustomSceneInitializer : public pbge::SceneInitializer {
    pbge::SceneGraph * operator () (pbge::OpenGL * ogl) {
        ogl->enableMode(pbge::OpenGL::DEPTH_TEST);
        glClearColor(0,0,0,0);

        pbge::SceneGraph * scene = new pbge::SceneGraph(new pbge::TransformationNode);

        createVectorFieldFromFile(scene, ogl);

        cam_node_name = scene->appendChildTo(pbge::SceneGraph::ROOT, pbge::TransformationNode::translation(0, 0, 100))->getSceneGraphIndex();
        
        pbge::CameraNode * cam = dynamic_cast<pbge::CameraNode*>(scene->appendChildTo(cam_node_name, new pbge::CameraNode()));
        scene->appendChildTo(cam_node_name, new pbge::PointLight);
        cam->lookAt(math3d::vector4(0,1,0),math3d::vector4(0,0,-1));
        cam->setPerspective(20, 1, 10.0f, 100);
        
        return scene;
    }
};

int main(int argc, char **argv) {
    FieldGenerator::generateFieldFile();
    pbge::Manager *manager = new pbge::Manager;
    manager->setWindowDimensions(500,500);
    manager->setFullscreen(false);
    manager->setWindowTitle("Spline Based MRI Fiber Tracking");
    manager->setSceneInitializer(new CustomSceneInitializer);
    manager->displayGraphics();
    delete manager;
    return 0;
}