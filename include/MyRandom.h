//
// Created by HORIA on 23.05.2024.
//

#ifndef IMAGEBANANA_MYRANDOM_H
#define IMAGEBANANA_MYRANDOM_H

#include <random>

float getRand() {
    static std::random_device rd {};
    static std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    static std::mt19937 mt {ss};
    static std::uniform_real_distribution<float> dist {0, 1};

    return dist(mt);
}

#endif //IMAGEBANANA_MYRANDOM_H
