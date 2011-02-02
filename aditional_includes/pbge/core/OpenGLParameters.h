
#ifndef PBGE_OPENGL_PARAMETERS
#define PBGE_OPENGL_PARAMETERS

#include <GL/glew.h>
#include "pbge/core/core.h"

namespace pbge {

    struct PBGE_EXPORT OpenGLParameters {
        int window_width,
            window_height,
            redSize,
            greenSize,
            blueSize,
            alphaSize,
            depthSize,
            stencilSize;

        OpenGLParameters() {
            window_width = 1024;
            window_height = 768;
            redSize = 8;
            greenSize = 8;
            blueSize = 8;
            alphaSize = 8;
            depthSize = 16;
            stencilSize = 16;
        }

    };
}

#endif
