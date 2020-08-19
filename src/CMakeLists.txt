## Build OpenType as a library
message("Building library")

set(CPP_FILES
    internals/FontReader.cpp
    internals/OffsetTable.cpp
    internals/TableRecord.cpp
    internals/SignatureRecord.cpp
    internals/AbstractTable.cpp
    internals/SignatureBlockFormat1.cpp
    internals/WindowsLanguageIds.cpp
    internals/MacintoshLanguageIds.cpp
    internals/MacintoshEncodingIds.cpp
    internals/NameIds.cpp
    internals/tables/TableDSIG.cpp
    internals/tables/TableLTSH.cpp
    internals/tables/TableOS2.cpp
    internals/tables/TableVDMX.cpp
    internals/tables/TableCMAP.cpp
    internals/tables/TableCVT.cpp
    internals/tables/TableFPGM.cpp
    internals/tables/TableMAXP.cpp
    internals/tables/TablePREP.cpp
    internals/tables/TableLOCA.cpp
    internals/tables/TableHEAD.cpp
    internals/tables/TablePOST.cpp
    internals/tables/TableNAME.cpp
    internals/tables/TableKERN.cpp
    internals/tables/TableGASP.cpp
    internals/tables/TableGLYF.cpp
    internals/tables/TableHHEA.cpp
    internals/tables/TableHMTX.cpp
    internals/tables/TableHDMX.cpp
    OpenTypeFont.cpp
)

add_library(OpenType STATIC ${CPP_FILES})

## ensure other libraries/executables linking to this can find
## the includes
target_include_directories(OpenType PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(OpenType PRIVATE -g -Werror -Wall -Wextra)
