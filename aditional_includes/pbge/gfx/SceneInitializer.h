
#ifndef PBGE_GFX_SCENEINITIALIZER
#define PBGE_GFX_SCENEINITIALIZER

#include "pbge/core/core.h"

namespace pbge {
    class SceneGraph;
    class OpenGL;

    class PBGE_EXPORT SceneInitializer {
    public:
        /*
            when this method is called the by the pbge the OpenGL context is guaranteed to be initialized

            must return a valid scene graph
        */
        virtual SceneGraph * operator () (OpenGL * ogl) = 0;

    };
}


#endif
