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
#include "editor_Free_Row.h"

void editorDeleteRow(int at)
{
  if (at < 0 || at >= E.num_rows)
    return;
  editorFreeRow(&E.row[at]);
  memmove(&E.row[at], &E.row[at + 1], sizeof(e_row) * (E.num_rows - at - 1));
  E.num_rows--;
  E.dirty_flag++;
}