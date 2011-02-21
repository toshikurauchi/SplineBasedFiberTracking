
#ifndef PBGE_GFX_LIGHT_H_
#define PBGE_GFX_LIGHT_H_

#include "math3d/vector4.h"
#include "pbge/gfx/Node.h"

namespace pbge {
    
    class Shader;
    class GPUProgram;
    class UpdaterVisitor;
    class RenderVisitor;

    class PBGE_EXPORT Light : public Node {
    public:
        virtual void turnOn() = 0;

        virtual void turnOff() = 0;

        virtual bool isLightOn() = 0;

        virtual GPUProgram * getLightPassProgram(OpenGL * ogl) = 0;

        virtual void setNecessaryUniforms(OpenGL * ogl, const math3d::matrix44 & viewTransform) = 0;

        virtual void setSpecularColor(const float & red, const float & green, const float & blue, const float & alpha) = 0;

        virtual void setDiffuseColor(const float & red, const float & green, const float & blue, const float & alpha) = 0;
    };

    class PBGE_EXPORT PointLight : public Light {
    public: // the node interface methods
        void updatePass(UpdaterVisitor * visitor, OpenGL * ogl);

        void postUpdatePass(UpdaterVisitor * visitor, OpenGL * ogl) {}

        void renderPass(RenderVisitor * visitor, OpenGL * ogl){}

        void postRenderPass(RenderVisitor * visitor, OpenGL * ogl){}

        void depthPass(RenderVisitor * visitor, OpenGL * ogl) {}

        void postDepthPass(RenderVisitor * visitor, OpenGL * ogl) {}

        void addChild(Node * node) {
            childs.push_back(node);
        }
        
        node_list & getChilds() {
            return childs;
        }

    public:
        // Light specific methods
        PointLight();

        void turnOn() {
            on = true;
        }

        void turnOff() {
            on = false;
        }

        bool isLightOn() {
            return on;
        }

        math3d::vector4 & getPosition() {
            return *position;
        }

        GPUProgram * getLightPassProgram(OpenGL * ogl) {
            if(program == NULL)
                return PointLight::getDefaultLightPassProgram(ogl);
            return program;
        }

        void setNecessaryUniforms(OpenGL * ogl, const math3d::matrix44 & viewTransform);

        void setSpecularColor(const float & red, const float & green, const float & blue, const float & alpha) {}

        void setDiffuseColor(const float & red, const float & green, const float & blue, const float & alpha) {
            diffuseColor[0] = red;
            diffuseColor[1] = green;
            diffuseColor[2] = blue;
            diffuseColor[3] = alpha;
        }

    public:
        static Shader * getDefaultLightPassVS(OpenGL * ogl);

        static Shader * getDefaultLightPassFS(OpenGL * ogl);

        static GPUProgram * getDefaultLightPassProgram(OpenGL * ogl);

    private:
        math3d::vector4 * position;

        float diffuseColor[4];

        GPUProgram * program;

        node_list childs;

        bool on;
    };
}

#endif
