cmake_minimum_required(VERSION 3.10)
project(TileTwister)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# 1. SDL3 (Base)
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.0
)
FetchContent_MakeAvailable(SDL3)

# 2. SDL3_ttf (Texte)
FetchContent_Declare(
  SDL3_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG main  
)
FetchContent_MakeAvailable(SDL3_ttf)

include_directories(include)

add_executable(TileTwister 
    src/main.cpp
    src/Game.cpp
    src/Game_Render.cpp
    src/Grid.cpp
    src/Grid_Movement.cpp
    src/Grid_Check.cpp
    src/Window.cpp
)

# On lie SDL3 et SDL3_ttf
target_link_libraries(TileTwister PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)