#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"

int main (int argc, char *argv[])
{
  fprintf(stdout,"%s Version %d.%d\n",
            argv[0],
            OPENTYPE_VERSION_MAJOR,
            OPENTYPE_VERSION_MINOR);
  return 0;
}
