#include "catch_main.h"
#include "catch2.hpp"
#include "OpenType.h"

#include <iostream>
#include <iomanip>

using namespace OpenType;

TEST_CASE("read table record from verdana", "[TableRecord]" ) {
    auto reader = FontReader( ttf_path );
    // we need to read the offset_table first
    auto offset_table = OffsetTable();
    offset_table.from_bytes(reader);

    // reader keeps track of where it is
    // DSIG
    auto table_record = TableRecord();
    table_record.from_bytes( reader );
    REQUIRE( table_record.get_tag() == "DSIG" );

    // reader keeps track of where it is
    // LTSH
    table_record = TableRecord();
    table_record.from_bytes( reader );
    REQUIRE( table_record.get_tag() == "LTSH" );

    // reader keeps track of where it is
    // OS/2
    table_record = TableRecord();
    table_record.from_bytes( reader );
    REQUIRE( table_record.get_tag() == "OS/2" );
}
