#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include "append_Buffer_Struct.h"
#include "ab_Append.h"
#include "editorConfig.h"

void editorDrawMessageBar(struct appendBuffer *ab)
{
  abAppend(ab, "\x1b[K", 3);
  int message_len = strlen(E.status_message);
  if (message_len > E.screen_cols)
    message_len = E.screen_cols;
  if (message_len && time(NULL) - E.statusMsg_Display_time < 5)
    abAppend(ab, E.status_message, message_len);
}