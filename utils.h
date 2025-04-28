#ifndef UTILS
#define UTILS

#include <stdexcept>
#include <vector>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <iostream>

namespace utils
{
    using bitArray = std::vector<bool>;
    using byteArray = std::vector<unsigned int>;
    const unsigned int BYTE_SIZE = 8;
    const int d = 12;
    const int q = 3329;

    // Converts a bit array (of a length that is a multiple of eight) into an array of bytes
    //  little endian order - https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.203.pdf
    byteArray
    bitsToBytes(const bitArray &bits)
    {
        const unsigned int b_size = bits.size();

        if (b_size % BYTE_SIZE != 0)
        {
            throw std::runtime_error("Bit array length must be multiples of BYTE_SIZE");
        }

        if (std::find_if_not(bits.begin(), bits.end(), [](const bool &bit)
                             { return bit != 0 || bit != 1; }) != bits.end())
        {
            throw std::runtime_error("Bit array must only contain 1s and 0s");
        }

        byteArray bytes(b_size / BYTE_SIZE, 0);

        for (unsigned int i = 0; i < b_size; i++)
        {
            const unsigned int idx = i == 0 ? i : i / BYTE_SIZE;
            bytes[idx] = bytes[idx] + (bits[i] * std::pow(2, i % BYTE_SIZE));
        }

        return bytes;
    }

    // Performs the inverse of bitsToBytes, converting a byte array into a bit array
    bitArray bytesToBits(const byteArray &bytes)
    {
        byteArray bytes_copy = bytes;
        const unsigned int b_size = bytes.size();
        bitArray bits(b_size * BYTE_SIZE, 0);

        for (unsigned int i = 0; i < b_size; i++)
        {
            for (unsigned int j = 0; j < BYTE_SIZE; j++)
            {
                const unsigned int bits_idx = BYTE_SIZE * i + j;
                bits[bits_idx] = bytes_copy[i] % 2;
                bytes_copy[i] = bytes_copy[i] / 2;
            }
        }

        return bits;
    }

    // Encodes an array of 𝑑-bit integers into a byte array for 1 ≤ 𝑑 ≤ 12.
    byteArray byteEncode(const std::vector<int> &nums)
    {
        const size_t NUMS_SIZE = 256;
        if (nums.size() != NUMS_SIZE)
        {
            throw std::runtime_error("input array must contain 256 integers");
        }

        bitArray bits(NUMS_SIZE * d, 0);

        for (unsigned int i = 0; i < nums.size(); i++)
        {
            int a = nums[i];
            for (unsigned int j = 0; j < d; j++)
            {
                unsigned int bits_idx = i * d + j;
                bits[bits_idx] = a % 2;
                a = (a - bits[bits_idx]) / 2;
            }
        }

        return bitsToBytes(bits);
    }

    // Decodes a byte array into an array of 𝑑-bit integers for 1 ≤ 𝑑 ≤ 12.
    std::vector<int> bytesDecode(const byteArray &bytes)
    {
        bitArray bits = bytesToBits(bytes);

        const size_t NUMS_SIZE = 256;
        const unsigned int m = d < 12 ? std::pow(2, d) : q;
        std::vector<int> nums(NUMS_SIZE, 0);

        for (unsigned int i = 0; i < NUMS_SIZE; i++)
        {
            int sum = 0;
            for (unsigned int j = 0; j < d - 1; j++)
            {
                unsigned int bits_idx = i * d + j;
                sum += bits[bits_idx] * (int(pow(2, j)) % m);
            }

            nums[i] = sum;
        }

        return nums;
    }
}

#endif