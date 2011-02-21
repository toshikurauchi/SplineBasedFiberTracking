


#ifndef gfxstateset_h_
#define gfxstateset_h_

#include <set>
#include <map>

#include "pbge/gfx/ShaderUniform.h"
#include "pbge/gfx/OpenGL.h"
#include "pbge/core/core.h"

#include <vector>

namespace pbge {
    class Texture;
    class TextureUnit;
    class BoundProgram;
    class GPUProgram;

    class PBGE_EXPORT State {
    public: 
        void applyChanges(OpenGL * ogl) {
            if(shouldChange(ogl)) {
                makeChange(ogl);
            }
        }

        virtual void makeChange(OpenGL * ogl) = 0;

        virtual bool shouldChange(OpenGL * ogl) = 0;
    };


    /*
        
    */
    class PBGE_EXPORT StateSet {
    public:
        StateSet(OpenGL * ogl);

        ~StateSet();

        void apply(OpenGL * ogl);

        void useProgram(GPUProgram * program);

        void enable(OpenGL::Mode mode);

        void disable(OpenGL::Mode mode);
        
        UniformValue * getUniformValue(const UniformInfo & info);

    private:
        UniformValue * createUniform(const UniformInfo & info);

        std::vector<State *> states;

        BoundProgram * boundProgram;

        std::map<UniformInfo, UniformValue *> uniformValues;

        std::vector<TextureUnit*> textureUnits;

        std::set<State*> changes;
    };
}


#endif