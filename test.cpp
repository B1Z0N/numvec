#include "basic_vector.hpp"
#include <iostream>

using namespace forvec;

template <typename T>
std::ostream &operator<<(std::ostream &os, const Numvec<T> &vec)
// output for debugging
{
    if (vec.is_empty())
        return os << "[ ]";

    os << "[" << vec[0];
    if (vec.size() >= 1)
    {
        for (int i = 1; i < vec.size(); i++)
        {
            os << ", " << vec[i];
        }
    }
    return os << "]";
}

template <typename __first, typename __second>
bool pack_equal(__first first, __second second)
{
    return first == second;
}

template <typename __first, typename __second, typename... __args>
bool pack_equal(__first first, __second second, __args... args)
{
    return first == second && pack_equal(second, args...);
}

Numvec<int> test_move()
{
    return {1, 2, 3};
}

int main()
{
    //testing constructors and assignments
    using ntype = Numvec<int>;
    using cntype = const ntype;
    cntype a1{};
    cntype a2 = {};
    cntype a3{a1};
    cntype a4 = a1;
    cntype a5(0);

    std::cout << pack_equal(a1, a2, a3, a4, a5);

    cntype b1{1, 2, 3};
    cntype b2 = {1, 2, 3};
    cntype b3 = b2;

    std::cout << pack_equal(b1, b2, b3);

    cntype c1{0, 0};
    cntype c2(2);

    std::cout << pack_equal(c1, c2);

    cntype d1{test_move()};
    cntype d2 = test_move();

    std::cout << pack_equal(d1, d2);

}
