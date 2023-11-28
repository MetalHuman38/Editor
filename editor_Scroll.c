#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "editor_Scroll.h"
#include "editorConfig.h"
#include "editor_Refresh_Screen.h"
#include "editorRow_CursorX_To_RenderX.h"

void editorScroll()
{
  E.render_x = 0;
  if (E.cursor_y < E.num_rows)
  {
    E.render_x = editorRowCxToRx(&E.row[E.cursor_y], E.cursor_x);
  }
  E.render_x = E.cursor_x;

  if (E.cursor_y < E.row_offset)
  {

    E.row_offset = E.cursor_y;
  }

  if (E.cursor_y >= E.row_offset + E.screen_rows)
  {
    E.row_offset = E.cursor_y - E.screen_rows + 1;
  }

  if (E.render_x < E.col_offset)
  {
    E.col_offset = E.render_x;
  }

  if (E.render_x >= E.col_offset + E.screen_cols)
  {
    E.col_offset = E.render_x - E.screen_cols + 1;
  }
}
