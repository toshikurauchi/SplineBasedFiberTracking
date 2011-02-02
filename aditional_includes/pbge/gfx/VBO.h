

#ifndef PBGE_GFX_VBO_H_
#define PBGE_GFX_VBO_H_

#include <vector>
#include <algorithm>
#include <string>

#include "pbge/core/core.h"
#include "pbge/exceptions/exceptions.h"

namespace pbge {
    class VertexBuffer;
    class Buffer;

    class PBGE_EXPORT VertexAttrib{
    public:
        typedef enum {
            VERTEX,
            NORMAL,
            TEXCOORD,
            COLOR,
            SECONDARY_COLOR,
            CUSTOM_ATTRIB
        } Type;

        VertexAttrib(int _nCoord, int _offset, GLsizei _stride) {
            nCoord = _nCoord;
            offset = _offset;
            stride = _stride;
        }

        virtual Type getType() = 0;

        int getOffset() {
            return offset;
        }
        int getStride() {
            return stride;
        }
        int getNCoord() {
            return nCoord;
        }
        virtual void bindAttrib(OpenGL * ogl) = 0;
    private:
        int nCoord, offset;
        GLsizei stride;
    };

    class PBGE_EXPORT VertexPositionAttrib : public VertexAttrib{
    public:
        VertexPositionAttrib(int _nCoord, int _offset, GLsizei _stride) : VertexAttrib(_nCoord, _offset, _stride) {}

        Type getType() { return VERTEX; }

        void bindAttrib(OpenGL * ogl);
    };

    class PBGE_EXPORT VertexNormalAttrib : public VertexAttrib{
    public:
        VertexNormalAttrib(int _offset, GLsizei _stride) : VertexAttrib(3, _offset, _stride) {}
        
        Type getType() { return NORMAL; }

        void bindAttrib(OpenGL * ogl);
    };

    class PBGE_EXPORT VertexTexcoordAttrib : public VertexAttrib {
    public:
        VertexTexcoordAttrib(int _nCoord, int _offset, GLsizei _stride) : VertexAttrib(_nCoord, _offset, _stride) {}

        Type getType() { return TEXCOORD; }

        void bindAttrib(OpenGL * ogl);
    };

    class PBGE_EXPORT VertexColorAttrib : public VertexAttrib {
    public:
        VertexColorAttrib(int _nCoord, int _offset, GLsizei _stride) : VertexAttrib(_nCoord, _offset, _stride) {}

        Type getType() { return COLOR; }

        void bindAttrib(OpenGL * ogl);
    };

    class PBGE_EXPORT VertexSecondaryColorAttrib : public VertexAttrib {
    public:
        VertexSecondaryColorAttrib(int _nCoord, int _offset, GLsizei _stride) : VertexAttrib(_nCoord, _offset, _stride) {}

        Type getType() { return SECONDARY_COLOR; }

        void bindAttrib(OpenGL * ogl);
    };

    class PBGE_EXPORT VertexCustomAttrib : public VertexAttrib {
    public:
        VertexCustomAttrib(int _nCoord, int _offset, GLsizei _stride) : VertexAttrib(_nCoord, _offset, _stride) {}

        Type getType() { return CUSTOM_ATTRIB;}

        void bindAttrib(OpenGL * ogl) {}
    };


    class PBGE_EXPORT VertexBuffer {
    public:
        VertexBuffer(Buffer * _buffer, unsigned _nVertices) {
            buffer = _buffer;
            nVertices = _nVertices;
        }

        ~VertexBuffer();

        void addAttrib(VertexAttrib * attrib) {
            attribs.push_back(attrib);
        }

        void bindAllAttribs(OpenGL * ogl);

        void bindOnly(VertexAttrib::Type, OpenGL * ogl);

        void bind(OpenGL * ogl);

        void unbind(OpenGL * ogl);

        unsigned getNVertices() {
            return nVertices;
        }
    
    private:
        Buffer * buffer;
        unsigned nVertices;
        std::vector<VertexAttrib*> attribs;
    };






    class PBGE_EXPORT VertexAttribBuilder {
    public:
        VertexAttribBuilder(unsigned _nCoord, VertexAttrib::Type _type, int _index = -1) {
            nCoord = _nCoord;
            type = _type;
            index = _index;
            indexesAssigned = false;
            currentElement = 0;
            name = "";
        }

        VertexAttribBuilder(unsigned _nCoord, VertexAttrib::Type _type, const std::string & _name) {
            nCoord = _nCoord;
            type = _type;
            index = -1;
            indexesAssigned = false;
            currentElement = 0;
            name = _name;
        }

        void pushValue(const float x, const float y, const float z, const float w) {
            values.push_back(x);
            values.push_back(y);
            values.push_back(z);
            values.push_back(w);
        }

        bool operator == (const VertexAttribBuilder & other);

        void setIndexes(const std::vector<unsigned short> & _indexes) {
            indexesAssigned = true;
            this->indexes = _indexes;
        }

        int numberOfCoordinates() {
            return nCoord;
        }

        int numberOfElements() {
            return indexes.size();
        }

        bool areIndexesAssigned() {
            return this->indexesAssigned;
        }

        void getNextElement(float * elems);

        bool isValid();

        VertexAttrib * createInstance(int offset, GLsizei stride);

    private:
        std::string name;
        unsigned nCoord;
        VertexAttrib::Type type;
        int index;
        std::vector<float> values;
        bool indexesAssigned;
        std::vector<unsigned short> indexes;
        int currentElement;
    };


    class PBGE_EXPORT VertexBufferBuilder {
    public:
        VertexBufferBuilder(unsigned _nVertices) {
            nVertices = _nVertices;
            curAttrib = NULL;
        }

        const VertexAttribBuilder addAttrib(unsigned _nElements, VertexAttrib::Type _type, int _index=-1) {
            VertexAttribBuilder attrib(_nElements, _type, _index);
            attribs.push_back(attrib);
            return attrib;
        }

        VertexBufferBuilder & pushValue(const VertexAttribBuilder & attrib, const float &x=0.0f, const float & y=0.0f, const float & z=0.0f, const float & w=0.0f);
        
        VertexBufferBuilder & pushValue(const float &x=0.0f, const float & y=0.0f, const float & z=0.0f, const float & w=0.0f) {
            if(curAttrib != NULL) curAttrib->pushValue(x,y,z,w);
            return *this;
        }

        VertexBufferBuilder & on(const VertexAttribBuilder & attrib) {
            std::vector<VertexAttribBuilder>::iterator it = std::find(attribs.begin(), attribs.end(), attrib);
            if(it != attribs.end())
                curAttrib = &(*it);
            return *this;
        }

        VertexBufferBuilder & setAttribIndex(const VertexAttribBuilder & attrib, const std::vector<unsigned short> & indexes);

        VertexBufferBuilder & setAttribIndex(const std::vector<unsigned short> & indexes);

        VertexBuffer * done(GLenum usage = GL_STATIC_DRAW);

    private:
        void validateAttribs();

        GLsizei calculateSize();

        VertexAttribBuilder * curAttrib;

        void createAttribs(VertexBuffer * vbo, GLsizei stride);

        unsigned nVertices;

        std::vector<VertexAttribBuilder> attribs;
    };
}

#endif