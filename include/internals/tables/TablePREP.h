#ifndef TABLE_PREP_H
#define TABLE_PREP_H

#include <vector>
#include <iostream>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    class TablePREP : public AbstractTable {
    public:
        TablePREP( TypeReader type_reader );
        void print(std::ostream& out) const; // Override
    private:
        std::vector<OT_UINT8> control_values_;
        void from_bytes( TypeReader& type_reader );

    };

}

#endif // TABLE_PREP_H
