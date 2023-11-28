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
  e_row *row = (E.cursor_y >= E.num_rows) ? NULL : &E.row[E.cursor_y];

  switch (key)
  {
  case ARROW_LEFT:
    if (E.cursor_x != 0)
    {
      E.cursor_x--;
    }
    else if (E.cursor_y > 0)
    {
      E.cursor_y--;
      E.cursor_x = E.row[E.cursor_y].size;
    }
    break;
  case ARROW_RIGHT:
    if (row && E.cursor_x < row->size)
    {
      E.cursor_x++;
    }
    else if (row && E.cursor_x == row->size)
    {
      E.cursor_y++;
      E.cursor_x = 0;
    }
    break;
  case ARROW_UP:
    if (E.cursor_y != 0)
    {
      E.cursor_y--;
    }
    break;
  case ARROW_DOWN:
    if (E.cursor_y < E.num_rows)
    {
      E.cursor_y++;
    }
    break;
  }

  row = (E.cursor_y > E.num_rows) ? NULL : &E.row[E.cursor_y];
  int row_len = row ? row->size : 0;
  if (E.cursor_x > row_len)
  {
    E.cursor_x = row_len;
  }
}