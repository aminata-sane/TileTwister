# TileTwister

Un jeu de puzzle où vous devez tordre les tuiles pour gagner.

## Compatibilité

Ce jeu utilise SDL3 et est compatible avec Windows, macOS et Linux, à condition que les dépendances soient installées.

## Prérequis

- CMake (version 3.10 ou supérieure)
- Un compilateur C++ supportant C++17 (comme GCC, Clang, ou MSVC)
- Pour Windows : Visual Studio ou MinGW

Les dépendances SDL3 et SDL3_ttf sont téléchargées automatiquement via CMake.

## Compilation

### Sur macOS/Linux

1. Ouvrez un terminal et allez dans le dossier du projet :
   ```
   cd /chemin/vers/TileTwister
   ```

2. Créez un dossier build :
   ```
   mkdir build
   cd build
   ```

3. Configurez avec CMake :
   ```
   cmake ..
   ```

4. Compilez :
   ```
   make
   ```

### Sur Windows

1. Ouvrez une invite de commande ou PowerShell et allez dans le dossier du projet.

2. Créez un dossier build :
   ```
   mkdir build
   cd build
   ```

3. Configurez avec CMake (en supposant Visual Studio) :
   ```
   cmake .. -G "Visual Studio 16 2019"
   ```
   Ou pour MinGW :
   ```
   cmake .. -G "MinGW Makefiles"
   ```

4. Compilez :
   - Avec Visual Studio : Ouvrez TileTwister.sln et build.
   - Avec MinGW : `mingw32-make`

## Lancement

Après compilation, lancez le jeu :
```
./TileTwister
```
Sur Windows, c'est `TileTwister.exe`

## Tests

Le projet inclut des tests unitaires avec Google Test. Après compilation, lancez les tests :
```
./UnitTests
```

## Dépannage

- Assurez-vous que CMake est installé.
- Pour Windows, installez Visual Studio avec le développement C++ ou MinGW.


## Rappel des bonnes pratiques :
     
   ## Pour MacOs: 
- Pour configurer : cd build && cmake ..
- Pour compiler : cd build && make
- Pour lancer le jeu : cd build && ./TileTwister
- Pour lancer les tests : cd build && ./UnitTests

    ## Pour Windows avec MinGW :

Configurer : cd build && cmake .. -G "MinGW Makefiles"
Compiler : cd build && mingw32-make
Lancer le jeu : cd build && TileTwister.exe
Lancer les tests : cd build && UnitTests.exe

   ## Pour Windows avec Visual Studio :

Configurer : cd build && cmake .. -G "Visual Studio 16 2019" (adapte la version)
Compiler : Ouvre TileTwister.sln dans Visual Studio et build, ou utilise msbuild TileTwister.sln en ligne de commande.
Lancer le jeu : cd build && TileTwister.exe
Lancer les tests : cd build && UnitTests.exe


Les dépendances (SDL3, Google Test) sont téléchargées automatiquement via CMake, donc ça devrait marcher sur Windows aussi, tant que CMake et un compilateur sont installés.