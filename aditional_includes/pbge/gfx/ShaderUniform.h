

#ifndef PBGE_GFX_SHADERUNIFORM_H_
#define PBGE_GFX_SHADERUNIFORM_H_


#include <string>
#include <sstream>

#include "math3d/math3d.h"

namespace pbge {

    class GPUProgram;
    class OpenGL;

    typedef enum {
        INVALID, 

        FLOAT,
        FLOAT_VEC2,
        FLOAT_VEC3,
        FLOAT_VEC4,

        INT,
        INT_VEC2,
        INT_VEC3,
        INT_VEC4,

        BOOL,
        BOOL_VEC2,
        BOOL_VEC3,
        BOOL_VEC4,

        FLOAT_MAT2,
        FLOAT_MAT3,
        FLOAT_MAT4,
        FLOAT_MAT23,
        FLOAT_MAT24,
        
        SAMPLER_2D,
        SAMPLER_3D,
        SAMPLER_CUBE,
        SAMPLER_1D_SHADOW,
        SAMPLER_2D_SHADOW
    }UniformType;

    class UniformInfo {
    public:
        UniformInfo(const std::string & _name, const UniformType _type, const int & _location) {
            name = _name;
            type = _type;
            location = _location;
        }

        UniformInfo(){}

        UniformType getType() const{
            return type;
        }

        const std::string getName() const{
            return name;
        }

        const int getLocation() const{
            return location;
        }
        
        bool operator < (const UniformInfo other) const {
            if(this->getType() < other.getType()) return true;
            return this->getName() < other.getName();
        }

        std::string toString() { 
            std::ostringstream os(std::ostringstream::out);
            os << name << " " << location << " " << type << std::endl;
            return os.str();
        }

    private:

        int location;        

        UniformType type;

        std::string name;
    };

    class UniformValue {
    public:
        virtual UniformType getType() = 0;

        virtual void bindValueOn(GPUProgram * program, const UniformInfo & info, OpenGL * ogl) = 0;
    };

    // Declaration of the UniformValues

    class UniformFloatVec4 : public UniformValue {
    public:
        UniformFloatVec4() {
            values[0] = 0.0f;
            values[1] = 0.0f;
            values[2] = 0.0f;
            values[3] = 0.0f;
        }

        UniformFloatVec4(const float & x, const float & y, const float & z, const float & w) {
            values[0] = x;
            values[1] = y;
            values[2] = z;
            values[3] = w;
        }

        UniformType getType() {
            return FLOAT_VEC4;
        }
        
        void setValue(const float & x, const float & y, const float & z, const float & w) {
            values[0] = x;
            values[1] = y;
            values[2] = z;
            values[3] = w;
        }

        void setValue(const math3d::vector4 & v) {
            this->setValue(v[0], v[1], v[2], v[3]);
        }

        void bindValueOn(GPUProgram * program, const UniformInfo & info, OpenGL * ogl);

    private:
        float values[4];
    };

    class UniformFloatVec3 : public UniformValue {
    public:
        UniformFloatVec3() {
            values[0] = 0.0f;
            values[1] = 0.0f;
            values[2] = 0.0f;
        }

        UniformFloatVec3(const float & x, const float & y, const float & z) {
            values[0] = x;
            values[1] = y;
            values[2] = z;
        }

        UniformType getType() {
            return FLOAT_VEC3;
        }
        
        void setValue(const float & x, const float & y, const float & z) {
            values[0] = x;
            values[1] = y;
            values[2] = z;
        }

        void bindValueOn(GPUProgram * program, const UniformInfo & info, OpenGL * ogl);

    private:
        float values[3];
    };

    class UniformFloatVec2 : public UniformValue {
    public:
        UniformFloatVec2() {
            values[0] = 0.0f;
            values[1] = 0.0f;
        }

        UniformFloatVec2(const float & x, const float & y) {
            values[0] = x;
            values[1] = y;
        }

        UniformType getType() {
            return FLOAT_VEC2;
        }
        
        void setValue(const float & x, const float & y) {
            values[0] = x;
            values[1] = y;
        }

        void bindValueOn(GPUProgram * program, const UniformInfo & info, OpenGL * ogl);

    private:
        float values[2];
    };

    class UniformFloat : public UniformValue {
    public:
        UniformFloat() {
            value = 0.0f;
        }

        UniformFloat(const float & v) {
            value = v;
        }

        UniformType getType() {
            return FLOAT;
        }
        
        void setValue(const float & v) {
            value = v;
        }

        void bindValueOn(GPUProgram * program, const UniformInfo & info, OpenGL * ogl);

    private:
        float value;
    };
}
#endif
