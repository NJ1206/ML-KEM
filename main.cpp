#include "utils.h"
#include <iostream>

int main()
{
    utils::bitArray bits = {0, 1, 0, 1, 0, 1, 0, 1};
    auto bytes = utils::bitsToBytes(bits);
    for (auto byte : bytes)
    {
        std::cout << byte << " ";
    }

    for (auto bit : utils::bytesToBits(bytes))
    {
        std::cout << bit << " ";
    }
}