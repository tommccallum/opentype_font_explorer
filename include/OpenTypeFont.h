#ifndef OPENTYPE_FONT_H
#define OPENTYPE_FONT_H

#include <string>
#include <memory>

namespace OpenType {
    class OpenTypeFontMetrics;
    class OpenTypeBitmap;
    class OffsetTable;

    /**
     * Main class for calling libraries to create
     */
    class OpenTypeFont {
    public:
        /**
         * Constructs a OpenTypeFont by reading the ttf
         * @param filename [description]
         */
        OpenTypeFont( std::string const filename );

        /**
         * Tests is font was opened successfully
         * and is ready for user to call other methods
         * @return [description]
         */
        bool is_error() const;

        /**
         * Get the font metrics for this font
         * @param character     single byte character
         * @return [description]
         */
        OpenTypeFontMetrics const get_metrics( char character ) const;

        /**
         * Get a bitmap for this character
         * @return [description]
         */
        OpenTypeBitmap const get_bitmap( char character ) const;

    private:
        std::string filename_;
        int error_;
        OffsetTable table_;

        void init();
    };

}

#endif // OPENTYPE_FONT_H
