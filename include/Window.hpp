#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <iostream>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    void clear();
    void display();
    
    // NOUVEAU : Une méthode pour changer le titre proprement
    void setTitle(const std::string& title); 

    SDL_Renderer* getRenderer() const { return renderer; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};