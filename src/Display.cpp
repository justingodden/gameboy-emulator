#include "Display.h"

Display::Display()
{
    window = new sf::RenderWindow;
    texture = new sf::Texture;
    sprite = new sf::Sprite;
    texture->create(width, height);

    window->create(sf::VideoMode(width * scaleFactor, height * scaleFactor), "Game Boy Emulator");
}

Display::~Display()
{
    delete window;
    delete texture;
    delete sprite;
    delete pixels;
}

void Display::update(std::array<uint8_t, 160 * 144 * 4> screenData)
{
    // incredibly inefficient. figure out how to type cast an array
    for (uint i = 0; i < 160 * 144 * 4; i += 4)
    {
        pixels[i * 4] = screenData.at(i);
        pixels[(i * 4) + 1] = screenData.at(i + 1);
        pixels[(i * 4) + 2] = screenData.at(i + 2);
        pixels[(i * 4) + 3] = screenData.at(i + 3);
    }

    texture->update(pixels);
    sprite->setTexture(*texture);
    sprite->setScale(scaleFactor, scaleFactor);
    window->draw(*sprite);
}