#include <iostream>
#include "basic_vector.hpp"

using namespace forvec;

int main()
{
    Numvec<int> a {1, 2, 3};
    Numvec<int> b {1, 2, 3};
    auto c {a};

    std::cout << (a == c);


    return 0;
}