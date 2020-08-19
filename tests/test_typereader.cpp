#include "catch_main.h"
#include "catch2.hpp"
#include "OpenType.h"

#include <iostream>
#include <iomanip>

TEST_CASE("convert 2 chars to a UINT16", "[TypeReader]" ) {
    std::vector<char> bytes = { char(0xAA), char(0xBB) };
    auto reader = OpenType::TypeReader(bytes);
    REQUIRE( reader.readUInt16() == 0xAABB );
}

TEST_CASE("convert 4 chars to a UINT32", "[TypeReader]" ) {
    std::vector<char> bytes = { char(0xAA), char(0xBB), char(0xCC), char(0xDD) };
    auto reader = OpenType::TypeReader(bytes);
    REQUIRE( reader.readUInt32() == 0xAABBCCDD );
}

TEST_CASE("conver tag", "[TypeReader]" ) {
    std::vector<char> bytes = { 'A', 'B', 'C', 'D' };
    auto reader = OpenType::TypeReader(bytes);
    REQUIRE( reader.readTag() == "ABCD" );
}
