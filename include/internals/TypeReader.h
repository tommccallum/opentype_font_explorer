#ifndef TYPE_READER_H
#define TYPE_READER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <locale> // wstring_convert
#include <codecvt>
#include "InternalTypes.h"

namespace OpenType {

    // Converts a big-endian stream of chars into words of required type
    // usage
    // FontReader reader( filename.ttf );
    // auto typereader = TypeReader( reader.get_bytes(0,8) );
    // auto next = typereader.readUInt16();
    class TypeReader {
    public:
        TypeReader( ) :
            padded_(0),
            index_(0)
        {
        }

        TypeReader( std::vector<char> bytes ) :
            bytes_(bytes),
            padded_(0),
            index_(0)
        {
        }

        bool eof() {
            return index_ >= bytes_.size();
        }

        void seek(size_t index) {
            index_ = index;
        }

        size_t get_position() {
            return index_;
        }

        OT_UINT8 readUInt8() {
            return static_cast<OT_UINT8>(bytes_[index_++]);
        }
        OT_INT8 readInt8() {
            return static_cast<OT_INT8>(bytes_[index_++]);
        }
        OT_UINT16 readUInt16() {
            OT_UINT16 word=0;
            word |= static_cast<uint8_t>(bytes_[index_++]) << 8;
            word |= static_cast<uint8_t>(bytes_[index_++]);
            return word;
        }
        OT_INT16 readInt16() {
            OT_INT16 word=0;
            word |= static_cast<int8_t>(bytes_[index_++]) << 8;
            word |= static_cast<int8_t>(bytes_[index_++]);
            return word;
        }
        OT_UFWORD readUFWORD() {
            OT_UFWORD word=0;
            word |= static_cast<uint8_t>(bytes_[index_++]) << 8;
            word |= static_cast<uint8_t>(bytes_[index_++]);
            return word;
        }
        OT_FWORD readFWORD() {
            OT_FWORD word=0;
            word |= static_cast<int8_t>(bytes_[index_++]) << 8;
            word |= static_cast<int8_t>(bytes_[index_++]);
            return word;
        }
        OT_UINT24 readUInt24() {
            OT_UINT32 word=0;
            OT_UINT16 halfword = 0;
            halfword = readUInt16();
            word |= halfword << 16;
            OT_UINT8 byte = readUInt8();
            word |= byte;
            return word;
        }
        OT_INT24 readInt24() {
            OT_INT32 word=0;
            OT_INT16 halfword = 0;
            halfword = readInt16();
            word |= halfword << 16;
            OT_INT8 byte = readInt8();
            word |= byte;
            return word;
        }
        OT_UINT32 readUInt32() {
            OT_UINT32 word=0;
            OT_UINT16 halfword = 0;
            halfword = readUInt16();
            word |= halfword << 16;
            halfword = readUInt16();
            word |= halfword;
            return word;
        }
        OT_INT32 readInt32() {
            OT_INT32 word=0;
            OT_INT16 halfword = 0;
            halfword = readInt16();
            word |= halfword << 16;
            halfword = readInt16();
            word |= halfword;
            return word;
        }
        OT_FIXED readFixed() {
            OT_INT16 hi = readInt16();
            OT_INT16 lo = readInt16();
            return OT_FIXED(hi,lo);
        }
        OT_OFFSET16 readOffset16() {
            return readUInt16();
        }
        OT_OFFSET32 readOffset32() {
            return readUInt32();
        }

        OT_LONGDATETIME readLongDateTime() {
            OT_LONGDATETIME dbl_word = 0;
            OT_UINT32 word = readUInt32();
            dbl_word |= int64_t(word) << 32;
            word = readUInt32();
            dbl_word |= int64_t(word);
            return dbl_word;
        }

        std::string readTag() {
            OT_TAG tag;
            OT_UINT8 ch;
            for( size_t ii=0; ii < 4; ii++ ) {
                ch= readUInt8();
                tag[ii] = ch;
            }
            return tag;
        }

