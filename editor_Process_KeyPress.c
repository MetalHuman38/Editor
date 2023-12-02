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
#include "editor_Insert_Char.h"
#include "editor_Save.h"
#include "editor_Set_Status_Message.h"
#include "editor_Delete_Char.h"
#include "editor_Insert_New_Line.h"
#include "editor_Find.h"

void editorProcessKeyPress()
{
  static int quit_times = KILO_QUIT_TIMES;

  int c = editorReadKey();

  switch (c)
  {
  case '\r':
    editorInsertNewLine();
    break;

  case CTRL_KEY('q'):
    if (E.dirty_flag && quit_times > 0)
    {
      editorSetStatusMessage("WARNING!!! File has unsaved changes."
                             "Press Ctrl-Q %d more times to quit.",
                             quit_times);
      quit_times--;
      return;
    }
    write(STDOUT_FILENO, "\x1b[2J", 4); // 4 in the parameter indicates writing 4 bytes out to the terminal.
                                        // first byte(\x1b) is the escape character or 27 in decimal.
                                        // other three bytes ([2J).
    write(STDOUT_FILENO, "\x1b[H", 3);  // This escape sequence is only 3 bytes long, and uses the H command
                                        // (cursor position ) to position the cursor.
    exit(0);
    break;

  case CTRL_KEY('s'):
    editorSave();
    break;

  case HOME_KEY:
    E.cursor_x = 0;
    break;

  case END_KEY:
    if (E.cursor_y < E.num_rows)
      E.cursor_x = E.row[E.cursor_y].size;
    break;

  case CTRL_KEY('f'):
    editorFind();
    break;

  case BACKSPACE:
  case CTRL_KEY('h'):
  case DEL_KEY:
    if (c == DEL_KEY)
      editorMoveCursor(ARROW_RIGHT);
    editorDeleteChar();
    break;

  case PAGE_UP:
  case PAGE_DOWN:
  {
    if (c == PAGE_UP)
    {
      E.cursor_y = E.row_offset;
    }
    else if (c == PAGE_DOWN)
    {
      E.cursor_y = E.row_offset + E.screen_rows - 1;
      if (E.cursor_y > E.num_rows)
        E.cursor_y = E.num_rows;
    }
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

  case CTRL_KEY('l'):
  case '\x1b':
    break;

  default:
    editorInsertChar(c);
    break;
  }
  quit_times = KILO_QUIT_TIMES;
}