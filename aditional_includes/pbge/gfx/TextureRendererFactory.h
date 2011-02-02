#include <string>
#include <GL/glew.h>

namespace pbge {
    class TextureRenderer {
    };

    class ARBFBOTextureRenderer:public TextureRenderer{

    };

    class EXTFBOTextureRenderer:public TextureRenderer {
    public:
        EXTFBOTextureRenderer(OpenGL * _ogl) {
            this->ogl = _ogl;
            initialize();
        }

        ~EXTFBOTextureRenderer() {
            ogl->deleteFramebuffersEXT(1, &fbo);
            fbo = 0;
            ogl = NULL;
        }
    private:
        void initialize() {
            ogl->genFramebuffersEXT(1, &fbo);
        }
        OpenGL * ogl;
        GLuint fbo;
    };

    class DefaultTextureRenderer:public TextureRenderer {

    };

    /* The abstract factory that chooses the correct implementation for the user */
    class TextureRendererFactory {
    public:
        TextureRendererFactory() {
            throw "need opengl";
        }
        TextureRendererFactory(OpenGL * _ogl) {
            this->ogl = _ogl;
        }

        TextureRenderer * getInstance() {
            if(textureRenderer == NULL) {
                instantiateTextureRenderer();
            }
            return textureRenderer;
        }

        void forceInstantiationOf(std::string extension) {

        }

        void instantiateTextureRenderer() {
            if(GLEW_ARB_framebuffer_object) {
                textureRenderer = new ARBFBOTextureRenderer;
            } else if (GLEW_EXT_framebuffer_object) {
                textureRenderer = new EXTFBOTextureRenderer(ogl);
            } else {
                textureRenderer = new DefaultTextureRenderer;
            }
        }

    private:
        OpenGL * ogl;
        TextureRenderer * textureRenderer;
    };
}