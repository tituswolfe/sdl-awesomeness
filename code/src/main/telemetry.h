//
// Created by Titus Wolfe on 3/15/26.
//

#ifndef MY3DENGINE_TELEMETRY_H
#define MY3DENGINE_TELEMETRY_H

#include <string>
#include <list>
#include "SDL3/SDL_render.h"

static constexpr int LINE_SPACING = 10;

static std::list<std::string> telemetryLines;

class telemetry {
};

static void addTelemetry(const std::string& line) {
    telemetryLines.push_back(line);
}

static void updateTelemetry(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    int lineNum = 0;
    for (const std::string& line : telemetryLines) {
        SDL_RenderDebugText(renderer, 0, lineNum * LINE_SPACING, line.c_str());
        lineNum++;
    }

    telemetryLines.clear();
}


#endif //MY3DENGINE_TELEMETRY_H