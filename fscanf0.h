#include <stdarg.h>
#include "libioP.h"
#include <stdio.h>

int fscanf0(FILE *stream, const char *format, ...) {
  va_list arg;
  int done;

  va_start(arg,format);
  done=vfscanf(stream,format,arg);
  va_end(arg);
  return done;
}
