//
// Created by Titus Wolfe on 3/15/26.
//

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include "main.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <list>
#include "util/Telemetry.h"
#include "util/RollingAverage.h"
#include "util/Convert.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

#define APP_NAME "SDL Awesomeness"
#define APP_VERSION "1.0"
#define APP_IDENTIFIER "online.pagma.sdl-awesomeness"

#define WINDOW_TITLE "SDL Awesomeness"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Uint64 lastTime = 0;

RollingAverage deltaTimeAverage = RollingAverage(200);
RollingAverage avgFPS = RollingAverage(1000);

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_Log("SDL_AppInit");
    SDL_SetAppMetadata(APP_NAME, APP_VERSION, APP_IDENTIFIER);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_T:
                setIsEnabled(!getIsEnabled());
                break;
            case SDLK_ESCAPE:
                return SDL_APP_SUCCESS;
            default: break;
        }
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

    const Uint64 runtimeNS = SDL_GetTicksNS();
    const double runtimeSec = nsToSec(runtimeNS);
    const Uint64 deltaTimeNS = runtimeNS - lastTime;
    const double deltaTimeMS = nsToMs(deltaTimeNS);
    const double deltaTimeSec = nsToSec(deltaTimeNS);
    const double framesPerSecond = 1 / deltaTimeSec;

    deltaTimeAverage.addSample(deltaTimeMS);
    avgFPS.addSample(framesPerSecond);

    const double cosRuntime = cos(runtimeSec);
    const double sinRuntime = sin(runtimeSec);
    const double tanRuntime = tan(runtimeSec);

    SDL_SetRenderDrawColor(renderer, 0, 20, 100, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */

    SDL_SetRenderScale(renderer, 4.0f, 4.0f);
    SDL_RenderDebugText(renderer, 50, 0, "Hello Jonny!");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    SDL_FRect rect = {
        (float) (WINDOW_WIDTH / 2 + cosRuntime * 50),
        (float) (WINDOW_HEIGHT / 2 + sinRuntime * 50),
        50,
        50
    };
    SDL_RenderFillRect(renderer, &rect);

    // SDL_Texture texture = SDL_Texture();
    // SDL_Vertex vertices[];
    // SDL_RenderGeometry(renderer, &texture, vertices, 3, NULL, 5);

    addTelemetry("SDL Awesomeness - Press T to toggle telemetry display");
    addTelemetry("Runtime Sec", runtimeSec);
    addTelemetry("cos(runtime)", cosRuntime);
    addTelemetry("sin(runtime)", sinRuntime);
    addTelemetry("delta time (ms)", deltaTimeMS);
    addTelemetry("avrg. delta time (ms)", deltaTimeAverage.getAverage());
    addTelemetry("fps", framesPerSecond);
    addTelemetry("Rolling Average FPS :)", avgFPS.getAverage());
    updateTelemetry(renderer);


    SDL_RenderPresent(renderer);

    lastTime = runtimeNS;

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Log("SDL_AppQuit");
}