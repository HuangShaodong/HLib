#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace HLib
{

// HLib中容器类不允许拷贝构造和拷贝赋值
template <typename T>
class List : public Object
{
protected:
    List(const List<T>&);
    List<T>& operator = (const List<T>&);
public:
    List();
    virtual bool insert(const int pos, const T& elem) = 0;
    virtual bool insert_front(const T& elem) = 0;
    virtual bool insert_back(const T& elem) = 0;
    virtual bool remove(const int pos) = 0;
    virtual bool remove_front() = 0;
    virtual bool remove_back() = 0;
    virtual bool set(const int pos, const T& elem) = 0;
    virtual bool get(const int pos, T& elem) const NO_EXCEPT = 0;
    virtual T get(const int pos) const = 0;
    virtual int find(const T& elem) const = 0;
    virtual int length() const NO_EXCEPT = 0;
    virtual void clear() = 0;
};


template<typename T>
List<T>::List()
{}

} // namespace HLib

#endif // LIST_H
