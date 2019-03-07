#ifndef HLIB_OBJECT_H
#define HLIB_OBJECT_H

namespace HLib
{

#ifndef NULL
#define NULL 0
#endif

#ifndef NO_EXCEPT
#define NO_EXCEPT throw()
#endif

#ifdef __x86_64__
    #ifndef SIZE_T
    #define SIZE_T unsigned long
    #endif
#endif

#ifndef __x86_64__
    #ifndef SIZE_T
    #define SIZE_T unsigned int
    #endif
#endif

// 顶层父类Object: 统一动态内存规划
// HLib所有class直接或间接继承Object
class Object
{
public:
    void* operator new (SIZE_T size) NO_EXCEPT;
    void  operator delete (void* ptr) NO_EXCEPT;
    void* operator new[] (SIZE_T size) NO_EXCEPT;
    void  operator delete[] (void* ptr) NO_EXCEPT;
    bool  operator == (const Object& obj) NO_EXCEPT;
    bool  operator != (const Object& obj) NO_EXCEPT;

    virtual ~Object() NO_EXCEPT = 0;
};

} // namespace HLib

#endif // HLIB_OBJECT_H
