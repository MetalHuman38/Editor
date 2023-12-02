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
#include "editor_Row_Insert_Char.h"

void editorInsertChar(int c)
{
  if (E.cursor_y == E.num_rows)
  {
    editorInsertRow(E.num_rows, "", 0);
  }
  editorRowInsertChar(&E.row[E.cursor_y], E.cursor_x, c);
  E.cursor_x++;
}