#ifndef TABLE_DSIG_H
#define TABLE_DSIG_H

#include <vector>
#include "internals/InternalTypes.h"
#include "internals/SignatureRecord.h"
#include "internals/AbstractTable.h"

namespace OpenType {
    class TypeReader;

    // class name matches the tag of the table
    class TableDSIG : public AbstractTable {
    public:
        TableDSIG( TypeReader type_reader );
        size_t get_signature_count() const;

        void print(std::ostream& out) const; // Override
    private:
        OT_UINT32 version_;
        OT_UINT16 num_signatures_;
        OT_UINT16 flags_;
        OT_UINT32 bof_offset_;
        std::vector<SignatureRecord> signature_records_;

        void from_bytes( TypeReader& type_reader );
        size_t get_info_size() {
            return sizeof(OT_UINT32)+2 * sizeof(OT_UINT16);
        }
    };
}

#endif // TABLE_DSIG_H
