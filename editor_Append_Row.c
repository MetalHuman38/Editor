#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "editor_Append_Row.h"
#include "editorConfig.h"
#include "editor_Draw_Rows.h"
#include "editor_Update_Row.h"

void editorAppendRow(char *s, size_t len)
{
  E.row = realloc(E.row, sizeof(e_row) * (E.num_rows + 1));

  int at = E.num_rows;
  E.row[at].size = len;
  E.row[at].chars = malloc(len + 1);
  memcpy(E.row[at].chars, s, len);
  E.row[at].chars[len] = '\0';

  E.row[at].rsize = 0;
  E.row[at].render = NULL;
  editorUpdateRow(&E.row[at]);

  E.num_rows++;
}