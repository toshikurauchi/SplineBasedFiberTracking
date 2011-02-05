

#include <iostream>

#include "pbge/core/Manager.h"
#include "pbge/gfx/Light.h"
#include "pbge/gfx/Buffer.h"
#include "pbge/gfx/SceneGraph.h"
#include "pbge/gfx/Node.h"
#include "pbge/gfx/Renderer.h"
#include "pbge/gfx/StateSet.h"

#include <GL/glut.h>

#include "Vector.h"

int cam_node_name;
pbge::Renderer * renderer;
pbge::SceneGraph * scene;

void setUp() {
    pbge::Manager::init();
    pbge::Manager::getInstance()->getOpenGL()->enableMode(pbge::OpenGL::DEPTH_TEST);
    glClearColor(0,0,0,0);
    math3d::vector4 pos = math3d::vector4(0,0,1);
    math3d::vector4 vec = math3d::vector4(1,1,0);
    pbge::ModelInstance * vboModel = Vector(pos, vec).createVectorInstance();

    renderer = new pbge::Renderer(pbge::Manager::getInstance()->getOpenGL());
    scene = new pbge::SceneGraph(new pbge::TransformationNode);

    pbge::Node * vectorPosNode = scene->appendChildTo(pbge::SceneGraph::ROOT, pbge::TransformationNode::translation(pos[0],pos[1],pos[2]));
    cam_node_name = scene->appendChildTo(pbge::SceneGraph::ROOT, pbge::TransformationNode::translation(0, 0, 3))->getSceneGraphIndex();
    
    scene->appendChildTo(vectorPosNode, vboModel);
    pbge::CameraNode * cam = dynamic_cast<pbge::CameraNode*>(scene->appendChildTo(cam_node_name, new pbge::CameraNode()));
    scene->appendChildTo(cam_node_name, new pbge::PointLight);
    cam->lookAt(math3d::vector4(0,1,0),math3d::vector4(0,0,-1));
    cam->setPerspective(45, 1, 1.0f, 10);
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