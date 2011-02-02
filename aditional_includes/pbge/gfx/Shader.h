#ifndef PBGE_GFX_SHADER_H_
#define PBGE_GFX_SHADER_H_ 1

#include <string>
#include <vector>
#include <set>

#include "pbge/gfx/ShaderUniform.h"
#include "pbge/gfx/OpenGL.h"
#include "pbge/core/core.h"

namespace pbge {

    class FileReader;

    class PBGE_EXPORT Shader {
    public:
        typedef enum {
            VERTEX_SHADER,
            FRAGMENT_SHADER
        } ShaderType;
        
        virtual const std::string & getInfoLog()=0;

        virtual bool compile(OpenGL * ogl) = 0;
    };

    class PBGE_EXPORT GPUProgram {
    public:
        virtual void bind(OpenGL * ogl) = 0;

        virtual void unbind(OpenGL * ogl) = 0;

        virtual bool link(OpenGL * ogl) = 0;

        virtual bool isLinked() = 0;

        virtual const std::string getInfoLog() = 0;

        virtual GLuint getId() = 0;

        virtual void updateUniforms(OpenGL * ogl) = 0;

    public: // Uniform binding
        virtual void bindFloat(const UniformInfo & info, OpenGL * ogl, const float & valor) = 0;
        virtual void bindFloatVec2(const UniformInfo & info, OpenGL * ogl, const float & v1, const float & v2) = 0;
        virtual void bindFloatVec3(const UniformInfo & info, OpenGL * ogl, const float & v1, const float & v2, const float & v3) = 0;
        virtual void bindFloatVec4(const UniformInfo & info, OpenGL * ogl, const float & v1, const float & v2, const float & v3, const float & v4) = 0;
    };


    class PBGE_EXPORT GLShader : public Shader{
    public:
        GLShader() { 
            shaderID = 0;
            source = NULL;
            compiled = false;
        }

        static GLShader * loadSourceFromFile(FileReader * file, const ShaderType type);

        static GLShader * loadSource(const std::string & source, const ShaderType type);

        bool isCompiled() {
            return compiled;
        }

        bool compile(OpenGL * ogl);

        const std::string & getInfoLog() {
            return infoLog;
        }

        GLuint getID() { 
            return shaderID; 
        }

    private:

        void extractInfolog(OpenGL * ogl);

        std::string infoLog;

        GLuint shaderID;

        ShaderType type;

        char * source;

        bool compiled;
    };

    class PBGE_EXPORT GLProgram : public GPUProgram{
    public:
        GLProgram() {
            programID = 0;
            linked = false;
        }

        void bind(OpenGL * ogl);

        void unbind(OpenGL * ogl);

        void attachShader(GLShader *shader);

        bool link(OpenGL * ogl);

        const std::string getInfoLog() {
            std::string shadersInfoLog = "";
            std::vector<GLShader*>::iterator it;
            for(it = attachedShaders.begin(); it != attachedShaders.end(); it++) {
                shadersInfoLog += (*it)->getInfoLog();
            }
            return shadersInfoLog + "\n" + infoLog;
        }

        bool isLinked() {
            return linked;
        }

        static GLProgram * fromString(const std::string &vertexShader, const std::string &fragmentShader);

        static GLProgram * fromFile(FileReader * vertexShaderFile, FileReader *  fragmentShaderFile);

        GLuint getId() { return programID; }

    public: // Uniform binding
        void bindFloat(const UniformInfo & info, OpenGL * ogl, const float & valor);
        void bindFloatVec2(const UniformInfo & info, OpenGL * ogl, const float & v1, const float & v2);
        void bindFloatVec3(const UniformInfo & info, OpenGL * ogl, const float & v1, const float & v2, const float & v3);
        void bindFloatVec4(const UniformInfo & info, OpenGL * ogl, const float & v1, const float & v2, const float & v3, const float & v4);
        void updateUniforms(OpenGL * ogl);
    private:
        void extractInfoLog(OpenGL * ogl);

        void extractUniformInformation(OpenGL * ogl);

        bool linked;

        GLuint programID;

        std::vector<GLShader*> attachedShaders;

        std::string infoLog;

        std::set<UniformInfo> uniforms;
    };
}

#endif
