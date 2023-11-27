#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "editorConfig.h"
// Include your custom header files.
#include "append_Buffer_Struct.h"
#include "ab_Append.h"
#include "editor_Read_Key.h"

void editorDrawRows(struct appendBuffer *ab)
{

  int y;
  for (y = 0; y < E.screen_rows; y++)
  {
    if (y == E.screen_rows / 3)
    {
      char welcome[80];
      int welcome_len = snprintf(welcome, sizeof(welcome), "Kilo Editor -- version %s", KILO_VERSION);
      if (welcome_len > E.screen_cols)
        welcome_len = E.screen_cols;
      int padding = (E.screen_cols - welcome_len / 2);
      if (padding)
      {
        abAppend(ab, "~", 1);
        padding--;
      }
      while (padding--)
        abAppend(ab, " ", 1);
      abAppend(ab, welcome, welcome_len);
    }
    else
    {
      abAppend(ab, "~", 1);
    }

    abAppend(ab, "\x1b[K", 3);
    if (y < E.screen_rows - 1)
    {
      abAppend(ab, "\r\n", 2);
    }
  }
}