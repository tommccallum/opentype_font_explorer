#include <stdexcept>
#include "OpenType.h"
#include "OpenTypeFont.h"
#include "OpenTypeFontMetrics.h"
#include "OpenTypeBitmap.h"

namespace OpenType {

    OpenTypeFont::OpenTypeFont( std::string const filename ) :
        filename_(filename),
        error_(0)
    {
        init();
    }

    bool OpenTypeFont::is_error() const {
        return error_ == 0;
    }

    OpenTypeFontMetrics const OpenTypeFont::get_metrics( char character ) const {
        auto metrics = OpenTypeFontMetrics {};
        (void) character;
        return metrics;
    }

    OpenTypeBitmap const OpenTypeFont::get_bitmap( char character ) const {
        auto bitmap = OpenTypeBitmap {};
        (void) character;
        return bitmap;
    }

    void OpenTypeFont::init() {
        try {
            FontReader reader( filename_ );
            table_.from_bytes( reader );
        } catch( std::exception& ex) {

        }
    }
}
