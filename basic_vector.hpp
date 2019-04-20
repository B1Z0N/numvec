#include <iostream>
#include <initializer_list>
#include <memory>

using namespace std;

namespace forvec
{
const START_RESERVED = 5;

template <typename T>
class Numvec
{
    T *arr;
    size_type len = 0;
    size_type reserved = START_RESERVED;

    int _check_length(int length);
    void reallocate();

public:
    //types
    typedef unsigned int size_type;

    // exceptions
    class BadLength
    {
    };

    // constructors, copy, move, destructors
    Numvec() noexcept;
    explicit Numvec(size_type length); // constructors
    Numvec(T *array, size_type length);
    Numvec(initializer_list<T> lst);
    Numvec<T> &operator=(initializer_list<T> lst);

    Numvec(const Numvec<T> &obj); // copy operations
    Numvec<T> &operator=(const Numvec<T> &obj);

    Numvec(Numvec<T> &&obj) noexcept; // move operations
    Numvec<T> &operator=(Numvec<T> &&obj);

    ~Numvec();

    // capacity
    size_type size();
    size_type capacity();
    bool is_empty();

    // element access
    T &at(int n);
    T &operator[](size_type n);
    T *data();
    T &front();
    T &back();

    // modify
    void push_back(const T &elem);
    void plus_back(const Numvec<T> vec);
    void pop_back();
    void clear() noexcept;

    bool operator==(const Numvec<T> &a, const Numvec<T> &b);

    //...
};

template <typename T>
void Numvec<T>::reallocate()
{
    T *ptr = new T[reserved];
    for (size_type i = 0; i < len; i++)
    {
        ptr[i] = arr[i];
    }

    delete[] arr;
    arr = ptr;
}

template <typename T>
Numvec<T>::Numvec() noexcept
{
    arr = new T[reserved]
}

template <typename T>
Numvec<T>::Numvec(typename Numvec<T>::size_type n)
{
    reserved = n << 2; // n * 4
    arr = new T[reserved];
    for (size_type i = 0; i < n; i++)
    {
        arr[i]{}; // default constructor call
    }

    len = n;
}

template <typename T>
Numvec<T>::Numvec(T *array, size_type length)
    : len{length}, reserved{len * 4}, {new T[reserved]}
{
    for (size_type i = 0; i < n; i++)
    {
        arr[i]{};
    }
}

template <typename T>
Numvec<T>::Numvec(initializer_list<T> lst)
    : len{lst.size()}, reserved{len * 4}, arr{new T[reserved]}
{
    uninitialized_copy(lst.begin(), lst.end(), arr);
}

template <typename T>
Numvec<T> &Numvec<T>::operator=(initializer_list<T> lst)
    : len{lst.size()}, reserved{len * 4}, arr{new T[reserved]}
{
    return *this;
}

template <typename T>
Numvec<T>::Numvec(const Numvec<T> &obj)
    : len{obj.size()}, reserved{obj.capacity()}, arr{new T[reserved]}
{
    for (size_type i = 0; i < len; i++)
    {
        arr[i] = obj[i];
    }
}

template <typename T>
Numvec<T> &Numvec<T>::operator=(const Numvec<T> &obj)
    : len{obj.size()}, arr{new T[reserved]}
{
    if (reserved < len)
    {
        reserved = len << 2;
        reallocate();
    }

    for (size_type i = 0; i < len; i++)
    {
        arr[i] = obj[i];
    }
}

template <typename T>
Numvec<T>::Numvec(Numvec<T> &&obj) noexcept
    : len{obj.size()}, arr{obj.data()} {}

template <typename T>
Numvec<T>::Numvec<T> &operator=(Numvec<T> &&obj)
    : len{obj.size()}, arr{obj.data()} {}

~Numvec();

} // namespace forvec