#ifndef MACINTOSH_ENCODING_ID_H
#define MACINTOSH_ENCODING_ID_H

#include <vector>
#include <string>
#include <cstdint>
#include "InternalTypes.h"

namespace OpenType {

struct MacintoshEncodingID {
    OT_UINT32 id;
    std::string name;
};

std::ostream& operator<<( std::ostream& out, const MacintoshEncodingID id );

const std::vector<MacintoshEncodingID> macintosh_encoding_ids = {
    {0,"Roman"},
    {1,"Japanese"},
    {2,"Chinese (Traditional)"},
    {3,"Korean"},
    {4,"Arabic"},
    {5,"Hebrew"},
    {6,"Greek"},
    {7,"Russian"},
    {8,"RSymbol"},
    {9,"Devanagari"},
    {10,"Gurmukhi"},
    {11,"Gujarati"},
    {12,"Oriya"},
    {13,"Bengali"},
    {14,"Tamil"},
    {15,"Telugu"},
    {16,"Kannada"},
    {17,"Malayalam"},
    {18,"Sinhalese"},
    {19,"Burmese"},
    {20,"Khmer"},
    {21,"Thai"},
    {22,"Laotian"},
    {23,"Georgian"},
    {24,"Armenian"},
    {25,"Chinese (Simplified)"},
    {26,"Tibetan"},
    {27,"Mongolian"},
    {28,"Geez"},
    {29,"Slavic"},
    {30,"Vietnamese"},
    {31,"Sindhi"},
    {32,"Uninterpreted"}
};

}

#endif // MACINTOSH_ENCODING_ID_H
