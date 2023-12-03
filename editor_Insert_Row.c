#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "editor_Insert_Row.h"
#include "editorConfig.h"
#include "editor_Update_Row.h"

void editorInsertRow(int at, char *s, size_t len)
{
  if (at < 0 || at > E.num_rows)
    return;
  E.row = realloc(E.row, sizeof(e_row) * (E.num_rows + 1));
  memmove(&E.row[at + 1], &E.row[at], sizeof(e_row) * (E.num_rows - at));
  for (int j = at + 1; j <= E.num_rows; j++)
    E.row[j].idx++;

  E.row[at].idx = at;

  E.row[at].size = len;
  E.row[at].chars = malloc(len + 1);
  memcpy(E.row[at].chars, s, len);
  E.row[at].chars[len] = '\0';

  E.row[at].rsize = 0;
  E.row[at].render = NULL;
  E.row[at].highlighting = NULL;
  E.row[at].highlight_open_comment = 0;
  editorUpdateRow(&E.row[at]);

  E.num_rows++;
  E.dirty_flag++;
}