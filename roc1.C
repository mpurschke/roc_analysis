#include "roc1.h"
R__LOAD_LIBRARY(libroc1.so)

void roc1(const char * filename)
{
  if ( filename != NULL)
    {
      pfileopen(filename);
    }
}
