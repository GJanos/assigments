#include "mystack.h"
#include <cstring>
#include <iostream>

template <class T>
inline Fontys::stackObject<T>::stackObject() : obj(nullptr), next(nullptr)
{
}

template <class T>
inline Fontys::stackMeta<T>::stackMeta() : stack(nullptr), numelem(0)
{
    stackObject<T> *iter = stack;
    while (iter != NULL)
    {
        stackObject<T> *next = iter->next;
        delete iter->obj;
        delete iter;
        iter = next;
    }
    stack = iter;
}

template <typename T>
inline Fontys::stackMeta<T>::~stackMeta()
{
}

template <typename T>
inline int Fontys::stackMeta<T>::push(T *obj)
{
    stackObject<T> *new_obj = new stackObject<T>();
    if (!new_obj)
        return -1;

    new_obj->obj = new T();
    memcpy(new_obj->obj, obj, sizeof(T));
    delete obj;

    /*
    new_obj->obj = std::move(obj);
    delete obj;
    */

    std::cout << *(new_obj->obj) << "\n";
    if (numelem != 0)
        new_obj->next = stack;

    stack = new_obj;
    numelem++;
    return 0;
}

template <typename T>
inline int Fontys::stackMeta<T>::pop(T *obj)
{
    if (stack == nullptr || numelem == 0)
        return -1;

    stackObject<T> *second = stack->next;

    if (obj != nullptr)
        memcpy(obj, stack->obj, sizeof(T));

    if (stack->obj != NULL)
        delete stack->obj;
    if (stack != NULL)
        delete stack;

    stack = second;
    numelem--;
    return 0;
}

template <typename T>
inline int Fontys::stackMeta<T>::nofelem()
{
    return numelem;
}