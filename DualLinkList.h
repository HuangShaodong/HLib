#ifndef HLIB_DUALLINKLIST_H
#define HLIB_DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace HLib
{

template <typename T>
class DualLinkList : public List<T>
{
    struct Node : public Object
    {
        T value;
        Node* pre;
        Node* next;
    };

    mutable struct : public Object
    {
        char buf[sizeof(T)];
        Node* pre;
        Node* next;
    } m_head;

    int m_length;
    Node* m_curr;
    int m_step;

    Node* position(const int pos) const NO_EXCEPT;

public:
    DualLinkList();
    bool insert(const int pos, const T& elem);
    bool insert_front(const T& elem);
    bool insert_back(const T& elem);
    bool remove(const int pos);
    bool remove_front();
    bool remove_back();
    bool set(const int pos, const T& elem);
    bool get(const int pos, T& elem) const NO_EXCEPT;
    T get(const int pos) const;
    int find(const T& elem) const;
    int length() const NO_EXCEPT;
    void clear();

    bool move(const int pos, const int step = 1);
    bool next() NO_EXCEPT;
    bool pre() NO_EXCEPT;
    bool end() const NO_EXCEPT;
    T current() const;

    ~DualLinkList();
};


template<typename T>
typename DualLinkList<T>::Node* DualLinkList<T>::position(const int pos) const NO_EXCEPT
{
    Node* ret = reinterpret_cast<Node*>(&m_head);

    for( int p=0; p<pos; p++ )
    {
        ret = ret->next;
    }

    return ret;
}


template<typename T>
DualLinkList<T>::DualLinkList()
{
    m_head.pre = NULL;
    m_head.next = NULL;
    m_length = 0;
    m_curr = NULL;
    m_step = 1;
}


template<typename T>
bool DualLinkList<T>::insert(const int pos, const T& elem)
{
    bool ret = ( (0 <= pos) && (pos <= m_length) );

    if( ret )
    {
        Node* node = new Node();

        if( node )
        {
            node->value = elem;

            Node* curr = position(pos);
            Node* next = curr->next;
            
            node->next = next;
            curr->next = node;

            // 是否首节点插入
            if( reinterpret_cast<Node*>(&m_head) != curr )
            {
                node->pre = curr;
            }
            else
            {
                node->pre = NULL;
            }

            // 是否尾首节点插入
            if( next )
            {
                next->pre = node;
            }

            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node...");
        }
    }

    return ret;
}


template<typename T>
bool DualLinkList<T>::insert_front(const T& elem)
{
    return insert(0, elem);
}


template<typename T>
bool DualLinkList<T>::insert_back(const T& elem)
{
    return insert(m_length, elem);
}


template<typename T>
bool DualLinkList<T>::remove(const int pos)  // O(n)
{
    bool ret = ( (0 <= pos) && (pos < m_length) );

    if( ret )
    {
        Node* curr = position(pos);
        Node* toDel = curr->next;
        Node* next = toDel->next;

        curr->next = next;

        // 非尾节点删除
        if( next )
        {
            next->pre = toDel->next;
        }

        m_length--;
        delete toDel;
    }

    return ret;
}


template<typename T>
bool DualLinkList<T>::remove_front() // O(1)
{
    return remove(0);
}


template<typename T>
bool DualLinkList<T>::remove_back()  // O(n)
{
    return remove(m_length-1);
}


template<typename T>
bool DualLinkList<T>::set(const int pos, const T& elem)  //O(n)
{
    bool ret = ( (0 <= pos) && (pos < m_length) );

    if( ret )
    {
        position(pos)->next->value = elem;
    }

    return ret;
}


template<typename T>
bool DualLinkList<T>::get(const int pos, T& elem) const NO_EXCEPT  // O(n)
{
    bool ret = ( (0 <= pos) && (pos < m_length) );

    if( ret )
    {
        elem = position(pos)->next->value;
    }

    return ret;
}

template<typename T>
T DualLinkList<T>::get(const int pos) const
{
    T ret;

    if( !get(pos, ret) )
    {
        THROW_EXCEPTION(InvalidOperationException, "parameter pos is OutofBound...");
    }

    return ret;
}


template<typename T>
int DualLinkList<T>::find(const T& elem) const  // O(n)
{
    int ret = -1;

    int curr = 0;
    Node* node = m_head.next;

    while( node )
    {
        if( elem == node->value )
        {
            ret = curr;
            break;
        }

        curr++;
        node = node->next;
    }

    return ret;
}


template<typename T>
inline int DualLinkList<T>::length() const NO_EXCEPT
{
    return m_length;
}


template<typename T>
void DualLinkList<T>::clear()
{
    Node* node = m_head.next;

    while( node )
    {
        Node* toDel = node;

        m_head.next = node->next;

        m_length--;
        delete toDel;
    }
}


template<typename T>
bool DualLinkList<T>::move(const int pos, const int step)
{
    bool ret = ( (0 <= pos) && (pos < m_length) );

    if( ret )
    {
        m_curr = position(pos)->next;
        m_step = step;
    }

    return ret;
}


template<typename T>
bool DualLinkList<T>::next() NO_EXCEPT
{
    int i = 0;

    while( (i < m_step) && (!end()) )
    {
        m_curr = m_curr->next;
        i++;
    }

    return (i == m_step);
}


template<typename T>
bool DualLinkList<T>::pre() NO_EXCEPT
{
    int i = 0;

    while( (i < m_step) && (!end()) )
    {
        m_curr = m_curr->pre;
        i++;
    }

    return (i == m_step);
}


template<typename T>
bool DualLinkList<T>::end() const NO_EXCEPT
{
    return (NULL == m_curr);
}


template<typename T>
T DualLinkList<T>::current() const
{
    if( !end() )
    {
        return m_curr->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
    }
}


template<typename T>
DualLinkList<T>::~DualLinkList()
{
    clear();
}


} // namespace HLib

#endif // HLIB_DUALLINKLIST_H
