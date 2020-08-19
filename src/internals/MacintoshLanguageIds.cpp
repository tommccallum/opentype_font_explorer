#include <iostream>
#include "internals/MacintoshLanguageIds.h"

namespace OpenType {

    std::ostream& operator<<( std::ostream& out, const MacintoshLanguageID id ) {
        out << int(id.id) << " " << id.name << std::endl;
        return out;
    }

}
