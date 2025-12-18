#include "../include/Grid.hpp"

bool Grid::checkWin() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // On vérifie si on a atteint la cible définie dans le .hpp
            if (data[i][j] == Grid::TARGET) {
                return true;
            }
        }
    }
    return false;
}

bool Grid::checkGameOver() {
    // 1. Cases vides ?
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (data[i][j] == 0) return false;
        }
    }
    // 2. Fusions possibles ?
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Droite
            if (j < 3 && data[i][j] == data[i][j + 1]) return false;
            // Bas
            if (i < 3 && data[i][j] == data[i + 1][j]) return false;
        }
    }
    return true;
}