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

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

#define APP_NAME "SDL Awesomeness"
#define APP_VERSION "1.0"
#define APP_IDENTIFIER "online.pagma.sdl-awesomeness"

#define WINDOW_TITLE "SDL Awesomeness"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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
            case SDLK_A:
                SDL_Log("THE USER PRESSED A OH NO!");
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
    const double runtimeSec = SDL_GetTicks() / 1000.0;
    const double cosRuntime = cos(runtimeSec);
    const double sinRuntime = sin(runtimeSec);
    const double tanRuntime = tan(runtimeSec);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */

    SDL_SetRenderScale(renderer, 4.0f, 4.0f);
    SDL_RenderDebugText(renderer, 50, 0, "Hello Jonny!");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    SDL_FRect rect = {
        (float) (WINDOW_WIDTH / 2 + sinRuntime * 100.0),
        (float) (WINDOW_HEIGHT / 2 + cosRuntime * 100.0),
        50,
        50
    };
    SDL_RenderFillRect(renderer, &rect);

    addTelemetry("SDL Awesomeness");
    addTelemetry("Runtime Sec", static_cast<Uint64>(runtimeSec));
    addTelemetry("cos(runtime)", cosRuntime);
    addTelemetry("sin(runtime)", sinRuntime);
    updateTelemetry(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Log("SDL_AppQuit");
}