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
    E.cursor_x--;
    break;
  case ARROW_RIGHT:
    E.cursor_x++;
    break;
  case ARROW_UP:
    E.cursor_y--;
    break;
  case ARROW_DOWN:
    E.cursor_y++;
    break;
  }
}