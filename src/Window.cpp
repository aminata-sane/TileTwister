#include "../include/Window.hpp"

Window::Window(const std::string& title, int width, int height) 
    : window(nullptr), renderer(nullptr) 
{
    // 1. On initialise la Vidéo
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erreur SDL_Init : " << SDL_GetError() << std::endl;
    }

    // 2. On crée la fenêtre et le renderer
    if (!SDL_CreateWindowAndRenderer(title.c_str(), width, height, 0, &window, &renderer)) {
        std::cerr << "Erreur création Fenêtre : " << SDL_GetError() << std::endl;
    }
}

Window::~Window() {
    // Nettoyage automatique
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit(); 
}

void Window::clear() {
    // Fond Gris foncé du jeu 2048
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_RenderClear(renderer);
}

void Window::display() {
    SDL_RenderPresent(renderer);
}

void Window::setTitle(const std::string& title) {
    SDL_SetWindowTitle(window, title.c_str());
}