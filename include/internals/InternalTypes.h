#ifndef INTERNAL_TYPES_H
#define INTERNAL_TYPES_H

#include "internals/FixedPointMath.h"

namespace OpenType {

    // Data Types used in OpenType Specification
    // @see https://docs.microsoft.com/en-gb/typography/opentype/spec/otff

    #include <cstdint>

    using OT_UINT8   = uint8_t;
    using OT_INT8    = int8_t;
    using OT_UINT16  =         uint16_t;
    using OT_INT16   =         int16_t;
    using OT_UINT32  =         uint32_t;
    using OT_INT32   =         int32_t;
    using OT_UINT24   =         uint32_t;
    using OT_INT24   =         int32_t;
    using OT_FIXED   =         Fixed<16,16>;    // 32-bit signed fixed-point number (16.16)
    using OT_FWORD   =         int16_t;
    using OT_UFWORD  =         uint16_t;
    using OT_F2DOT14 =         int16_t;     // 16-bit signed fixed number with low 14 bits of fraction (2.14)
    using OT_LONGDATETIME =    int64_t; // 64-bit timestamp since midnight, Jan 1 1904
    using OT_TAG      =        char[4];    // 4 x 8 bit unsigned
    using OT_OFFSET16 =        uint16_t;
    using OT_OFFSET32 =        uint32_t;





}

#endif // INTERNAL_TYPES_H
