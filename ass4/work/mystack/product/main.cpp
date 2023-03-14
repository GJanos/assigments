#include "mystack.h"
#include <iostream>

int main()
{
    Fontys::stackMeta<double> stack;
    double *test = new double(15.3);
    double *test2 = new double(3.3);
    stack.push(test);
    stack.push(test2);
    double *ret1 = new double;
    stack.pop(ret1);
    delete ret1;
    std::cout << stack.nofelem() << "   " << *test << " " << *test2 << "\n";

    return 0;
}