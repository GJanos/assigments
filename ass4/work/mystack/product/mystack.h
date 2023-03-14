#ifndef __MYSTACKH__
#define __MYSTACKH__

namespace Fontys
{
    template <typename T>
    struct stackObject
    {
        T *obj;
        stackObject *next;
        stackObject();
    };

    template <typename T>
    class stackMeta
    {
    private:
        stackObject<T> *stack;
        int numelem;

    public:
        stackMeta();
        ~stackMeta();
        int push(T *obj);
        int pop(T *obj);
        int nofelem();
    };
}

#endif