#include "../include/Game.hpp"
#include <iostream>
#include <string>

Game::Game() {
    isRunning = true;
    hasWon = false;
    window = nullptr;
    renderer = nullptr;
    font = nullptr; // <--- On initialise à null par sécurité
}

Game::~Game() {
    if (font) TTF_CloseFont(font); // <--- On ferme la police proprement
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit(); // <--- On éteint le module texte
    SDL_Quit();
}

void Game::runGraphics() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erreur SDL : " << SDL_GetError() << std::endl;
        return;
    }

    // 1. Initialisation du système de texte
    if (!TTF_Init()) {
        std::cerr << "Erreur TTF_Init : " << SDL_GetError() << std::endl;
        return;
    }

    // 2. Chargement de la police
    font = TTF_OpenFont("../assets/MyCustomFont.ttf", 64.0f);
    
    if (!font) {
        std::cerr << "Erreur chargement police : " << SDL_GetError() << std::endl;
        // On continue quand même, mais sans texte
    }

    if (!SDL_CreateWindowAndRenderer("Tile Twister - SDL3", 600, 600, 0, &window, &renderer)) {
        std::cerr << "Erreur Fenêtre : " << SDL_GetError() << std::endl;
        return;
    }

    while (isRunning) {
        handleEvents();
        checkGameStatus();
        render();
    }
}

// ... Le reste (handleEvents, checkGameStatus) ne change pas
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) isRunning = false;
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            bool moved = false;
            switch (event.key.key) {
                case SDLK_UP:    grid.moveUp(); moved = true; break;
                case SDLK_DOWN:  grid.moveDown(); moved = true; break;
                case SDLK_LEFT:  grid.moveLeft(); moved = true; break;
                case SDLK_RIGHT: grid.moveRight(); moved = true; break;
                case SDLK_ESCAPE: isRunning = false; break;
            }
            if (moved) grid.spawnRandomTile();
        }
    }
}

void Game::checkGameStatus() {
    if (!hasWon && grid.checkWin()) {
        hasWon = true; 
        SDL_SetWindowTitle(window, "Tile Twister - VICTOIRE !");
    }
    if (grid.checkGameOver()) {
        SDL_SetWindowTitle(window, "Tile Twister - GAME OVER");
    }
}