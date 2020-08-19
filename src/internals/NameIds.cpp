#include <iostream>
#include "internals/NameIds.h"

namespace OpenType {

    std::ostream& operator<<( std::ostream& out, const NameID id ) {
        out << int(id.id) << " " << id.name << std::endl;
        return out;
    }

}
