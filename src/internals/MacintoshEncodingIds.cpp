#include <iostream>
#include "internals/MacintoshEncodingIds.h"

namespace OpenType {

    std::ostream& operator<<( std::ostream& out, const MacintoshEncodingID id ) {
        out << int(id.id) << " " << id.name << std::endl;
        return out;
    }

}
