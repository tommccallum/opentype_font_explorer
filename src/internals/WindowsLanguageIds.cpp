#include <iostream>
#include "internals/WindowsLanguageIds.h"

namespace OpenType {
    std::ostream& operator<<( std::ostream& out, const WindowsLanguageID id ) {
        out << int(id.id) << " " << id.primary_language << " " << id.region << std::endl;
        return out;
    }
}
