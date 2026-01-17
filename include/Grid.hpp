#pragma once
#include <array>

class Grid {
public:   // Ici on mettra les actions possibles (bouger, afficher...)
    Grid();
    void display(); // <--- Nouvelle fonction pour afficher
    void spawnRandomTile(); // <--- Nouvelle fonction
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    bool checkWin();
    bool checkGameOver();

    int getTile(int x, int y) const; // Lecture seule d'une case

    void setTile(int x, int y, int value); // Pour les tests

    static const int TARGET = 2048;

private: // Ici on met les données cachées (les nombres)
    std::array<std::array<int, 4>, 4> data;
};