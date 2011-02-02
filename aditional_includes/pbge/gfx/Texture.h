#ifndef PBGE_GFX_TEXTURE_H_
#define PBGE_GFX_TEXTURE_H_

#include <string>
#include <vector>

#include "pbge/core/core.h"
#include "pbge/gfx/OpenGL.h"
#include "pbge/gfx/Buffer.h"

namespace pbge {
    class OpenGL;

    class Texture {
    public:
        GLuint getGLID() { return glID; }

        GLenum getTarget() { return target; }
    protected:
        GLuint glID;
        GLenum target;
    };

    class Texture2D : public Texture {
        virtual void loadFromBuffer(Buffer * buffer, GLint width, GLint height, GLenum internalFormat, GLenum bufferDataType, OpenGL * ogl);
    };

}
#endif
