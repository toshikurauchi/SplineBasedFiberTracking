

#ifndef PBGE_GFX_OPENGL_H_
#define PBGE_GFX_OPENGL_H_

#include <iostream>
#include <GL/glew.h>

#include "math3d/math3d.h"

#include "pbge/core/core.h"

namespace pbge {
    class ResourceStorage;
    class StateSet;
    class Buffer;
    class UniformInfo;
    class UniformValue;
    
    class GLContext {
    public:
        virtual void makeCurrent() = 0;

        virtual void swapBuffers() = 0;

        virtual void release() = 0;

        virtual void getSystemGLContext(void * p_context) = 0;

        virtual void getSystemDeviceContext(void * p_device) = 0;
    };

    class PBGE_EXPORT OpenGL {
    public:

        typedef enum {
            DEPTH_TEST = 0,
            STENCIL_TEST,
            SCISSOR_TEST,
            BLEND,
            COLOR_LOGIC_OP,
            CULL_FACE,
            DEPTH_CLAMP,
            DITHER,
            LINE_SMOOTH,
            MULTISAMPLE,
            POLYGON_OFFSET_FILL,
            POLYGON_OFFSET_LINE,
            POLYGON_OFFSET_POINT,
            POLYGON_SMOOTH,
            PRIMITIVE_RESTART,
            SAMPLE_ALPHA_TO_COVERAGE,
            PROGRAM_POINT_SIZE
        } Mode;

        OpenGL();

        ~OpenGL();
        
        void setContext(GLContext * newContext);

        GLContext * getContext() {
            return context;
        }

        void releaseContext ();

        void makeContextCurrent() {
            context->makeCurrent();
        }

        void swapBuffers() {
            context->swapBuffers();
        }

        virtual void setMatrixMode(GLenum mode);

        virtual void loadViewMatrix(const math3d::matrix44 & m) {
            matrices[0] = m;
        }

        virtual void loadProjectionMatrix(const math3d::matrix44 & m) {
            matrices[1] = m;
        }

        virtual void loadModelMatrix(const math3d::matrix44 & m) {
            matrices[2] = m;
        }

        virtual void updateState();

        virtual void uploadProjection();

        virtual Buffer * createBuffer(size_t _size, GLenum _usage, GLenum _target);

        virtual UniformValue * getUniformValue(const UniformInfo & info);

        virtual void enableMode(Mode mode);

        virtual void disableDrawBuffer();

        virtual void enableDrawBuffer(GLenum buffer);

        virtual StateSet & getState() { return *state; }

        virtual ResourceStorage & getStorage() { return *storage; }

        
        
        // raw OpenGL API calls
        virtual void activeTexture(GLenum textureUnit);

        virtual void alphaFunc(GLenum func, GLclampf ref);

        virtual void attachShader(GLuint program, GLuint shader);

        virtual void begin(GLenum mode);

        virtual void beginQuery(GLenum target, GLuint id);

        virtual void bindAttribLocation(GLuint program, GLuint index, const GLchar* name);

        virtual void bindBuffer(GLenum target, GLuint buffer);

        virtual void bindTexture(GLenum target, GLuint texture);

        virtual void blendFunc(GLenum sfactor, GLenum dfactor);

        virtual void bufferData(GLenum target, GLsizeiptr size, GLvoid * data, GLenum usage);

        virtual void bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data);
        
        virtual void clear(GLbitfield mask);

        virtual void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

        virtual void clearDepth(GLclampd depth);

        virtual void clearStencil(GLint s);

        virtual void clientActiveTexture(GLenum textureUnit);

        virtual void clipPlane(GLenum plane, const GLdouble * equation);

        virtual void colorPointer(GLint size, GLenum type, GLsizei stride, GLvoid * pointer);

        virtual void compileShader(GLuint shader);

        virtual GLuint createProgram();

        virtual GLuint createShader(GLenum shaderType);

        virtual void deleteBuffers(GLsizei n, GLuint * buffers);

        virtual void depthFunc(GLenum func);

        virtual void depthMask(GLboolean flag);

        virtual void disable(GLenum mode);

        virtual void drawBuffer(GLenum mode);

        virtual void enable(GLenum mode);

        virtual void enableClientState(GLenum cap);

        virtual void genBuffers(GLsizei n, GLuint * buffers);

        virtual void getActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);

        virtual void getFloatv(GLenum pname, GLfloat * params);

        virtual void getIntegerv(GLenum pname, GLint * params);

        virtual void getProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei * length, GLchar * infoLog);

        virtual void getProgramiv(GLuint program, GLenum pname, GLint * params);

        virtual void getShaderiv(GLuint shader, GLenum pname, GLint * ptr);

        virtual void getShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei * length, GLchar * infoLog);

        virtual const char * getString(GLenum name);

        virtual GLint getUniformLocation(GLuint program, const char * name);

        virtual void linkProgram(GLuint program);

        virtual void loadMatrix(GLfloat * matrix);

        virtual void * mapBuffer(GLenum target, GLenum access);

        virtual void matrixMode(GLenum mode);

        virtual void normalPointer(GLenum type, GLsizei stride, GLvoid * pointer);

        virtual void readBuffer(GLenum mode);

        virtual void secondaryColorPointer(GLint size, GLenum type, GLsizei stride, GLvoid * pointer);

        virtual void shaderSource(GLuint id, GLsizei count, const GLchar ** strings, const GLint * sizes);

        virtual void texCoordPointer(GLint size, GLenum type, GLsizei stride, GLvoid * pointer);

        virtual void uniform1f(GLint location, GLfloat v);

        virtual void uniform2f(GLint location, GLfloat v1, GLfloat v2);

        virtual void uniform3f(GLint location, GLfloat v, GLfloat v2, GLfloat v3);

        virtual void uniform4f(GLint location, GLfloat v, GLfloat v2, GLfloat v3, GLfloat v4);

        virtual void uniform1i(GLint location, GLint v);

        virtual void uniform2i(GLint location, GLint v1, GLint v2);

        virtual void uniform3i(GLint location, GLint v1, GLint v2, GLint v3);

        virtual void uniform4i(GLint location, GLint v1, GLint v2, GLint v3, GLint v4);

        virtual void useProgram(GLuint program);

        virtual void vertexPointer(GLint size, GLenum type, GLsizei stride, GLvoid * pointer);

        virtual void viewport(GLint x, GLint y, GLint w, GLint h);
        
        //Extensions to 2.1
        virtual void genFramebuffersEXT(GLsizei n, GLuint * buffers);

        virtual void deleteFramebuffersEXT(GLsizei n, GLuint * buffers);

    private:
        void uploadModelview();

        math3d::matrix44 * matrices;

        GLenum currentMatrixMode;

        StateSet * state;

        ResourceStorage * storage;

        GLContext * context;
    };

}

#endif
