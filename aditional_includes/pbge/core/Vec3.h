

#ifndef vec3_h
#define vec3_h 1

namespace pbge {
    template <class Type>
    class GenericVec3 {
    public:
        GenericVec3(Type x, Type y, Type z) {
            this->set(x,y,z);
        }

        GenericVec3() {}

        void set(Type x, Type y, Type z) {
            data[0] = x; 
            data[1] = y;
            data[2] = z;
        }

        Type * getData() {
            return data;
        }

        Type & operator [] (int i) { 
            return data[i]; 
        }
        const Type & operator [] (int i) const { 
            return e[i]; 
        }
    private:
        Type data[3];
    };

    typedef GenericVec3<float> Vec3;
    typedef GenericVec3<float> Vec3f;
    typedef GenericVec3<int> Vec3i;
    typedef GenericVec3<unsigned char> Vec3ub;
}

#endif

