#include "utils.h"
#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    utils::bitArray bits = {0, 1, 0, 1, 0, 1, 0, 1};
    auto bytes = utils::bitsToBytes(bits);
    for (auto byte : bytes)
    {
        std::cout << byte << " ";
    }

    std::cout << std::endl;

    for (auto bit : utils::bytesToBits(bytes))
    {
        std::cout << bit << " ";
    }

    std::cout << std::endl;

    std::vector<int> nums;
    for (int i = 0; i < 256; i++)
    {
        int num = rand() % 3329;
        std::cout << num << " ";
        nums.push_back(num);
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    auto bytesEncoded = utils::byteEncode(nums);

    for (auto num : utils::bytesDecode(bytesEncoded))
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
}