#ifndef TABLE_LTSH_H
#define TABLE_LTSH_H

#include <iostream>
#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    // class name matches the tag of the table
    class TableLTSH : public AbstractTable {
    public:
        TableLTSH( TypeReader type_reader );

        void print(std::ostream& out) const; // Override
    private:
        OT_UINT16 version_;
        OT_UINT16 num_glyphs_;

        // vertical pel height at which the glyph can be assumed to
        // scale linearly, on a per glyph basis
        std::vector<char> y_pels_;

        void from_bytes( TypeReader& type_reader );

    };
}

#endif // TABLE_LTSH_H
