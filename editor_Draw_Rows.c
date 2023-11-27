#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "editorConfig.h"
// Include your custom header files.
#include "append_Buffer_Struct.h"
#include "ab_Append.h"

void editorDrawRows(struct appendBuffer *ab)
{

  int y;
  for (y = 0; y < E.screen_rows; y++)
  {
    abAppend(ab, "~", 1);

    if (y < E.screen_rows - 1)
    {
      abAppend(ab, "\r\n", 2);
    }
  }
}