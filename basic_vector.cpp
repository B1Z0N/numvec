#include "basic_vector.hpp"

int Numvec::_check_length(int length)
{
    if (len < 0)
        throw IncorrectLength;

    return length;
};

Numvec::Numvec(int length)
    : len{_check_length(length)}, arr{new T[len]}
{
    for (int i = 0; i < len; i++)
        arr[i]{};
}

Numvec::Numvec(T *array, int length)
    : len{_check_length(length)}, arr{new T[len]}
{
    uninitialized_copy(array, array + len, arr);
}

Numvec::Numvec(initializer_list<T> lst)
    : len{lst.size()}, arr{new T[len]}
{
    uninitialized_copy(lst.begin(), lst.end(), arr);
}

//...
Numvec::Numvec(const Numvec& obj)
{
    arr = 
}
Numvec::Numvec& operator = (const Numvec& obj);
Numvec::Numvec(Numvec&& obj);
Numvec::Numvec& operator = (Numvec&& obj);

Numvec::~Numvec() { delete[] arr; }



//...