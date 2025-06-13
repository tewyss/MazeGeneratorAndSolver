#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class MenuResult { Configure, Exit };

MenuResult showMainMenu(sf::RenderWindow &window);