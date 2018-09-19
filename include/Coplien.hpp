#ifndef COPLIEN_HPP
#define COPLIEN_HPP

template<typename T>
void copy(T & dst, const T & src)
{
    T temp = src;
    dst = temp;
}

template<typename T, size_t N>
void copyArr(T (& dst)[N], const T (& src)[N])
{
    for (size_t i = 0; i < N; i++)
    {
        T temp = src[i];
        dst[i] = temp;
    }
}

#endif