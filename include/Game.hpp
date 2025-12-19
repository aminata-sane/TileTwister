#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h> // <--- NOUVEAU : Importation pour le texte
#include "Grid.hpp"
#include "Window.hpp"

class Game {
public:
    Game();
    ~Game();

    void runGraphics();

private:
    Grid grid;
    Window window;
    bool isRunning;
    bool hasWon;
    TTF_Font* font; // La variable qui garde la police en mémoire

    const int WINDOW_SIZE = 600;
    const int TILE_SIZE = 130;
    const int PADDING = 15;

    void handleEvents();
    void render();
    void drawTile(int x, int y, int value);
    void checkGameStatus();
    void drawEndScreen(std::string message, SDL_Color color); // Fonction pour dessiner l'écran de fin
};