        uint32_t get_checksum() {
            size_t prev = index_; // cache old value
            uint32_t sum = 0L;
            while ( index_ < bytes_.size() ) {
                sum += readUInt32();
            }
            seek(prev); // restore value
            return sum;
        }

        size_t size()  const {
            return bytes_.size();
        }

        void pad() {
            padded_ = 0;
            while( bytes_.size() % 4 != 0 ) {
                bytes_.push_back(0x0);
                padded_++;
            }
        }

        size_t get_padding_size() const {
            return padded_;
        }

        TypeReader get_byte_sequence( size_t start ) const {
            std::vector<char>::const_iterator first = bytes_.begin() + start;
            std::vector<char>::const_iterator last = bytes_.end();
            std::vector<char> result(first,last);
            return result;
        }

        TypeReader get_byte_sequence( size_t start, size_t length ) const {
            std::vector<char>::const_iterator first = bytes_.begin() + start;
            std::vector<char>::const_iterator last = bytes_.begin() + start + length;
            std::vector<char> result(first,last);
            return result;
        }

        std::vector<OT_FWORD> readFWordVector() {
            std::vector<OT_FWORD> result;
            while ( index_ < bytes_.size() ) {
                result.push_back( readFWORD() );
                index_++;
            }
            return result;
        }

        std::vector<OT_UINT16> readUInt16Vector() {
            std::vector<OT_UINT16> result;
            while ( index_ < bytes_.size() ) {
                result.push_back( readUInt16() );
                index_++;
            }
            return result;
        }

        std::vector<OT_UINT8> readUInt8Vector() {
            std::vector<OT_UINT8> result;
            while ( index_ < bytes_.size() ) {
                result.push_back( readUInt8() );
                index_++;
            }
            return result;
        }

        std::vector<OT_OFFSET16> readOffset16Vector() {
            std::vector<OT_OFFSET16> result;
            while ( index_ < bytes_.size() ) {
                result.push_back( readOffset16() );
            }
            return result;
        }

        std::vector<OT_OFFSET32> readOffset32Vector() {
            std::vector<OT_OFFSET32> result;
            while ( index_ < bytes_.size() ) {
                result.push_back( readOffset32() );
            }
            return result;
        }

        std::vector<char> readCharVector() {
            std::vector<char>::const_iterator first = bytes_.begin() + index_;
            std::vector<char>::const_iterator last = bytes_.end();
            std::vector<char> result(first,last);
            return result;
        }

        std::vector<char> readChar( size_t n ) {
            std::vector<char>::const_iterator first = bytes_.begin() + index_;
            std::vector<char>::const_iterator last = bytes_.begin() + index_ + n;
            std::vector<char> result(first,last);
            index_ += n;
            return result;
        }

        std::string readPascalString() {
            int8_t len = readInt8();
            std::vector<char>::const_iterator first = bytes_.begin() + index_;
            std::vector<char>::const_iterator last = bytes_.begin() + index_ + len;
            std::string result( first, last );
            index_ += len;
            return result;
        }

        std::string readStringUTF8(int offset, int length) {
            // read in as if it was UTF-16 and then
            // we convert to UTF-8
            auto wide_string = std::u16string {};
            for( int ii = offset; ii < offset+length; ii++) {
                char16_t ch = bytes_[ii];
                wide_string.push_back( ch );
            }
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
            return convert.to_bytes(wide_string);
        }

        std::string readStringUTF16BF( int offset, int length ) {
            auto wide_string = std::u16string {};
            for( int ii = offset; ii < offset+length; ii+=2 ) {
                char16_t ch = 0;
                ch |= ( bytes_[ii] << 8 );
                ch |= (bytes_[ii+1]);
                wide_string.push_back( ch );
            }
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
            return convert.to_bytes(wide_string);
        }

        void remove_padding() {
            while( padded_ > 0 ) {
                bytes_.pop_back();
                padded_--;
            }
        }

    private:
        std::vector<char> bytes_;
        size_t padded_;
        size_t index_;
    };

}

#endif // TYPE_READER_H
