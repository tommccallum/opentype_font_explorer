#include "catch_main.h"
#include "catch2.hpp"
#include "OpenTypeBitmap.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

use namespace OpenType;

TEST_CASE("create texture using OpenTypeBitmap", "[OpenTypeBitmap]" ) {
    auto bitmap = OpenTypeBitmap( 100, 100 );

    // set an alternating pattern
    for( size_t x = 0; x < 100; x++ ) {
        for( size_t y = 0; y < 100; y++ ) {
            if ( x % 2 == 0 ) {
                bitmap.set_pixel( x, y, 255 );
            }
        }
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        bitmap.get_width(),
        bitmap.get_height(),
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        bitmap.get_void_ptr_buffer()
    );
    REQUIRE( glGetError() == GL_NO_ERROR );

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // draw rectangle using texture and save to file
}
