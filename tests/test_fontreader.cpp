#include "catch_main.h"
#include "catch2.hpp"
#include "OpenType.h"

SCENARIO( "ttf file can be read", "[FontReader]" ) {
    GIVEN("a ttf file") {
        WHEN("the non-existent file is read") {
            THEN("test for has_data should be false") {
                OpenType::FontReader reader("file_not_here.ttf");
                REQUIRE( reader.has_data() == false );
            }
        }
    }
}

SCENARIO( "ttf file can be read 2", "[FontReader]" ) {
    GIVEN("a ttf file") {
        WHEN("the existing file is read") {
            THEN("test for has_data should be true") {
                OpenType::FontReader reader(ttf_path);
                REQUIRE( reader.has_data() == true );
            }
        }
    }
}

SCENARIO( "ttf file can be read 3", "[FontReader]" ) {
    GIVEN("a ttf file") {
        WHEN("the existing file is read") {
            THEN("test data begins with expected bytes") {
                OpenType::FontReader reader(ttf_path);
                std::cout << reader;
                std::vector<char> bytes = reader.get_bytes(0,1);
                std::cout << "hello " << std::hex << int(bytes[0]) << " " << std::hex << int(bytes[1]) << std::endl;
                REQUIRE(int(bytes[0]) == 0x00);
                REQUIRE(int(bytes[1]) == 0x01);
            }
        }
    }
}
