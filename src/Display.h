#pragma once

#include <array>
#include <stdint.h>
#include <SFML/Graphics.hpp>

class Display
{
public:
    Display();
    ~Display();

public:
    void update(std::array<uint8_t, 160 * 144 * 4> screenData);

private:
    sf::RenderWindow *window = nullptr;
    sf::Texture *texture = nullptr;
    sf::Sprite *sprite = nullptr;
    sf::Uint8 *pixels = new sf::Uint8[64 * 32 * 4];

    uint8_t width = 160;
    uint8_t height = 144;
    uint8_t scaleFactor = 3;
};