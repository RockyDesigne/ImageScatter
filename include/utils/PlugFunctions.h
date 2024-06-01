//
// Created by HORIA on 31.05.2024.
//

#ifndef IMAGEBANANA_PLUGFUNCTIONS_H
#define IMAGEBANANA_PLUGFUNCTIONS_H

#include "AnimationEngine.h"

using UPDATE_PTR = void (*)(AnimationEngine*);
using ANIM_PTR = AnimationEngine* (*)(void);
using DEST_PTR = void (*)(AnimationEngine*);

#endif //IMAGEBANANA_PLUGFUNCTIONS_H
