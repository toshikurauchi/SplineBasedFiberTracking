#ifndef pbge_manager
#define pbge_manager 1

#include "pbge/core/Log.h"
#include "pbge/core/core.h"

#include <string>
#include <vector>

namespace pbge {
    class OpenGL;
    class Window;
    class SceneGraph;
    class SceneInitializer;

    class PBGE_EXPORT Manager{
    public:
        /* Write a status or warning message */
        void writeLog(std::string message) { 
            if(this->log != NULL)
                log->write(message); 
        }
        
        /* Write internal error messages for the user */
        void writeErrorLog(std::string message) {
            if(this->log != NULL) 
                log->writeError(message); 
        }
        
        /* Add a new shader source directory to the search path */
        void addShaderDirectory(const std::string & newDir);

        /* Get all the directories in the shader source search path */
        const std::vector<std::string> getShaderDirs() const;

        /* sets a user defined logger */
        void setLog(Log * newLog) {
            if(this->log != NULL)
                delete this->log;
            log = newLog;
        }
        
        OpenGL * getOpenGL() {
            return ogl;
        }

    // public window initialization functions
    public:
        Manager();

        ~Manager();

        void setWindowDimensions(const unsigned & w, const unsigned & h);

        void setFullscreen(const bool & fullscreen);

        void setWindowTitle(const std::string title);

        void setMainSceneGraph(SceneGraph * sceneGraph);

        void setSceneInitializer(SceneInitializer * initializer);

        void displayGraphics();

    private:
        Window * window;
        Log * log;
        OpenGL * ogl;
        std::vector<std::string> shaderDirectories;
    };
}

#endif //pbge_manager
