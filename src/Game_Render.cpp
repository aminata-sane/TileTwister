#include "../include/Game.hpp"
#include <SDL3/SDL.h>
#include <string> // Pour std::to_string

void Game::render() {
    // 1. Fond et Grille
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255); 
    SDL_RenderClear(renderer);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            drawTile(i, j, grid.getTile(i, j));
        }
    }

    // 2. Vérification de l'état pour l'Overlay (Victoire/Défaite)
    if (hasWon) {
        // Or semi-transparent
        drawEndScreen("VICTOIRE !", {237, 194, 46, 200}); 
    }
    else if (grid.checkGameOver()) {
        // Rouge sombre semi-transparent
        drawEndScreen("GAME OVER", {60, 58, 50, 200});
    }

    // 3. Affichage final
    SDL_RenderPresent(renderer);
}

void Game::drawEndScreen(std::string message, SDL_Color bgColor) {
    if (!font) return;

    // Activer la transparence
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Fond semi-transparent
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, NULL); 

    // Remettre le mode normal pour le texte
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // Texte en Blanc
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, message.c_str(), 0, white);
    
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        
        float textW = (float)textSurface->w;
        float textH = (float)textSurface->h;
        
        SDL_FRect textRect = {
            (WINDOW_SIZE - textW) / 2,
            (WINDOW_SIZE - textH) / 2,
            textW, textH
        };

        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

        SDL_DestroySurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
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
        SDL_Color textColor = (value <= 4) ? SDL_Color{119, 110, 101, 255} : SDL_Color{249, 246, 242, 255};
        
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, std::to_string(value).c_str(), 0, textColor);
        
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            
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