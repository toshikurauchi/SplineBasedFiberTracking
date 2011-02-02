

#ifndef gfxbuffer_h_
#define gfxbuffer_h_

#include <cstdlib>
#include <iostream>

#include "pbge/core/Manager.h"
#include "pbge/gfx/OpenGL.h"

namespace pbge {
    class Buffer {
    public:
        // allows factory method on OpenGL
        friend OpenGL;

        // Useless constructor
        // but don't erase it
        Buffer() {
            this->data = NULL;
            glID = 0;
        }
        
        // returns the data buffer
        virtual void * map() {
            return data;
        }

        // Maps with an offset from the begining of the data buffer
        virtual void * map(int _begin) {
            return (char*)data + _begin;
        }
        
        // force call to glMapBuffer
        virtual void * forceDirectMap(OpenGL * ogl, GLenum access) {
            ogl->bindBuffer(target, glID);
            return ogl->mapBuffer(target, access);
        }

        //virtual void setData(void * _data, size_t _size);

        //virtual void setSubData(void * _data, size_t _size, int _begin, int _end);
        
        // call this to update the OpenGL state
        virtual void flush(OpenGL * ogl, bool keepBound=false) {
            if(glID == 0) createBuffer(ogl, keepBound);
            else if(begin_update >=0) {
                ogl->bindBuffer(target, glID);
                ogl->bufferSubData(target, begin_update, size - begin_update, (char*)data + begin_update);
                if(!keepBound) {
                    ogl->bindBuffer(target, 0);
                }
            } else if(keepBound)
                ogl->bindBuffer(target, glID);
        }

        void bind(OpenGL * ogl) {
            ogl->bindBuffer(target, glID);
        }

        void unbind(OpenGL * ogl) {
            ogl->bindBuffer(target, 0);
        }

        void bindOn(GLenum _target, OpenGL * ogl) {
            ogl->bindBuffer(_target, glID);
        }

        GLuint getID() {
            return glID;
        }
    private:
        Buffer(size_t _size, GLenum _usage, GLenum _target) {
            this->size = _size;
            this->usage = _usage;
            this->target = _target;
            // malloc is used because raw data is needed
            this->data = malloc(size);
            if(this->data == NULL) {
                Manager::getInstance()->writeErrorLog("ERROR: Out Of Memory for Buffer");
            }
            this->glID = 0;
        }
        
        void release() {
            if(glID) 
                Manager::getInstance()->getOpenGL()->deleteBuffers(1, &glID);
            if(this->data)
                free(this->data);
        }

        void createBuffer(OpenGL * ogl, bool keepBound) {
            ogl->genBuffers(1, &glID);
            ogl->bindBuffer(target, glID);
            ogl->bufferData(target, size, data, usage);
            if(!keepBound)
                ogl->bindBuffer(target, 0);
        }

        int begin_update;

        GLenum usage;

        GLenum target;

        void * data;

        GLuint glID;

        size_t size;
    };

}

#endif