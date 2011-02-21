

#ifndef PBGE_CORE_WINDOW_H_
#define PBGE_CORE_WINDOW_H_

#include <string>

namespace pbge {
    class OpenGL;
    class Renderer;
    class SceneGraph;
    class SceneInitializer;

    class Window {
    public:
        Window () {
            fullscreen = false;
            width = 500;
            height = 500;
            positionX = 0;
            positionY = 0;
            windowTitle = "";
            renderer = NULL;
            ogl = NULL;
            scene = NULL;
            initializer = NULL;
        }

        ~Window();
        
        void setWindowDimensions(const unsigned & w, const unsigned & h) {
            width = w;
            height = h;
        }

        void setFullscreen(const bool & _fullscreen) {
            fullscreen = _fullscreen;
        }

        void setTitle(const std::string & title) {
            windowTitle = title;
        }

        void setOpenGL(OpenGL * openGL) {
            this->ogl = openGL;
        }

        OpenGL * getOpenGL () {
            return ogl;
        }

        Renderer * getRenderer () {
            return renderer;
        }

        void setScene(SceneGraph * sceneGraph) {
            scene = sceneGraph;
        }

        SceneGraph * getScene() {
            return scene;
        }

        void setSceneInitializer(SceneInitializer * newInitializer) {
            initializer = newInitializer;
        }

        SceneInitializer * getSceneInitializer() {
            return initializer;
        }

        void displayWindow();

    private:
        std::string windowTitle;

        unsigned width;
        
        unsigned height;

        unsigned positionX;

        unsigned positionY;

        bool fullscreen;

        Renderer * renderer;

        OpenGL * ogl;

        SceneGraph * scene;

        SceneInitializer * initializer;
    };
}
#endif