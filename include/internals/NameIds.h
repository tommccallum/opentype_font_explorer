#ifndef NAME_IDS_H
#define NAME_IDS_H
#include <vector>
#include <cstdint>
#include <string>
#include "InternalTypes.h"

namespace OpenType {

struct NameID {
    OT_UINT32 id;
    std::string name;
};

std::ostream& operator<<( std::ostream& out, const NameID id ) ;


// @see https://docs.microsoft.com/en-gb/typography/opentype/spec/name
const std::vector<NameID> name_ids = {
    { 0, "Copyright Notice"},
    { 1, "Font Family Name" },
    { 2, "Font Subfamily Name" },
    { 3, "Unique Font Identifier" },
    { 4, "Full Font Name" },
    { 5, "Version" },
    { 6, "Postscript Font Name" },
    { 7, "Trademark" },
    { 8, "Manufacturer" },
    { 9, "Designer" },
    { 10, "Description" },
    { 11, "URL Vendor" },
    { 12, "URL Designer" },
    { 13, "License Description" },
    { 14, "License Info URL" },
    { 15, "Reserved" },
    { 16, "Typographic Family Name" },
    { 17, "Typographic Subfamily Name" },
    { 18, "Compatible Full" },
    { 19, "Sample Text" },
    { 20, "PostScript CID findFont Name" },
    { 21, "WWS Family Name" },
    { 22, "WWS Subfamily Name" },
    { 23, "Light Background Palette" },
    { 24, "Dark Background Palette" },
    { 25, "Variations PostScript Name Prefix" }
};

}

#endif // NAME_IDS_H
