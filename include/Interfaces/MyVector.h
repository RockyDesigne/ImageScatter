//
// Created by HORIA on 23.05.2024.
//

#ifndef IMAGEBANANA_MYVECTOR_H
#define IMAGEBANANA_MYVECTOR_H

#include <cctype>
#include <array>

template<typename T, std::size_t N>
class MyVector {
public:
    std::size_t m_size = 0;
    std::array<T, N> elems { {} };

    virtual void push(const T& item) = 0;

};

#endif //IMAGEBANANA_MYVECTOR_H
