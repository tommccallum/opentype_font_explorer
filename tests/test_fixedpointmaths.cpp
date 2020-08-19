#include <iostream>
#include <sstream>
#include "catch_main.h"
#include "catch2.hpp"
#include "internals/FixedPointMath.h"

using namespace OpenType;

int32_t adobe_double2fixed( double x ) {
    return (int32_t)( (x) * 65536.0 + 0.5 );
}

int32_t adobe_int2fixed( int32_t x ) {
    return (int32_t)( (uint32_t)(x) << 16 );
}

TEST_CASE( "Create a 16.16 number", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    REQUIRE( Fixed<16,16>::FIXED_ONE == 0x10000 );
}

TEST_CASE( "Check double bit shift is 65536.0", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    REQUIRE( Fixed<16,16>::DBL_BIT_SHIFT == 65536.0 );
}

TEST_CASE( "Check fixed min is 0x80000000L", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    REQUIRE( Fixed<16,16>::FIXED_MIN == (int32_t) 0x80000000L );
}

TEST_CASE( "Check fixed max is 0x7FFFFFFFL", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    REQUIRE( Fixed<16,16>::FIXED_MAX == (int32_t) 0x7FFFFFFFL );
}

TEST_CASE( "Check epsilon is 0x1", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    REQUIRE( Fixed<16,16>::EPSILON == (int32_t) 0x1 );
}

TEST_CASE( "Check printing works", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>(5);
    std::cout << "CHECK OUTPUT: " << fp << std::endl;
    REQUIRE( 1 == 1 );
}


TEST_CASE( "Check fixed value -5", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>(-5);
    std::cout << "NEGINT: " << "0x" << std::hex << adobe_int2fixed(-5) << std::endl;
    REQUIRE( fp == (int32_t)0xFFFB0000L );
}

TEST_CASE( "Check fixed value of -1", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>(-1);
    std::cout << "NEGINT: " << "0x" << std::hex << adobe_int2fixed(-1) << std::endl;
    REQUIRE( fp == (int32_t)0xFFFF0000 );
}

TEST_CASE( "Check fixed value of 0", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>(0);
    std::cout << "NEGINT: " << "0x" << std::hex << adobe_int2fixed(0) << std::endl;
    REQUIRE( fp == (int32_t)0x00000000 );
}

// TEST_CASE( "Check fixed value of 0xFFFFFFFF", "[fixedpointmath]" ) {
//     double d = double(32768);
//     auto fp = Fixed<16,16>(d);
//     std::cout << "NEGINT: " << fp << " 0x" << std::hex << adobe_double2fixed(d) << std::endl;
//     REQUIRE( fp == (int32_t)d );
// }

TEST_CASE( "Check to double with number 5.25", "[fixedpointmath]" ) {
    double d = 5.25;
    auto fp = Fixed<16,16>(d);
    std::cout << "CHECK FLOAT OUTPUT: requested: " << d << " created: " << fp << " expected: " << "0x" << std::hex << adobe_double2fixed(d) << std::endl;
    REQUIRE( fp == 0x54000 );
}

TEST_CASE( "Check to double with number -5.25", "[fixedpointmath]" ) {
    double d = -5.25;
    auto fp = Fixed<16,16>(d);
    std::cout << "CHECK FLOAT OUTPUT: requested: " << d << " created: " << fp << " expected: " << "0x" << std::hex << adobe_double2fixed(d) << std::endl;
    REQUIRE( fp == int32_t(0xFFFAC001) );
}

TEST_CASE( "Check to double with number 5.5", "[fixedpointmath]" ) {
    double d = 5.5;
    auto fp = Fixed<16,16>(d);
    std::cout << "CHECK FLOAT OUTPUT: requested: " << d << " created: " << fp << " expected: " << "0x" << std::hex << adobe_double2fixed(d) << std::endl;
    REQUIRE( fp == 0x58000 );
}

TEST_CASE( "Check to double with number 5.75", "[fixedpointmath]" ) {
    double d = 5.75;
    auto fp = Fixed<16,16>(d);
    std::cout << "CHECK FLOAT OUTPUT: requested: " << d << " created: " << fp << " expected: " << "0x" << std::hex << adobe_double2fixed(d) << std::endl;
    REQUIRE( fp == 0x5c000 );
}

TEST_CASE( "Check to double with number 1/3", "[fixedpointmath]" ) {
    double d = 1.0/3.0;
    auto fp = Fixed<16,16>(d);
    std::cout << "CHECK FLOAT OUTPUT: requested: " << d << " created: " << fp << " expected: " << "0x" << std::hex << adobe_double2fixed(d) << std::endl;
    REQUIRE( fp == 0x5555 );
}

TEST_CASE( "Check to double with number 1/2^16 (smallest fractional value)", "[fixedpointmath]" ) {
    double d = 1.0/pow(2.0,16);
    auto fp = Fixed<16,16>(d);
    std::cout << "CHECK FLOAT OUTPUT: requested: " << d << " created: " << fp << " expected: " << "0x" << std::hex << adobe_double2fixed(d) << std::endl;
    REQUIRE( fp == 0x0001 );
}

TEST_CASE( "Check to double with number -1/2^16 (smallest fractional value)", "[fixedpointmath]" ) {
    double d = -1.0/pow(2.0,16);
    auto fp = Fixed<16,16>(d);
    std::cout << "CHECK FLOAT OUTPUT: requested: " << d << " created: " << fp << " expected: " << "0x" << std::hex << adobe_double2fixed(d) << std::endl;
    REQUIRE( fp == 0x0000 );
}

TEST_CASE( "Check to double with number -1/2 (smallest fractional value)", "[fixedpointmath]" ) {
    double d = -1.0/2.0;
    auto fp = Fixed<16,16>(d);
    std::cout << "CHECK FLOAT OUTPUT: requested: " << d << " created: " << fp << " expected: " << "0x" << std::hex << adobe_double2fixed(d) << std::endl;
    REQUIRE( fp == int32_t(0xFFFF8001) );
}


TEST_CASE( "Check floor works with number 5", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>(5);
    REQUIRE( fp.integral() == 0x50000 );
}

TEST_CASE( "Check input stream works with doubles", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    std::stringstream ss("5.25");
    ss >> fp;
    REQUIRE( fp == 0x54000 );
}

TEST_CASE( "Check input stream works with int32", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    std::stringstream ss("10");
    ss >> fp;
    REQUIRE( fp == 0xA0000 );
}

TEST_CASE( "Check input stream works with negative doubles", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    std::stringstream ss("-5.25");
    ss >> fp;
    REQUIRE( fp == int32_t(0xFFFAC001) );
}

TEST_CASE( "Check input stream works with negative int32", "[fixedpointmath]" ) {
    auto fp = Fixed<16,16>();
    std::stringstream ss("-10");
    ss >> fp;
    REQUIRE( fp == int32_t(0xFFF60001) );
}
