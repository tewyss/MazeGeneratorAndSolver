#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
// once font loaded we can use it everywhere via `auto &font = FontManager::getFont();`
struct FontManager {
  static sf::Font &getFont() {
    static sf::Font font;
    [[maybe_unused]]
    static bool loaded = []() {
      if (not font.loadFromFile("assets/fonts/Matrix_Mono.ttf")) {
        throw std::runtime_error("Failed to load font");
      }
      return true;
    }();
    return font;
  }
};