#include "../include/Game.hpp"
#include <iostream>
#include <string>

Game::Game() {
    isRunning = true;
    hasWon = false;
    window = nullptr;
    renderer = nullptr;
}

// Le destructeur nettoie la mémoire quand l'objet Game est détruit
Game::~Game() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::runGraphics() {
    // 1. Initialisation SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erreur SDL_Init : " << SDL_GetError() << std::endl;
        return;
    }

    // 2. Création Fenêtre et Renderer
    if (!SDL_CreateWindowAndRenderer("Tile Twister - SDL3", 600, 600, 0, &window, &renderer)) {
        std::cerr << "Erreur Fenêtre/Renderer : " << SDL_GetError() << std::endl;
        return;
    }

    // 3. Boucle principale du jeu
    while (isRunning) {
        handleEvents();     // Écouter le clavier
        checkGameStatus();  // Vérifier victoire/défaite
        render();           // Dessiner
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        } 
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            bool moved = false;
            switch (event.key.key) {
                case SDLK_UP:    grid.moveUp(); moved = true; break;
                case SDLK_DOWN:  grid.moveDown(); moved = true; break;
                case SDLK_LEFT:  grid.moveLeft(); moved = true; break;
                case SDLK_RIGHT: grid.moveRight(); moved = true; break;
                case SDLK_ESCAPE: isRunning = false; break;
            }

            if (moved) {
                grid.spawnRandomTile();
                // On pourrait ajouter un petit son ici plus tard
            }
        }
    }
}

void Game::checkGameStatus() {
    if (!hasWon && grid.checkWin()) {
        std::cout << "VICTOIRE ! (Regarde la console)" << std::endl;
        hasWon = true; 
        SDL_SetWindowTitle(window, "Tile Twister - VICTOIRE !");
    }
    if (grid.checkGameOver()) {
        std::cout << "PERDU !" << std::endl;
        SDL_SetWindowTitle(window, "Tile Twister - GAME OVER");
    }
}

