/*
oakpark_dup_str() demo

by: Iman S. H. Suyoto

Copyright (C) 2005 Iman S. H. Suyoto
 
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons
to whom the Software is furnished to do so, subject to the
following conditions:
 
The above copyright notice and this permission notice shall
be included in all copies or substantial portions of the
Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "oakpark.h"

int main(void)
{ char * line;
  int status = 0;

  fprintf(stderr, "Enter a line:\n");
  line = oakpark_get_line(stdin, NULL);
  if(line)
  { char * line_dup = oakpark_dup_str(line);

    if(line_dup)
    { printf("The two strings must be the same:\n%s%s",
             line, line_dup);
      free(line_dup);
      }
    else
    { fprintf(stderr, "Can't duplicate the line.\n");
      status = EXIT_FAILURE;
      }
    free(line); 
    }
  else
  { status = EXIT_FAILURE;
    }
  return status;
  }
