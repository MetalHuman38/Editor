#include "editor_Syntax.h"
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

void editorDrawStatusBar(struct appendBuffer *ab)
{
  abAppend(ab, "\x1b[7m", 4);
  char status[80], right_status[80];
  int len = snprintf(status, sizeof(status), "%.20s - %d lines %s", E.filename ? E.filename : "[No Name]", E.num_rows,
                     E.dirty_flag ? "(modified)" : "");

  int right_len = snprintf(right_status, sizeof(right_status), "%s | %d/%d", E.syntax ? E.syntax->filetype : "no ft", E.cursor_y + 1, E.num_rows);

  if (len > E.screen_cols)
    len = E.screen_cols;
  abAppend(ab, status, len);
  while (len < E.screen_cols)
  {
    if (E.screen_cols - len == right_len)
    {
      abAppend(ab, right_status, right_len);
      break;
    }
    else
    {
      abAppend(ab, " ", 1);
      len++;
    }
  }
  abAppend(ab, "\x1b[m", 3);
  abAppend(ab, "\r\n", 2);
}
