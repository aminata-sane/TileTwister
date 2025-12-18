#include "../include/Game.hpp"
#include <SDL3/SDL.h>

// Ce fichier ne gère QUE l'affichage graphique

void Game::render() {
    // 1. Fond de la fenêtre (Gris foncé)
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255); 
    SDL_RenderClear(renderer);

    // 2. On parcourt toutes les cases de la grille
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // On récupère la valeur
            int val = grid.getTile(i, j);
            // On dessine le carré
            drawTile(i, j, val);
        }
    }

    // 3. Affichage final
    SDL_RenderPresent(renderer);
}

void Game::drawTile(int x, int y, int value) {
    // Calcul de la position
    float xPos = (y * (TILE_SIZE + PADDING)) + PADDING; 
    float yPos = (x * (TILE_SIZE + PADDING)) + PADDING; 

    SDL_FRect tileRect = {xPos, yPos, (float)TILE_SIZE, (float)TILE_SIZE};

    // Choix de la couleur
    switch (value) {
        case 0:    SDL_SetRenderDrawColor(renderer, 205, 193, 180, 255); break;
        case 2:    SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255); break;
        case 4:    SDL_SetRenderDrawColor(renderer, 237, 224, 200, 255); break;
        case 8:    SDL_SetRenderDrawColor(renderer, 242, 177, 121, 255); break;
        case 16:   SDL_SetRenderDrawColor(renderer, 245, 149, 99,  255); break;
        case 32:   SDL_SetRenderDrawColor(renderer, 246, 124, 95,  255); break;
        case 64:   SDL_SetRenderDrawColor(renderer, 246, 94,  59,  255); break;
        case 128:  SDL_SetRenderDrawColor(renderer, 237, 207, 114, 255); break;
        case 256:  SDL_SetRenderDrawColor(renderer, 237, 204, 97,  255); break;
        case 512:  SDL_SetRenderDrawColor(renderer, 237, 200, 80,  255); break;
        case 1024: SDL_SetRenderDrawColor(renderer, 237, 197, 63,  255); break;
        case 2048: SDL_SetRenderDrawColor(renderer, 237, 194, 46,  255); break;
        default:   SDL_SetRenderDrawColor(renderer, 60,  58,  50,  255); break;
    }

    SDL_RenderFillRect(renderer, &tileRect);
}