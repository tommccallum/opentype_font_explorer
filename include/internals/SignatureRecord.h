#ifndef SIGNATURE_RECORD_H
#define SIGNATURE_RECORD_H

#include <vector>
#include "internals/InternalTypes.h"
#include "internals/SignatureBlockFormat1.h"

namespace OpenType {
    class TypeReader;

    class SignatureRecord {
    public:
        SignatureRecord( );
        void from_bytes( TypeReader& reader );

        friend std::ostream& operator<<( std::ostream& out, const SignatureRecord& table );
    private:
        OT_UINT32 format_; // format of the signature
        OT_UINT32 length_; // how long is the signature in bytes
        OT_OFFSET32 offset_; // offset to the signature block from the start of the DSIG table
        std::vector<SignatureBlockFormat1> signatures_;

        size_t get_info_size() {
            return sizeof( OT_UINT32 ) + sizeof( OT_UINT32 ) + sizeof( OT_OFFSET32 );
        }
    };
}

#endif // SIGNATURE_RECORD_H
