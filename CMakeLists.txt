cmake_minimum_required(VERSION 3.14) # GTest a besoin d'une version récente
project(TileTwister)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- 1. DÉPENDANCES (SDL3 & GTest) ---
include(FetchContent)

# SDL3
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.0
)
FetchContent_MakeAvailable(SDL3)

# SDL3_ttf
FetchContent_Declare(
  SDL3_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_ttf)

# Google Test (NOUVEAU)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# Pour éviter que GTest n'écrase nos options de compilation sur Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

# --- 2. LISTE DES FICHIERS COMMUNS ---
# Ces fichiers sont utilisés à la fois par le JEU et par les TESTS.
# On n'inclut PAS main.cpp ici car les tests ont leur propre main() !
set(CORE_SOURCES
    src/Game.cpp
    src/Game_Render.cpp
    src/Window.cpp
    src/Grid.cpp
    src/Grid_Movement.cpp
    src/Grid_Check.cpp
)

# --- 3. EXÉCUTABLE DU JEU ---
add_executable(TileTwister 
    src/main.cpp 
    ${CORE_SOURCES} # On ajoute les fichiers communs
)
target_link_libraries(TileTwister PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)

# --- 4. EXÉCUTABLE DES TESTS ---
enable_testing()

add_executable(UnitTests
    tests/test_moves.cpp
    ${CORE_SOURCES} # On réutilise la logique du jeu
)

# On lie les tests à GTest et aussi à SDL (car Game.cpp en a besoin pour compiler)
target_link_libraries(UnitTests PRIVATE 
    GTest::gtest_main 
    SDL3::SDL3 
    SDL3_ttf::SDL3_ttf
)

include(GoogleTest)
gtest_discover_tests(UnitTests)