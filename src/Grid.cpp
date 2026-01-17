#include "../include/Grid.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

Grid::Grid() {
    // Initialisation à 0
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = 0;
        }
    }
    spawnRandomTile();
    spawnRandomTile();
}

void Grid::display() {
    std::cout << "-----------------" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "| ";
        for (int j = 0; j < 4; j++) {
            if (data[i][j] == 0) std::cout << ". ";
            else std::cout << data[i][j] << " ";
            std::cout << "| ";
        }
        std::cout << std::endl;
        std::cout << "-----------------" << std::endl;
    }
}

void Grid::spawnRandomTile() {
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (data[i][j] == 0) emptyCells.push_back({i, j});
        }
    }

    if (emptyCells.empty()) return;

    int randomIndex = rand() % emptyCells.size();
    std::pair<int, int> target = emptyCells[randomIndex];
    int value = (rand() % 10 == 0) ? 4 : 2;
    data[target.first][target.second] = value;
}

int Grid::getTile(int x, int y) const {
    if (x >= 0 && x < 4 && y >= 0 && y < 4) {
        return data[x][y];
    }
    return -1; // Erreur
}

void Grid::setTile(int x, int y, int value) {
    if (x >= 0 && x < 4 && y >= 0 && y < 4) {
        data[x][y] = value;
    }
}