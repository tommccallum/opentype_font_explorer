#ifndef OPEN_FONT_READER_H
#define OPEN_FONT_READER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

namespace OpenType {

    class FontReader {
    public:
        FontReader( std::string filename );
        void reset();
        void seek(size_t position);
        size_t size() const;
        bool has_data() const;
        std::vector<char> get_bytes(size_t length) ;
        std::vector<char> get_bytes(size_t start, size_t length);
        // does not update the pos_ cursor
        std::vector<char> get_byte_sequence(size_t start, size_t length) const;
        size_t get_position() const;
        friend std::ostream& operator<<( std::ostream& out, const FontReader& reader );
    private:
        std::string filename_;
        std::vector<char> bytes_; // raw bytes of ttf
        size_t pos_; // position of last read + 1
        void readBytes(); // read in the entire ttf file into memory
    };

}

#endif // OPEN_FONT_READER_H
