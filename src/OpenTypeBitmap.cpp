#include "OpenTypeBitmap.h"

namespace OpenType {

    OpenTypeBitmap::OpenTypeBitmap(int width, int height) :
        width_(static_cast<unsigned int>(width)),
        height_(static_cast<unsigned int>(height)),
        stride_(1)
    {
        init();
    }

    OpenTypeBitmap::OpenTypeBitmap(unsigned int width, unsigned int height) :
        width_(width),
        height_(height),
        stride_(1)
    {
        init();
    }

    void OpenTypeBitmap::set_pixel( unsigned int x, unsigned int y, unsigned char ch ) {
        size_t index = get_index( x, y );
        if ( index < width_*height_ ) {
            pixels_[ index ] = ch;
        }
    }

    unsigned char OpenTypeBitmap::get_pixel(unsigned int x, unsigned int y) const {
        size_t index = get_index( x, y );
        if ( index < width_*height_ ) {
            return pixels_[ index ];
        }
        return 0;
    }

    unsigned int OpenTypeBitmap::get_width() const {
        return width_;
    }
    unsigned int OpenTypeBitmap::get_height() const {
        return height_;
    }

    /**
     * Get a C style buffer for use with Open GL
     * @return [description]
     */
    unsigned char* OpenTypeBitmap::get_void_ptr_buffer() {
        return static_cast<void*>(&pixels_);
    }

    void OpenTypeBitmap::init() {
        pixels_.reserve( width_ * height_ );
    }

    size_t OpenTypeBitmap::get_index( int x, int y ) {
        return ( x * width_ ) + y;
    }


}
