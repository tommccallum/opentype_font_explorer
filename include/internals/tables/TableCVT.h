#ifndef TABLE_CVT_H
#define TABLE_CVT_H

#include <vector>
#include <iostream>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    class TableCVT : public AbstractTable {
    public:
        TableCVT( TypeReader type_reader );
        void print(std::ostream& out) const; // Override
    private:
        std::vector<OT_FWORD> control_values_;
        void from_bytes( TypeReader& type_reader );

    };

}

#endif // TABLE_CVT_H
