#include <iostream>
#include <cstdint>

int main() {
    uint64_t x64in = 0xBBAAFFEEDDCCBBAA;
    uint64_t x64out = 0x0L;

    // _byteswap_ushort
    //_byteswap_ulong
    // _byteswap_uint64
    x64out = __bswap_64( x64in );
    std::cout << std::hex << x64in << "=" << x64out << std::endl;

    uint64_t x32in = 0xDDCCBBAA;
    uint64_t x32out = 0x0L;

    // _byteswap_ushort
    //_byteswap_ulong
    // _byteswap_uint64
    x32out = __bswap_32( x32in );
    std::cout << std::hex << x32in << "=" << x32out << std::endl;

    uint64_t x16in = 0xBBAA;
    uint64_t x16out = 0x0L;

    // _byteswap_ushort
    //_byteswap_ulong
    // _byteswap_uint64
    x16out = __bswap_16( x16in );
    std::cout << std::hex << x16in << "=" << x16out << std::endl;

    return 0;
}
