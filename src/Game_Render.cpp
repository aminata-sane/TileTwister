#include "../include/Game.hpp"
#include <SDL3/SDL.h>
#include <string> 

void Game::render() {
    // 1. On efface l'écran via notre classe Window
    window.clear(); 

    // 2. On dessine les tuiles
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            drawTile(i, j, grid.getTile(i, j));
        }
    }

    // 3. Overlay (Victoire / Défaite)
    if (hasWon) {
        drawEndScreen("VICTOIRE !", {237, 194, 46, 200}); 
    }
    else if (grid.checkGameOver()) {
        drawEndScreen("GAME OVER", {60, 58, 50, 200});
    }

    // 4. On affiche le tout
    window.display();
}

void Game::drawEndScreen(std::string message, SDL_Color bgColor) {
    if (!font) return;

    // --- CORRECTION ICI ---
    // On récupère le renderer depuis l'objet window
    SDL_Renderer* renderer = window.getRenderer();
    // ----------------------

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, NULL); 
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

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
    // --- CORRECTION ICI ---
    // On récupère le renderer depuis l'objet window
    SDL_Renderer* renderer = window.getRenderer();
    // ----------------------

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