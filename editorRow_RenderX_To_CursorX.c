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

int editorRowRxToCx(e_row *row, int rx)
{

  int cur_rx = 0;
  int cx;
  for (cx = 0; cx < row->size; cx++)
  {
    cur_rx += (KILO_TAB_STOP - 1) - (cur_rx % KILO_TAB_STOP);
    cur_rx++;

    if (cur_rx > rx)
      return cx;
  }
  return cx;
}