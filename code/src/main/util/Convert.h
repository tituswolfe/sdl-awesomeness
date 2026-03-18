//
// Created by Titus Wolfe on 3/16/26.
//

#ifndef SDLAWESOMENESS_CONVERT_H
#define SDLAWESOMENESS_CONVERT_H
#include "SDL3/SDL_stdinc.h"


class Convert {
};

static double nsToSec(const Uint64 ns) {
    return static_cast<double>(ns) / 1e+9;
}

static double nsToMs(const Uint64 ns) {
    return static_cast<double>(ns) / 1e+6;
}


#endif //SDLAWESOMENESS_CONVERT_H