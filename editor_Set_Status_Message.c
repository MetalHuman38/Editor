#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdarg.h>

#include "editorConfig.h"

void editorSetStatusMessage(const char *fmt, ...)
{

  va_list ap;
  va_start(ap, fmt);
  vsnprintf(E.status_message, sizeof(E.status_message), fmt, ap);
  va_end(ap);
  E.statusMsg_Display_time = time(NULL);
}