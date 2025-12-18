#include "../include/Game.hpp"
#include <SDL3/SDL.h>
#include <string> // Nécessaire pour convertir int en string

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255); 
    SDL_RenderClear(renderer);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            drawTile(i, j, grid.getTile(i, j));
        }
    }
    SDL_RenderPresent(renderer);
}

void Game::drawTile(int x, int y, int value) {
    // 1. Fond coloré
    float xPos = (y * (TILE_SIZE + PADDING)) + PADDING; 
    float yPos = (x * (TILE_SIZE + PADDING)) + PADDING; 
    SDL_FRect tileRect = {xPos, yPos, (float)TILE_SIZE, (float)TILE_SIZE};

    switch (value) {
        case 0:    SDL_SetRenderDrawColor(renderer, 205, 193, 180, 255); break;
        case 2:    SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255); break;
        case 4:    SDL_SetRenderDrawColor(renderer, 237, 224, 200, 255); break;
        case 8:    SDL_SetRenderDrawColor(renderer, 242, 177, 121, 255); break;
        case 16:   SDL_SetRenderDrawColor(renderer, 245, 149, 99,  255); break;
        case 32:   SDL_SetRenderDrawColor(renderer, 246, 124, 95,  255); break;
        case 64:   SDL_SetRenderDrawColor(renderer, 246, 94,  59,  255); break;
        default:   
            if (value > 2048) SDL_SetRenderDrawColor(renderer, 60, 58, 50, 255);
            else SDL_SetRenderDrawColor(renderer, 237, 207, 114, 255); 
            break;
    }
    SDL_RenderFillRect(renderer, &tileRect);

    // 2. Texte (Chiffre)
    if (value != 0 && font) {
        // Couleur du texte : Foncé pour 2 et 4, Blanc pour le reste
        SDL_Color textColor = (value <= 4) ? SDL_Color{119, 110, 101, 255} : SDL_Color{249, 246, 242, 255};

        SDL_Surface* textSurface = TTF_RenderText_Blended(font, std::to_string(value).c_str(), 0, textColor);
        
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            
            // Centrage
            float textW = (float)textSurface->w;
            float textH = (float)textSurface->h;
            SDL_FRect textRect = {
                xPos + (TILE_SIZE - textW) / 2,
                yPos + (TILE_SIZE - textH) / 2,
                textW, textH
            };

            SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

            SDL_DestroySurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }
}