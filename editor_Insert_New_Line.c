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
#include "editor_Insert_Row.h"
#include "editor_Update_Row.h"

void editorInsertNewLine()
{
  if (E.cursor_x == 0)
  {
    editorInsertRow(E.cursor_y, "", 0);
  }
  else
  {
    e_row *row = &E.row[E.cursor_y];
    editorInsertRow(E.cursor_y + 1, &row->chars[E.cursor_x], row->size - E.cursor_x);
    row = &E.row[E.cursor_y];
    row->size = E.cursor_x;
    row->chars[row->size] = '\0';
    editorUpdateRow(row);
  }
  E.cursor_y++;
  E.cursor_x = 0;
}