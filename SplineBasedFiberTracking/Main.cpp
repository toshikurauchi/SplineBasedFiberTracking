

#include <iostream>
#include <fstream>

#include "pbge/core/Manager.h"
#include "pbge/gfx/Light.h"
#include "pbge/gfx/Buffer.h"
#include "pbge/gfx/SceneGraph.h"
#include "pbge/gfx/Node.h"
#include "pbge/gfx/Renderer.h"
#include "pbge/gfx/StateSet.h"

#include <GL/glut.h>

#include "Vector.h"
#include "FieldGenerator.h"

int cam_node_name;
pbge::Renderer * renderer;
pbge::SceneGraph * scene;

void createVectorFieldFromFile(pbge::SceneGraph *scene) {
    std::ifstream inputFile("inputField.txt", std::ifstream::in);
    
    int numberOfVectors = 0;
    inputFile >> numberOfVectors;
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

        pbge::ModelInstance * vectorModel = Vector(pos, vec).createVectorInstance();
    
        pbge::Node * vectorPosNode = scene->appendChildTo(pbge::SceneGraph::ROOT, pbge::TransformationNode::translation(pos[0],pos[1],pos[2]));
        scene->appendChildTo(vectorPosNode, vectorModel);
    }
    inputFile.close();
}

void setUp() {
    pbge::Manager::init();
    pbge::Manager::getInstance()->getOpenGL()->enableMode(pbge::OpenGL::DEPTH_TEST);
    glClearColor(0,0,0,0);

    renderer = new pbge::Renderer(pbge::Manager::getInstance()->getOpenGL());
    scene = new pbge::SceneGraph(new pbge::TransformationNode);

    createVectorFieldFromFile(scene);

    cam_node_name = scene->appendChildTo(pbge::SceneGraph::ROOT, pbge::TransformationNode::translation(0, 0, 100))->getSceneGraphIndex();
    
    pbge::CameraNode * cam = dynamic_cast<pbge::CameraNode*>(scene->appendChildTo(cam_node_name, new pbge::CameraNode()));
    scene->appendChildTo(cam_node_name, new pbge::PointLight);
    cam->lookAt(math3d::vector4(0,1,0),math3d::vector4(0,0,-1));
    cam->setPerspective(20, 1, 10.0f, 100);
    renderer->setScene(scene);
}

void display() {
    renderer->render();
    glutSwapBuffers();
    GLenum err = glGetError();
    while(err != GL_NO_ERROR) {
        std::cout << gluErrorString(err) << std::endl;
        err = glGetError();
    }
}

int main(int argc, char **argv) {
    FieldGenerator::generateFieldFile();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Spline Based MRI Fiber Tracking");
    setUp();
    glutDisplayFunc(display);
    glutMainLoop();
    delete scene;
    delete renderer;
    return 0;
}