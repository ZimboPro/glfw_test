#ifndef COPLIEN_HPP
#define COPLIEN_HPP

/**
 * @brief A template copy function
 * 
 * @tparam T 
 * @param dst 
 * @param src 
 */
template<typename T>
void copy(T & dst, const T & src)
{
    T temp = src;
    dst = temp;
}


/**
 * @brief A template copy array function
 * 
 * @tparam T 
 * @tparam N 
 */
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