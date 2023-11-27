#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "editor_Read_Key.h"
#include "editor_Move_cursor.h"
#include "enum_Editor_Key.h"
#include "editorConfig.h"

void editorProcessKeyPress()
{
  int c = editorReadKey();

  switch (c)
  {
  case CTRL_KEY('q'):
    write(STDOUT_FILENO, "\x1b[2J", 4); // 4 in the parameter indicates writing 4 bytes out to the terminal.
                                        // first byte(\x1b) is the escape character or 27 in decimal.
                                        // other three bytes ([2J).

    write(STDOUT_FILENO, "\x1b[H", 3); // This escape sequence is only 3 bytes long, and uses the H command
                                       // (cursor position ) to position the cursor.

    exit(0);
    break;

  case HOME_KEY:
    E.cursor_x = 0;
    break;

  case END_KEY:
    E.cursor_x = E.screen_cols - 1;
    break;

  case PAGE_UP:
  case PAGE_DOWN:
  {
    int times = E.screen_rows;
    while (times--)
      editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
  }
  break;

  case ARROW_UP:
  case ARROW_DOWN:
  case ARROW_LEFT:
  case ARROW_RIGHT:
    editorMoveCursor(c);
    break;
  }
}