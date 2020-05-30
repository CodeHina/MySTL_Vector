#ifndef V_STACK_H_INCLUDED
#define V_STACK_H_INCLUDED
#include "Vector.h"

template<typename T>
class V_Stack : public Vector<T>
{
public:

    void push(const T& e)
    {
        this->put_back(e);
    }
    T pop()
    {
        return this->Remove(this->get_size()-1);
    }
    T& top()
    {
        return (*this)[this->get_size()-1];       //Vector对象已经重载了[]
    }
    void show_base()
    {
        int n = this->get_size();
        while(n--)
            std::cout << this->pop();
    }

    bool IsEmpty()
    {
        return !this->get_size();
    }



};






#endif // V_STACK_H_INCLUDED
