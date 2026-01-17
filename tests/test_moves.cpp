#include <gtest/gtest.h>
#include "../include/Grid.hpp"

// Test : Vérifier que le mouvement vers la gauche fusionne bien
TEST(GridTest, MoveLeftShouldMerge) {
    // 1. Mise en place (Setup)
    Grid grid;
    
    // On nettoie tout (on met des 0 partout)
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            grid.setTile(i, j, 0);
        }
    }

    // On prépare une situation connue : [2, 2, 0, 0] sur la première ligne
    grid.setTile(0, 0, 2);
    grid.setTile(0, 1, 2);

    // 2. Action
    grid.moveLeft();

    // 3. Vérification (Assert)
    // On s'attend à avoir [4, 0, 0, 0]
    EXPECT_EQ(grid.getTile(0, 0), 4) << "Les deux 2 auraient dû fusionner en 4";
    EXPECT_EQ(grid.getTile(0, 1), 0) << "La deuxième case devrait être vide";
}

// Test : Vérifier que ça ne fusionne pas n'importe quoi
TEST(GridTest, MoveLeftNoMergeDifferentValues) {
    Grid grid;
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) grid.setTile(i, j, 0);

    // Situation : [2, 4, 0, 0]
    grid.setTile(0, 0, 2);
    grid.setTile(0, 1, 4);

    grid.moveLeft();

    // Résultat attendu : [2, 4, 0, 0] (rien ne bouge)
    EXPECT_EQ(grid.getTile(0, 0), 2);
    EXPECT_EQ(grid.getTile(0, 1), 4);
}