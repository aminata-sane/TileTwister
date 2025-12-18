#pragma once
#include <SDL3/SDL.h> // <--- On inclut SDL3
#include "Grid.hpp"

class Game {
public:
    Game();
    ~Game(); // Destructeur pour nettoyer la SDL à la fin

    void runGraphics(); // Nouvelle fonction pour le mode graphique

private:
    Grid grid;
    bool isRunning;
    bool hasWon;

    // --- Variables SDL ---
    SDL_Window* window;
    SDL_Renderer* renderer;
    const int WINDOW_SIZE = 600;
    const int TILE_SIZE = 130;
    const int PADDING = 15;
    // ---------------------

    void handleEvents();    // Gère clavier/souris
    void render();          // Dessine tout à l'écran
    void drawTile(int x, int y, int value); // Dessine un carré
    void checkGameStatus();
};