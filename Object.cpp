#include "Object.h"

#include <malloc.h>

namespace HLib
{

void* Object::operator new (SIZE_T size)     NO_EXCEPT
{
    return malloc(size);
}

void Object::operator delete (void* ptr)     NO_EXCEPT
{
    free(ptr);
}

void* Object::operator new[] (SIZE_T size)   NO_EXCEPT
{
    return malloc(size);
}

void Object::operator delete[] (void* ptr)   NO_EXCEPT
{
    free(ptr);
}

bool Object::operator == (const Object& obj) NO_EXCEPT
{
    return (this == &obj);
}

bool Object::operator != (const Object& obj) NO_EXCEPT
{
    return (this != &obj);
}

Object::~Object() NO_EXCEPT
{}

} // namespace HLib
