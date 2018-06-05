/*
oakpark_get_ascii_val() demo

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
#include <ctype.h>
#include "oakpark.h"

int main(void)
{ size_t len;
  char * line;

  fprintf(stderr, "Enter a line:\n");
  line = oakpark_get_line(stdin, &len);
  if(line)
  { char * curr = line;
    char curr_char;

    while((curr_char = *curr) != '\0')
    { printf("Character: ");
      if(iscntrl((unsigned char)curr_char))
      { printf("[unprintable]");
        }
      else
      { printf("'%c'", curr_char);
        }
      printf("; ASCII value: %d\n",
             oakpark_get_ascii_val(curr_char));
      curr++;
      }
    free(line);
    }
  return 0;
  }
