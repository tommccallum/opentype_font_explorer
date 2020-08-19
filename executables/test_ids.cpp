#include <iostream>
#include "internals/NameIds.h"
#include "internals/WindowsLanguageIds.h"
#include "internals/MacintoshEncodingIds.h"
#include "internals/MacintoshLanguageIds.h"
#include <algorithm>
#include <iterator>

using namespace OpenType;



int main() {
    std::cout << "== Name Ids ==" << std::endl;
    std::copy( std::begin(name_ids), std::end(name_ids), std::ostream_iterator<NameID>(std::cout) );
    std::cout << "== Macintosh Encoding Ids ==" << std::endl;
    std::copy( std::begin(macintosh_encoding_ids), std::end(macintosh_encoding_ids), std::ostream_iterator<MacintoshEncodingID>(std::cout) );
    std::cout << "== Macintosh Language Ids ==" << std::endl;
    std::copy( std::begin(macintosh_language_ids), std::end(macintosh_language_ids), std::ostream_iterator<MacintoshLanguageID>(std::cout) );
    std::cout << "== Windows Language Ids ==" << std::endl;
    std::copy( std::begin(windows_language_ids), std::end(windows_language_ids), std::ostream_iterator<WindowsLanguageID>(std::cout) );
}
