#include "internals/AbstractTable.h"

namespace OpenType {

    // this is required to stop a linker error - check
    AbstractTable::~AbstractTable() {};

    std::ostream& operator<<( std::ostream& out, AbstractTable const & table ) {
        table.print(out);
        return out;
    }

    std::ostream& operator<<( std::ostream& out, AbstractTable const * table ) {
        out << *table;
        return out;
    }
}
