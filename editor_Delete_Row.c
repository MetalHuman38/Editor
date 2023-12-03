#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include "editorConfig.h"
#include "editor_Free_Row.h"

void editorDeleteRow(int at)
{
  if (at < 0 || at >= E.num_rows)
    return;
  editorFreeRow(&E.row[at]);
  memmove(&E.row[at], &E.row[at + 1], sizeof(e_row) * (E.num_rows - at - 1));
  for (int j = at; j < E.num_rows - 1; j++)
    E.row[j].idx--;
  E.num_rows--;
  E.dirty_flag++;
}