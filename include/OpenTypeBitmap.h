#ifndef OPEN_TYPE_BITMAP_H
#define OPEN_TYPE_BITMAP_H

namespace OpenType {

    class OpenTypeBitmap {
    public:
        OpenTypeBitmap(int width, int height);
        OpenTypeBitmap(unsigned int width, unsigned int height);
        void set_pixel( unsigned int x, unsigned int y, unsigned char ch );
        unsigned char get_pixel(unsigned int x, unsigned int y) const;
        unsigned int get_width() const;
        unsigned int get_height() const;
        unsigned char* get_void_ptr_buffer(); // get c style buffer reference
    private:
        unsigned int width_;
        unsigned int height_;
        unsigned int stride_;
        std::vector<unsigned char> pixels_;

        void init();
        size_t get_index( int x, int y );
    };

}

#endif // OPEN_TYPE_FONT_BITMAP_H
