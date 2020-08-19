#ifndef TABLE_GASP_H
#define TABLE_GASP_H

#include <iostream>
#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    // class name matches the tag of the table
    class TableGASP : public AbstractTable {
    public:
        enum Behaviour {
            GASP_GRIDFIT=0x0001,
            GASP_DOGRAY=0x0002,
            GASP_SYMMETRIC_GRIDFIT=0x0004,
            GASP_SYMMETRIC_SMOOTHING=0x0008,
        };
        struct GaspRange {
            OT_UINT16 range_max_ppem;
            OT_UINT16 range_gasp_behaviour;
        };

        TableGASP( TypeReader type_reader );

        void print(std::ostream& out) const; // Override
    private:
        OT_UINT16 version_;
        OT_UINT16 num_ranges_;
        std::vector<GaspRange> ranges_;

        void from_bytes( TypeReader& type_reader );

    };
}

#endif // TABLE_GASP_H
