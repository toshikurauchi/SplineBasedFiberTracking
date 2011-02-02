

#ifndef gfxmodel_h_
#define gfxmodel_h_

#include "pbge/core/core.h"
#include "pbge/gfx/OpenGL.h"
#include "pbge/gfx/Node.h"

namespace pbge {
    class VertexBuffer;
    class ModelInstance;

    class PBGE_EXPORT Model{
    public:
        virtual void render(ModelInstance * instance, OpenGL * ogl)=0;

        virtual void renderDepth(ModelInstance * instance, OpenGL * ogl)=0;
    };

    class PBGE_EXPORT VBOModel : public Model {
    public:
        VBOModel(VertexBuffer * vbo, GLenum primitive);

        void render(ModelInstance * instance, OpenGL * ogl);

        void renderDepth(ModelInstance * instance, OpenGL * ogl);
    private:
        VertexBuffer * vbo;
        GLenum primitive;
    };


    class PBGE_EXPORT ModelInstance : public Node {
    public:
        ModelInstance(){
            model = NULL;
        }

        ModelInstance(Model * _model) {
            model = _model;
        }
        
        void updatePass(UpdaterVisitor * visitor, OpenGL * ogl){}

        void postUpdatePass(UpdaterVisitor * visitor, OpenGL * ogl){}

        void renderPass(RenderVisitor * visitor, OpenGL * ogl);

        void postRenderPass(RenderVisitor * visitor, OpenGL * ogl){}

        void depthPass(RenderVisitor * visitor, OpenGL * ogl);

        void postDepthPass(RenderVisitor * visitor, OpenGL * ogl){}

        void addChild(Node * node) {
            childs.push_back(node);
        }

        node_list & getChilds() {
            return childs;
        }

        Model * getModel() {
            return model;
        }
    private:
        Model * model;

        node_list childs;
    };
}
#endif
