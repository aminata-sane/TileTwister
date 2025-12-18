#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Game.hpp"

int main(int argc, char* argv[]) { // Signature main pour SDL
    std::srand(std::time(nullptr)); 

    Game myGame;
    myGame.runGraphics(); // <--- On lance le mode graphique !

    return 0;
}