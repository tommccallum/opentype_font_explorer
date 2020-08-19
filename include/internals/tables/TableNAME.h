#ifndef TABLE_NAME_H
#define TABLE_NAME_H

#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

        class TableNAME : public AbstractTable {
        public:
            // @see https://docs.microsoft.com/en-gb/typography/opentype/spec/name#name-records
            struct LangTagRecord {
                OT_UINT16 length;
                OT_OFFSET16 offset;
                std::string text;
            };


            // Each string in the string storage is referenced by a name record.
            // The name record has a multi-part key, to identify the logical type
            // of string and its language or platform-specific implementation variants,
            // plus the location of the string in the string storage.

            //@see https://docs.microsoft.com/en-gb/typography/opentype/spec/name#name-records
            // As with encoding records in the 'cmap' table, name records must be
            // sorted first by platform ID, then by platform-specific ID,
            // then by language ID, and then by name ID.
            // Descriptions of the various IDs follow.
            struct NameRecord {
                // The name ID identifies a logical string category, such as family name
                // or copyright. Name IDs are the same for all platforms and languages;
                // these are described in detail below. The other three elements of the
                // key allow for platform-specific implementations: a platform ID, a
                // platform-specific encoding ID, and a language ID.
                OT_UINT16 name_id=0;

                // The other three elements of the key allow for platform-specific
                // implementations: a platform ID, a platform-specific encoding ID,
                // and a language ID.
                OT_UINT16 platform_id=0;
                OT_UINT16 encoding_id=0;
                OT_UINT16 language_id=0;

                OT_UINT16 length=0;
                OT_OFFSET16 offset=0;

                std::string text;
            };


            TableNAME( TypeReader type_reader );
            void print(std::ostream& out) const; // Override

        private:
            // Format 0 fields
            OT_UINT16 format_;
            OT_UINT16 count_;
            OT_OFFSET16 string_offset_;
            std::vector<NameRecord> name_records_;

            // version 1 fields
            OT_UINT16 lang_tag_count_;
            std::vector<LangTagRecord> lang_tag_records_;

            void from_bytes( TypeReader& type_reader );
        };
}

#endif // TABLE_NAME_H
