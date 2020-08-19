#include <iostream>
#include <iomanip>
#include <cassert>
#include <memory>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableGLYF.h"
#include "internals/tables/TableMAXP.h"
#include "internals/tables/TableLOCA.h"

namespace OpenType {

    TableGLYF::Glyph::Glyph() :
        number_of_contours_(0),
        x_min_(0),
        y_min_(0),
        x_max_(0),
        y_max_(0)
    {

    }

    TableGLYF::Glyph::Glyph(OT_INT16 number_of_contours,
            OT_INT16 x_min,
            OT_INT16 y_min,
            OT_INT16 x_max,
            OT_INT16 y_max) :
        number_of_contours_(number_of_contours),
        x_min_(x_min),
        y_min_(y_min),
        x_max_(x_max),
        y_max_(y_max)
    {

    }

    bool TableGLYF::Glyph::is_composite() const {
        return number_of_contours_ < 0x0;
    }

    void TableGLYF::Glyph::set(Simple* glyph) {
        // takes ownership of this pointer
        simple_.reset( glyph );
    }

    void TableGLYF::Glyph::from_bytes( TypeReader& type_reader ) {
        // starts at position to read glyph
        if ( is_composite() ) {

        } else {
            from_bytes_simple( type_reader );
        }
    }

    void TableGLYF::Glyph::from_bytes_simple( TypeReader& type_reader ) {
        simple_ = std::make_unique<Simple>();
        for( int ii=0; ii < number_of_contours_; ii++ ) {
            simple_->end_pts_of_contours.push_back( type_reader.readUInt16() );
        }
        simple_->instruction_length = type_reader.readUInt16();
        for( int ii=0; ii < simple_->instruction_length; ii++ ) {
            simple_->instructions.push_back( type_reader.readUInt8() );
        }

        // should expand to 1 flag per point
        // is |point| the same as |contour|?
        int flag_count = 0;
        while ( flag_count < number_of_contours_ ) {
            OT_UINT8 flag = type_reader.readUInt8();
            simple_->flags.push_back( uint16_t(flag) );
            flag_count++;
            if ( (flag & 0x08) == 0x08 ) {
                OT_UINT8 flag_repeated = type_reader.readUInt8();
                // I employ a brute force approach and expand the compressed
                // array of flags for ease, probably a better solution
                for( int jj=0; jj < flag_repeated; jj++ ) {
                    simple_->flags.push_back( uint16_t(flag) );
                    flag_count++;
                }
            }
        }

        OT_INT16 x = 0;
        for( size_t ii=0; ii < simple_->flags.size(); ii++ ) {
            if ( ( simple_->flags[ii] & 0x2 ) == 0x2 ) { // X_SHORT_VECTOR is SET
                x = type_reader.readUInt8();
                if ( ( simple_->flags[ii] & 0x10 ) == 0x10 ) { // X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR is SET
                    simple_->x_coordinates.push_back( x );
                } else {
                    simple_->x_coordinates.push_back( -x );
                }
            } else {
                if ( ( simple_->flags[ii] & 0x10 ) == 0x10 ) { // X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR is SET
                    simple_->x_coordinates.push_back( x );
                } else {
                    x = type_reader.readInt16();
                    simple_->x_coordinates.push_back( x );
                }
            }
        }

        OT_UINT16 y = 0;
        for( size_t ii=0; ii < simple_->flags.size(); ii++ ) {
            if ( ( simple_->flags[ii] & 0x4 ) == 0x4 ) { // Y_SHORT_VECTOR is SET
                y = type_reader.readUInt8();
                if ( ( simple_->flags[ii] & 0x20 ) == 0x20 ) { // Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR is SET
                    simple_->y_coordinates.push_back( y );
                } else {
                    simple_->y_coordinates.push_back( -y );
                }
            } else {
                if ( ( simple_->flags[ii] & 0x20 ) == 0x20 ) { // Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR is SET
                    // repeat previous coordinate
                    simple_->y_coordinates.push_back( y );
                } else {
                    // add new signed 16-bit coordinate
                    y = type_reader.readInt16();
                    simple_->y_coordinates.push_back( y );
                }
            }
        }
    }

