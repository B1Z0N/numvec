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
bool _pack_equal(__first first, __second second)
{
    return first == second;
}

template <typename __first, typename __second, typename... __args>
bool _pack_equal(__first first, __second second, __args... args)
{
    return first == second && _pack_equal(second, args...);
}

// template <typename T>
// bool check_meq()
// {
//     for(int i = 0; i < lst.size() - 1; i++)
//     {
//         if(lst[i] != lst[i + 1]) return false;
//     }

//     return true;
// }

int main()
{
    const Numvec<int> a1{};
    const Numvec<int> a2 = {};
    const Numvec<int> a3{a1};
    const Numvec<int> a4 = a1;
    const Numvec<int> a5(0);

    // std::cout << (a1 == a2 == a3 == a4 == a5);
    // std::cout << check_multiple_equality(1, 1, 1);
    std::cout << _pack_equal(1, 2, 3, 4, 5);
}
