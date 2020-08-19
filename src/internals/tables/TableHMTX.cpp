#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableHHEA.h"
#include "internals/tables/TableMAXP.h"
#include "internals/tables/TableHMTX.h"

namespace OpenType {

    TableHMTX::TableHMTX(TypeReader type_reader, TableHHEA* hhea, TableMAXP* maxp ) :
        AbstractTable(),
        number_of_h_metrics_( hhea->get_number_of_h_metrics() ),
        num_glyphs_( maxp->get_num_glyphs() )
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableHMTX::from_bytes( TypeReader& type_reader ) {
        for( int ii=0; ii < number_of_h_metrics_; ii++ ) {
            auto lhm = LongHorMetric {};
            lhm.advance_width = type_reader.readUInt16();
            lhm.lsb = type_reader.readInt16();
            h_metrics_.push_back( std::move( lhm ) );
        }
        for( int ii=0; ii < num_glyphs_ - number_of_h_metrics_; ii++ ) {
            left_side_bearings_.push_back( type_reader.readInt16() );
        }
    }

    // @Override
    void TableHMTX::print(std::ostream& out) const {
        out << "HMTX{";
        out << std::dec;
        out << "(" << h_metrics_.size() << ")(";
        size_t ii=0;
        for( auto lhm : h_metrics_ ) {
            out << "{" << lhm.advance_width << "," << lhm.lsb << "}";
            if ( ii < h_metrics_.size()-1 ) out << ",";
        }
        out << "),";
        ii=0;
        out << "(" << left_side_bearings_.size() << ")(";
        for( auto lsb : left_side_bearings_ ) {
            out << lsb ;
            if ( ii < left_side_bearings_.size()-1 ) out << ",";
        }
        out << ")";

        out << "}";
        out << std::endl;
    }


}
