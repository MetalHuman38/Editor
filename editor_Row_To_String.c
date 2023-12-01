#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include "editor_Row_To_String.h"

char *editorRowToString(int *buffer_len)
{
  int total_len = 0;
  int j;
  for (j = 0; j < E.num_rows; j++)
    total_len += E.row[j].size + 1;
  *buffer_len = total_len;

  char *buffer = malloc(total_len);
  char *p = buffer;
  for (j = 0; j < E.num_rows; j++)
  {
    memcpy(p, E.row[j].chars, E.row[j].size);
    p += E.row[j].size;
    *p = '\n';
    p++;
  }
  return buffer;
}
