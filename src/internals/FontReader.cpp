#include <iostream>
#include <iomanip>
#include "internals/FontReader.h"

namespace OpenType {


    FontReader::FontReader( std::string filename ) {
        filename_ = filename;
        readBytes();
    }

    void FontReader::readBytes() {
        bytes_.clear();
        std::streampos size;
        std::ifstream fh;
        fh.open( filename_, std::ios::in | std::ios::binary | std::ios::ate );
        if ( fh.is_open() ) {
            // don't eat newlines in binary mode
            fh.unsetf(std::ios::skipws);
            size = fh.tellg();
            bytes_.reserve( size ); // reserve memory in vector
            fh.seekg(0, std::ios::beg);
            bytes_.insert( bytes_.begin(),
                            std::istream_iterator<char>(fh),
                            std::istream_iterator<char>()
                        );
        }
        pos_ = 0;
    }

    void FontReader::reset() {
        pos_ = 0;
    }

    void FontReader::seek(size_t position) {
        pos_ = position;
    }

    size_t FontReader::size()  const {
        return bytes_.size();
    }

    bool FontReader::has_data()  const {
        return size() > 0;
    }

    std::vector<char> FontReader::get_bytes(size_t length) {
        std::vector<char>::const_iterator first = bytes_.begin() + pos_;
        // last should always be 1 more than we need
        std::vector<char>::const_iterator last = bytes_.begin() + pos_ + length+1;
        std::vector<char> result(first,last);
        pos_ = pos_ + length;
        return result;
    }

    std::vector<char> FontReader::get_bytes(size_t start, size_t length) {
        std::vector<char>::const_iterator first = bytes_.begin() + start;
        // last should always be 1 more than we need
        std::vector<char>::const_iterator last = bytes_.begin() + start + length+1;
        std::vector<char> result(first,last);
        pos_ = start + length;
        return result;
    }

    /**
     * Reads a sequence of bytes, without changing offset
     * @param  start  [description]
     * @param  length [description]
     * @return        [description]
     */
    std::vector<char> FontReader::get_byte_sequence(size_t start, size_t length) const {
        // length appears to be 1 short than we would normally expect in file format
        std::vector<char>::const_iterator first = bytes_.begin() + start;
        std::vector<char>::const_iterator last = bytes_.begin() + start + length;
        std::vector<char> result(first,last);
        return result;
    }

    size_t FontReader::get_position() const {
        return pos_;
    }

    std::ostream& operator<<( std::ostream& out, const FontReader& reader ) {
        int ii=0;
        for( char c : reader.bytes_ ) {
            out << "0x" << std::setfill('0') << std::setw(2) << std::hex << int(c) << " ";
            ii++;
            if ( ii > 9 ) break;
        }
        return out;
    }

} // end of namespace
