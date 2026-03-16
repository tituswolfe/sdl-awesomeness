cmake_minimum_required(VERSION 3.20)
project(SDLAwesomeness CXX)

set(CMAKE_CXX_STANDARD 17)

# 1. Include the FetchContent module
include(FetchContent)

# 2. Declare the SDL3 dependency
# We point directly to the official GitHub and a specific tag (or 'main')
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        main  # You can also use a specific version like 'v3.1.6'
)

# Optional: Disable SDL3 features you don't need to speed up your build
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)

# 3. Download and make the SDL3 targets available
FetchContent_MakeAvailable(SDL3)

# 4. Find OpenGL (This is still system-dependent because it talks to your GPU drivers)
find_package(OpenGL REQUIRED)

# 5. Define your executable
add_executable(My3DEngine Code/src/main/main.cpp
        code/src/main/util/telemetry.cpp
        code/src/main/util/telemetry.h
        code/src/main/geometry/Vertex.cpp
        code/src/main/geometry/Vertex.h
        code/src/main/math/Vector.cpp
        code/src/main/math/Vector.h
        code/src/main/rendering/camera.cpp
        code/src/main/rendering/camera.h
        code/src/main/util/RollingAverage.cpp
        code/src/main/util/RollingAverage.h)

# 6. Link against the SDL3 target created by FetchContent
# Use SDL3::SDL3-shared or SDL3::SDL3-static depending on preference
target_link_libraries(My3DEngine PRIVATE SDL3::SDL3 OpenGL::GL)

# macOS specific: Silence OpenGL deprecation warnings
if(APPLE)
    target_compile_definitions(My3DEngine PRIVATE
            GL_SILENCE_DEPRECATION
            SDL_DISABLE_OLD_NAMES # This will stop the "renamed" error and just say "Function not found"
    )
endif()