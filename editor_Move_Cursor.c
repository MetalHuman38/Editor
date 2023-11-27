#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "editor_Move_cursor.h"
#include "editorConfig.h"
#include "editor_Process_KeyPress.h"
#include "enum_Editor_Key.h"

void editorMoveCursor(int key)
{

  switch (key)
  {
  case ARROW_LEFT:
    if (E.cursor_x != 0)
    {
      E.cursor_x--;
    }
    break;
  case ARROW_RIGHT:
    if (E.cursor_x != E.screen_cols - 1)
    {
      E.cursor_x++;
    }
    break;
  case ARROW_UP:
    if (E.cursor_y != 0)
    {
      E.cursor_y--;
    }
    break;
  case ARROW_DOWN:
    if (E.cursor_y != E.screen_rows - 1)
    {
      E.cursor_y++;
    }
    break;
  }
}