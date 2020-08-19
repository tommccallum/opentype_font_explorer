#ifndef SIGNATURE_BLOCK_FORMAT_1_H
#define SIGNATURE_BLOCK_FORMAT_1_H

#include <vector>
#include "InternalTypes.h"

namespace OpenType {
    class TypeReader;

    class SignatureBlockFormat1 {
    public:
        SignatureBlockFormat1( TypeReader type_reader );
        friend std::ostream& operator<<( std::ostream& out, const SignatureBlockFormat1& table );
    private:
        OT_UINT16 reserved1_;
        OT_UINT16 reserved2_;
        OT_UINT32 length_;
        std::vector<char> signature_;

        void from_bytes( TypeReader& type_reader );
    };
}

#endif // SIGNATURE_BLOCK_FORMAT_1_H
