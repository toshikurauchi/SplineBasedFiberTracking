

#ifndef PBGE_GFX_NODEVISITORS_H_
#define PBGE_GFX_NODEVISITORS_H_
#include <vector>

#include "math3d/math3d.h"

#include "pbge/core/core.h"

namespace pbge {

    class Node;
    class Light;
    class Camera;
    class OpenGL;

    class PBGE_EXPORT UpdaterVisitor {
    public:
        static const int MAX_STACK_DEPTH = 16;

        UpdaterVisitor() {
            transformationStack = new math3d::matrix44[UpdaterVisitor::MAX_STACK_DEPTH];
            transformationStack[0] = math3d::identity44;
            stackIndex = 0;
        }

        ~UpdaterVisitor() {
            delete [] transformationStack;
        }

        void visit(Node * node, OpenGL * ogl);

        void pushTransformation(const math3d::matrix44 & m);

        void popTransformation();

        const math3d::matrix44 getCurrentTransformation();

        void addActiveCamera(Camera * camera) {
            activeCameras.push_back(camera);
        }

        void addActiveLight(Light * light) {
            activeLights.push_back(light);
        }

        std::vector<Light*> & getActiveLights() {
            return activeLights;
        }

        std::vector<Camera *> & getActiveCameras() {
            return activeCameras;
        }

    private:
        void _visit(Node * node, OpenGL * ogl);

        math3d::matrix44 * transformationStack;

        int stackIndex;

        std::vector<Camera *> activeCameras;

        std::vector<Light*> activeLights;
    };

    /* Interface for a visitor class that render something on some OpenGL buffer */
    class PBGE_EXPORT RenderVisitor {
    public:
        virtual void visit(Node * node, OpenGL * ogl) = 0;
    };

    class PBGE_EXPORT ColorPassVisitor : public RenderVisitor {
        void visit(Node * node, OpenGL * ogl);
    };

    class PBGE_EXPORT DepthPassVisitor : public RenderVisitor{
    public:
        void visit(Node * node, OpenGL * ogl);
    };

    class PBGE_EXPORT LightPassVisitor : public RenderVisitor {
    public:

        LightPassVisitor () {
            currentLight = NULL;
        }

        void setCurrentLight(Light * light) {
            currentLight = light;
        }

        void setCurrentCamera(Camera * camera) {
            currentCamera = camera;
        }

        void visit(Node * node, OpenGL * ogl);
    private:
        Camera * currentCamera;

        Light * currentLight;
    };
}


#endif