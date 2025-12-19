#include "../include/Game.hpp"
#include <iostream>
#include <string>

// Le constructeur initialise l'objet 'window', ce qui ouvre la fenêtre SDL automatiquement
Game::Game() : window("Tile Twister - SDL3", 600, 600) {
    isRunning = true;
    hasWon = false;
    font = nullptr;
}

Game::~Game() {
    if (font) TTF_CloseFont(font);
    TTF_Quit();
    // Pas besoin de détruire window ou renderer, le destructeur de la classe Window le fera.
}

void Game::runGraphics() {

    // 1. Initialisation du système de texte
    if (!TTF_Init()) {
        std::cerr << "Erreur TTF_Init : " << SDL_GetError() << std::endl;
        return;
    }

    // 2. Chargement de la police
    font = TTF_OpenFont("../assets/MyCustomFont.ttf", 64.0f);
    
    if (!font) {
        std::cerr << "Erreur chargement police : " << SDL_GetError() << std::endl;
    }

    while (isRunning) {
        handleEvents();
        checkGameStatus();
        render();
    }
}

void Game::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        } 
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            
            // Verrouillage fin de partie
            if (grid.checkGameOver() || hasWon) {
                if (event.key.key == SDLK_ESCAPE) {
                    isRunning = false;
                }
                continue; 
            }

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
            }
        }
    }
}

void Game::checkGameStatus() {
    if (!hasWon && grid.checkWin()) {
        hasWon = true; 
        // CORRECTION : On utilise la méthode de notre classe Window
        window.setTitle("Tile Twister - VICTOIRE !");
    }
    if (grid.checkGameOver()) {
        window.setTitle("Tile Twister - GAME OVER");
    }
}