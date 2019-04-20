#include <iostream>
#include <initializer_list>
#include <memory>

using namespace std;

namespace forvec
{
const unsigned int START_RESERVED = 5;

template <typename T>
class Numvec
{
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
    size_type size() const;
    size_type capacity() const;
    bool is_empty() const;

    // element access
    T &at(size_type n) const;
    T &operator[](size_type n) const;
    T *data() const;
    T &front() const;
    T &back() const;

    // modify
    void push_back(const T &elem);
    void plus_back(const Numvec<T> vec);
    void pop_back();
    void clear() noexcept;

    bool operator==(const Numvec<T> &other) const;

    //...
private:
    T *arr;
    size_type len = 0;
    size_type reserved = START_RESERVED;

    int _check_length(int length);
    void reallocate();
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
    arr = new T[reserved];
}

template <typename T>
Numvec<T>::Numvec(typename Numvec<T>::size_type n)
{
    reserved = n << 2; // n * 4
    arr = new T[reserved];
    for (size_type i = 0; i < n; i++)
    {
        arr[i] = T(); // default constructor call
    }

    len = n;
}

template <typename T>
Numvec<T>::Numvec(T *array, size_type length)
    : len{length}, reserved{len * 4}, arr{new T[reserved]}
{
    for (size_type i = 0; i < length; i++)
    {
        arr[i] = T();
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
{
    len = lst.size();
    reserved = len * 4;
    arr = new T[reserved];

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
{
    len = obj.size();
    arr = new T[reserved];

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
Numvec<T> &Numvec<T>::operator=(Numvec<T> &&obj)
{
    len = obj.size(); 
    arr = obj.data();
}

template <typename T>
Numvec<T>::~Numvec() { delete[] arr; }

template <typename T>
typename Numvec<T>::size_type Numvec<T>::size() const { return len; }

template <typename T>
typename Numvec<T>::size_type Numvec<T>::capacity() const { return reserved; }

template <typename T>
bool Numvec<T>::is_empty() const { return (!len); }

template <typename T>
T &Numvec<T>::at(size_type n) const
{
    if (n >= len)
        throw BadLength {};

    return arr[n];
}

template <typename T>
T &Numvec<T>::operator[](size_type n) const
{
    return arr[n];
}

template <typename T>
T *Numvec<T>::data() const { return arr; }

template <typename T>
T &Numvec<T>::front() const { return arr[0]; }

template <typename T>
T &Numvec<T>::back() const { return arr[len - 1]; }

template <typename T>
void Numvec<T>::push_back(const T &elem)
{
    if (len == reserved)
    {
        reserved = reserved << 2;
        reallocate();
    }

    arr[len++] = elem;
}

template <typename T>
void Numvec<T>::plus_back(const Numvec<T> vec)
{
    size_type after_len = len + vec.size();
    if (after_len > reserved)
    {
        reserved = after_len << 2;
        reallocate();
    }

    for (size_type i = len, j = 0; i < after_len; i++, j++)
    {
        arr[i] = vec[j];
    }
}

template <typename T>
void Numvec<T>::pop_back() { len--; }

template <typename T>
void Numvec<T>::clear() noexcept { len = 0; }

template <typename T>
bool Numvec<T>::operator==(const Numvec<T> &other) const
{
    if (len != other.size())
        return false;

    T *p = other.data();
    for (size_type i = 0; i < len; i++)
    {
        if (p[i] != arr[i])
            return false;
    }

    return true;
}

} // namespace forvec