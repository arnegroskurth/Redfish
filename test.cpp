
#include <iostream>
#include <bitset>

#include "src/Constants.hpp"

int main() {

    std::cout << HAS_SET_BITS_64(uint64_t(0)) << std::endl;
    std::cout << HAS_SET_BITS_64(uint64_t(1)) << std::endl;
    std::cout << HAS_SET_BITS_64(uint64_t(16)) << std::endl;
    std::cout << HAS_SET_BITS_64(uint64_t(4096)) << std::endl;

    std::cout << HAS_SET_BITS_32(uint32_t(0)) << std::endl;
    std::cout << HAS_SET_BITS_32(uint32_t(1)) << std::endl;
    std::cout << HAS_SET_BITS_32(uint32_t(16)) << std::endl;
    std::cout << HAS_SET_BITS_32(uint32_t(4096)) << std::endl;

    std::cout << HAS_SET_BITS_8(uint8_t(0)) << std::endl;
    std::cout << HAS_SET_BITS_8(uint8_t(1)) << std::endl;
    std::cout << HAS_SET_BITS_8(uint8_t(16)) << std::endl;
    std::cout << HAS_SET_BITS_8(uint8_t(250)) << std::endl;


    return 0;
}