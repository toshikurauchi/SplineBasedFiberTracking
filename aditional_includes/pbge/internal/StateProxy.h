

#ifndef PBGE_INTERNAL_STATEPROXY_H_
#define PBGE_INTERNAL_STATEPROXY_H_

#include "pbge/gfx/OpenGL.h"

namespace pbge {

    class StateProxy {
    public:
        virtual void apply(OpenGL * ogl) = 0;

        virtual void unApply(OpenGL * ogl) = 0;

    };

    class EnableMode : public StateProxy{
    public:
        EnableMode(OpenGL::Mode mode);

        void apply(OpenGL * ogl);

        void unApply(OpenGL * ogl);
    private:
        OpenGL::Mode mode;
    };

    class DisableMode : public StateProxy{
    public:
        DisableMode(OpenGL::Mode mode);

        void apply(OpenGL * ogl);

        void unApply(OpenGL * ogl);
    private:
        OpenGL::Mode mode;
    };
}



#endif //PBGE_INTERNAL_STATEPROXY_H_