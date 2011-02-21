

#ifndef PBGE_GFX_RESOURCESTORAGE_H_
#define PBGE_GFX_RESOURCESTORAGE_H_

#include <map>

#include "pbge/core/core.h"

namespace pbge {
    class Shader;
    class GPUProgram;

    class PBGE_EXPORT ResourceStorage {
    public:
        void storeNamedShader(const std::string & name, Shader * shader) {
            shaders[name] = shader;
        }

        void storeNamedProgram(const std::string & name, GPUProgram * program) {
            programs[name] = program;
        }

        Shader * getNamedShader(const std::string & name) {
            std::map<std::string, Shader *>::iterator it = shaders.find(name);
            if(it != shaders.end()) 
                return it->second;
            return NULL;
        }

        GPUProgram * getNamedProgram(const std::string & name) {
            std::map<std::string, GPUProgram *>::iterator it = programs.find(name);
            if(it != programs.end())
                return it->second;
            return NULL;
        }

    private:

        std::map<std::string, Shader *> shaders;

        std::map<std::string, GPUProgram *> programs;
    };
}

#endif
