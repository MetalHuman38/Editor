#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "editorRow_CursorX_To_RenderX.h"
#include "editorConfig.h"
#include "editor_Read_Key.h"

int editorRowCxToRx(e_row *row, int cx)
{
  int rx = 0;
  int j;
  for (j = 0; j < cx; j++)
  {
    if (row->chars[j] == '\t')
      rx += (KILO_TAB_STOP - 1) - (rx % KILO_TAB_STOP);
    rx++;
  }
  return rx;
}