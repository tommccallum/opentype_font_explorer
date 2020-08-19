#ifndef TABLE_GLYF_H
#define TABLE_GLYF_H

#include <iostream>
#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    class TableMAXP;
    class TableLOCA;

    // class name matches the tag of the table
    class TableGLYF : public AbstractTable {
    public:
        class Glyph {
        public:
                struct Simple {
                    std::vector<OT_UINT16> end_pts_of_contours;
                    OT_UINT16 instruction_length;
                    std::vector<OT_UINT8> instructions;
                    // flags is now same length as x,y coordinates
                    std::vector<OT_UINT16> flags;

                    // either format based on flags setting
                    // could be mixed so we choose the larger
                    // and then cast as required later on.
                    std::vector<OT_UINT16> x_coordinates;
                    std::vector<OT_UINT16> y_coordinates;

                };

                struct Composite {
                    OT_UINT16 flags;
                    OT_UINT16 glyph_index;
                    // these could be UINT8,INT8,UINT16 or INT16
                    OT_UINT16 x_offset;
                    OT_UINT16 y_offset;
                };

                Glyph();

                Glyph(OT_INT16 number_of_contours,
                        OT_INT16 x_min,
                        OT_INT16 y_min,
                        OT_INT16 x_max,
                        OT_INT16 y_max
                        );
                bool is_composite() const ;
                // take ownership of new glyph
                void set(Simple* glyph);
                void from_bytes( TypeReader& type_reader );
                void print( std::ostream& out ) const ;
                friend std::ostream& operator<<( std::ostream& out, Glyph const & table );
                friend std::ostream& operator<<( std::ostream& out, Glyph const * table );
        private:
                OT_INT16 number_of_contours_;
                OT_INT16 x_min_;
                OT_INT16 y_min_;
                OT_INT16 x_max_;
                OT_INT16 y_max_;
                std::unique_ptr<Simple> simple_;
                std::vector<std::unique_ptr<Composite>> composite_;

                void from_bytes_simple( TypeReader& type_reader );
        };

        TableGLYF( TypeReader type_reader, TableMAXP* maxp, TableLOCA* loca );

        void print(std::ostream& out) const; // Override
    private:
        std::vector<Glyph> glyphs_;

        void from_bytes( TypeReader& type_reader, TableMAXP* maxp, TableLOCA* loca );

    };
}

#endif // TABLE_GLYF_H
