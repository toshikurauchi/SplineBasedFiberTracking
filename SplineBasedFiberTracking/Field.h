#ifndef field_h
#define field_h

#include <string>
#include <iterator>

#include "Vector.h"

class Field
{
public:
    static Field fromFile(std::string fileName, pbge::OpenGL * ogl);
private:
    Field(int x, int y, int z);
    Vector ***field;
};

//class FieldIterator : public std::iterator<std::input_iterator_tag, Vector>{
//}

#endif