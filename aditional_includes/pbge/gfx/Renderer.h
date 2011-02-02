

#ifndef PBGE_GFX_RENDERER_H_
#define PBGE_GFX_RENDERER_H_

#include <vector>
#include <GL/glew.h>

#include "pbge/core/core.h"

namespace pbge {
    class UpdaterVisitor;
    class RenderVisitor;
    class Camera;
    class OpenGL;
    class LightPassVisitor;
    class SceneGraph;
    class Node;

    class PBGE_EXPORT Renderer{
    public:
        Renderer(OpenGL * _ogl);

        void setScene(const SceneGraph * scene_manager);

        SceneGraph * getScene();

        void updateScene();

        void render();
    private:
        void renderWithCamera(Camera * camera, Node * root);

        SceneGraph * scene;

        UpdaterVisitor * updater;

        RenderVisitor * renderer;

        RenderVisitor * depthRenderer;

        LightPassVisitor * lightPassVisitor;

        OpenGL * ogl;
    };
}
#endif
