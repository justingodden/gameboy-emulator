#include <string>
#include "Cart.h"
#include "Gameboy.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        std::string romPath(argv[1]);
        Cart *cart = new Cart(romPath);
        Gameboy gameboy = Gameboy(cart);

        delete cart;
        return 0;
    }

    return 1;
}