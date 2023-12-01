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
#include "editorConfig.h"
#include "E_Row_TypeDef.h"
#include "editor_Row_Delete_Char.h"

void editorDeleteChar()
{
  if (E.cursor_y == E.num_rows)
    return;

  e_row *row = &E.row[E.cursor_y];
  if (E.cursor_x > 0)
  {
    editorRowDeleteChar(row, E.cursor_x - 1);
    E.cursor_x--;
  }
}