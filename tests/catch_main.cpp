#define CATCH_CONFIG_RUNNER
#include "catch2.hpp"
#include "catch_main.h"

std::string ttf_path;

int main( int argc, char* argv[] )
{
  Catch::Session session; // There must be exactly one instance

  // Build a new parser on top of Catch's
  using namespace Catch::clara;

  auto cli = session.cli() | Opt(ttf_path,"TTF filepath")
    ["--ttf"]("TTF Path"); // Get Catch's composite command line parser

  // Now pass the new composite back to Catch so it uses that
  session.cli( cli );

  // Let Catch (using Clara) parse the command line
  int returnCode = session.applyCommandLine( argc, argv );
  if( returnCode != 0 ) // Indicates a command line error
      return returnCode;

  return session.run();
}
