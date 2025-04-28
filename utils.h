#ifndef UTILS
#define UTILS

#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace utils
{
    using bitArray = std::vector<bool>;

    // little endian order - https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.203.pdf
    std::vector<unsigned int> bitsToBytes(const bitArray &bits)
    {
        const unsigned int b_size = bits.size();

        if (b_size % 8 != 0)
        {
            throw std::runtime_error("Bit array length must be multiples of 8");
        }

        if (std::find_if_not(bits.begin(), bits.end(), [](const bool &bit)
                             { return bit != 0 || bit != 1; }) != bits.end())
        {
            throw std::runtime_error("Bit array must only contain 1s and 0s");
        }

        std::vector<unsigned int> bytes(b_size / 8, 0);

        for (unsigned int i = 0; i < b_size; i++)
        {
            const unsigned int idx = i == 0 ? i : i / 8;
            bytes[idx] = bytes[idx] + (bits[i] * std::pow(2, i % 8));
        }

        return bytes;
    }

    bitArray bytesToBits(const std::vector<unsigned int> &bytes)
    {
        std::vector<unsigned int> bytes_copy = bytes;
        const unsigned int b_size = bytes.size();
        bitArray bits(b_size * 8, 0);

        for (unsigned int i = 0; i < b_size; i++)
        {
            for (unsigned int j = 0; j < 8; j++)
            {
                const unsigned int bits_idx = 8 * i + j;
                bits[bits_idx] = bytes_copy[i] % 2;
                bytes_copy[i] = bytes_copy[i] / 2;
            }
        }

        return bits;
    }

}

#endif