#pragma once

#include "Maze.h"
#include <iostream>

enum class EndScreenResult { Reconfigure, Exit };

EndScreenResult showEndScreen(sf::RenderWindow &window, const Maze &maze);
