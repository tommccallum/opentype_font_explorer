#include "catch_main.h"
#include "catch2.hpp"
#include "OpenType.h"

#include <iostream>
#include <iomanip>

using namespace OpenType;

TEST_CASE("read offset table from verdana", "[OffsetTable]" ) {
    auto reader = FontReader( ttf_path );
    auto offset_table = OffsetTable();

    offset_table.from_bytes( reader );
    REQUIRE( offset_table.get_sfnt_version() == 0x00010000 );
}

TEST_CASE("read all table records using OffsetTable", "[OffsetTable]" ) {
    auto reader = FontReader( ttf_path );
    auto offset_table = OffsetTable();

    offset_table.from_bytes( reader );
    std::cout << offset_table << std::endl;
}