    void TableGLYF::Glyph::print( std::ostream& out ) const {
        out << "GLYF::Glyph{";
        out << std::dec;
        out << number_of_contours_ << ",";
        out << x_min_ << "," << y_min_ << "," << x_max_ << "," << y_max_ << ",";
        if ( simple_ != NULL ) {
            out << "SIMPLE{";
            out << "(";
            for( auto x : simple_->end_pts_of_contours ) {
                out << x << ",";
            }
            out << "),";
            out << simple_->instruction_length << ",";
            out << "(";
            for( auto x : simple_->instructions ) {
                out << "0x" << std::hex << std::setw(2) << std::setfill('0') << int(x) << ",";
            }
            out << std::dec;
            out << "),";
            out << simple_->flags.size() << ",";
            out << "(";
            for( auto x : simple_->flags ) {
                out << "0x" << std::hex << std::setw(2) << std::setfill('0') << int(x) << ",";
            }
            out << std::dec;
            out << "),";
            out << "(";
            for( auto x : simple_->x_coordinates ) {
                out << x << ",";
            }
            out << "),";
            out << "(";
            for( auto x : simple_->y_coordinates ) {
                out << x << ",";
            }
            out << ")";
            out << "}";
        }
        out << "}";
    }


    std::ostream& operator<<( std::ostream& out, TableGLYF::Glyph const & table ) {
        table.print(out);
        return out;
    }

    std::ostream& operator<<( std::ostream& out, TableGLYF::Glyph const * table ) {
        out << *table;
        return out;
    }




    // GLYF PARENT CLASS



    TableGLYF::TableGLYF(TypeReader type_reader, TableMAXP* maxp, TableLOCA* loca) :
        AbstractTable()
    {
        from_bytes( type_reader, maxp, loca );
    }

    // expects reader to be in correct position to read
    void TableGLYF::from_bytes( TypeReader& type_reader, TableMAXP* maxp, TableLOCA* loca ) {
        // get some sense checking information
        OT_UINT16 num_glyphs = maxp->get_num_glyphs();
        // OT_UINT16 max_points = maxp->get_max_points();
        // OT_UINT16 max_contours = maxp->get_max_contours();
        // OT_UINT16 max_size_of_instructions = maxp->get_max_size_of_instructions();

        bool is_using_long_offsets = loca->use_long_offsets();
        std::cout << is_using_long_offsets << '\n';
        std::cout << num_glyphs << '\n';
        std::cout << loca->size() << '\n';

        assert( size_t(num_glyphs + 1) == loca->size() );

        for( int ii=0; ii < num_glyphs; ii++ ) {
            TypeReader glyph_data;
            if ( is_using_long_offsets ) {
                OT_OFFSET32 offset = loca->get_offset32( ii );
                OT_UINT32 data_length = loca->get_glyph_data_length32( ii );
                glyph_data = type_reader.get_byte_sequence( offset, data_length );
            } else {
                OT_OFFSET16 offset = loca->get_offset16( ii );
                OT_UINT16 data_length = loca->get_glyph_data_length16( ii );
                glyph_data = type_reader.get_byte_sequence( offset, data_length );
            }

            auto glyph = Glyph( type_reader.readInt16(),
                                type_reader.readInt16(),
                                type_reader.readInt16(),
                                type_reader.readInt16(),
                                type_reader.readInt16()
                                );
            glyph.from_bytes( type_reader );
            glyphs_.push_back( std::move( glyph ) );
        }
    }

    // @Override
    void TableGLYF::print(std::ostream& out) const {
        out << "GLYF{";
        out << std::dec << glyphs_.size() << ",";
        size_t ii = 0;
        for( auto& glyph : glyphs_ ) {
            out << glyph;
            if ( ii < glyphs_.size() - 1 ) out << ",";
            ii++;
        }
        out << "}";
        out << std::endl;
    }

}
