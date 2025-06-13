#pragma once

#include "ConfigureMenu.h"
#include "MainMenu.h"
#include "Maze.h"
#include "EndScreen.h"

bool runMenus(sf::RenderWindow &window, ConfigSettings &outCfg);
Maze buildAndGenerateMaze(sf::RenderWindow &window, const ConfigSettings &cfg);
void applyCycles(sf::RenderWindow &window, Maze &maze, double prob);
void solveMaze(sf::RenderWindow &window, Maze &maze, const ConfigSettings &cfg);
void responsivePause(sf::RenderWindow &window, Maze &maze, float secs);
bool handleReconfigure(sf::RenderWindow &window, ConfigSettings &cfg);

void runGenerationCycle(sf::RenderWindow &window, Maze &maze,
                        const ConfigSettings &cfg);

void runEndScreenLoop(sf::RenderWindow &window, Maze &maze,
                      ConfigSettings &cfg);