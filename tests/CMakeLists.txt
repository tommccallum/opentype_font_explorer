
if(BUILD_TESTING)
    set(DATA_DIR ${CMAKE_SOURCE_DIR}/fonts)
    #set(TEMP_DIR  ${CMAKE_SOURCE_DIR}/tests/tmp)
    include_directories("${CMAKE_SOURCE_DIR}/cmake")

    ## all test case filenames without extension
    set(TEST_CASES
        test_catch
        test_fontreader
        test_typereader
        test_offsettable
        test_tablerecord
        test_fixedpointmaths
    )

    ## bind all tests with the library output
    foreach(_test_case ${TEST_CASES})
        add_executable(${_test_case} ${_test_case}.cpp catch_main.cpp)
        target_link_libraries(${_test_case} OpenType)
    endforeach()

    ##################################################################################################
    # Dont forget its:  add_test(<test name (globally unique) > <exe name> <argument1> <argument2>
    ##################################################################################################
    add_test(001-test-catch test_catch)
    add_test(002-FontReader test_fontreader ${CATCH_SOURCE_DIR}/fonts/verdana.ttf)
    add_test(003-TypeReader test_typereader ${CATCH_SOURCE_DIR}/fonts/verdana.ttf)
    add_test(004-OffsetTable test_offsettable ${CATCH_SOURCE_DIR}/fonts/verdana.ttf)
    add_test(005-TableRecord test_tablerecord ${CATCH_SOURCE_DIR}/fonts/verdana.ttf)
    add_test(006-FixedPointMath test_fixedpointmaths.cpp)
endif() ## end if BUILD_TESTING
