# Note: CMake 4.2 does not exist yet (the current series is 3.x).
# If CMake throws a version error, change this back to 3.14 or your installed version.
cmake_minimum_required(VERSION 4.2)

# Explicitly mark that we are using both C++ (for your code/EnTT) and C (for Raylib)
project(SimmRayy CXX C)

# 1. Setup Compiler Cache (ccache) for near-instant branch switching
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}") # Caches Raylib's C files
endif()

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# 2. Declare Dependencies
# --- EnTT ---
FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG        v3.16.0
)

# --- Raylib ---
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        6.0
)

# 3. Optimize Raylib Build Flags
# These MUST come before FetchContent_MakeAvailable
set(BUILD_EXAMPLES OFF CACHE BOOL "Disable Raylib examples" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "Disable Raylib games" FORCE)

# 4. Download and configure both libraries
FetchContent_MakeAvailable(entt raylib)

# 5. Setup your application
add_executable(SimmRayy src/main.cpp)

# 6. Link libraries to your executable
target_link_libraries(SimmRayy PRIVATE EnTT::EnTT raylib)