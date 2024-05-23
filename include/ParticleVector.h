//
// Created by HORIA on 23.05.2024.
//

#ifndef IMAGEBANANA_PARTICLEVECTOR_H
#define IMAGEBANANA_PARTICLEVECTOR_H

#include "MyVector.h"
#include "Particle.h"
#include <cctype>
#include <cassert>

template<std::size_t N>
class ParticleVector : public MyVector<Particle, N> {
public:
    void push(const Particle& p) override {
        assert(this->m_size < N && "Particles buffer overflow!");
        this->elems[this->m_size].color = p.color;
        this->elems[this->m_size].oX = p.oX;
        this->elems[this->m_size].oY = p.oY;
        this->elems[this->m_size].x = p.x;
        this->elems[this->m_size].y = p.y;
        this->elems[this->m_size].vx = p.vx;
        this->elems[this->m_size].vy = p.vy;
        ++this->m_size;
    }

    void reset() {
            this->m_size = 0;
    }

};

#endif //IMAGEBANANA_PARTICLEVECTOR_H
