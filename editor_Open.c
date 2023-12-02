#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include "editor_Open.h"
#include "editorConfig.h"
#include "die.h"
#include "editor_Read_Key.h"
#include "editor_Insert_Row.h"

void editorOpen(char *filename)
{
  free(E.filename);
  E.filename = strdup(filename);
  FILE *fp = fopen(filename, "r");
  if (!fp)
    die("fopen");
  char *line = NULL;
  size_t line_cap = 0;
  ssize_t line_len;

  while ((line_len = getline(&line, &line_cap, fp)) != -1)
  {
    while (line_len > 0 && (line[line_len - 1] == '\n' || line[line_len - 1] == '\r'))
      line_len--;
    editorInsertRow(E.num_rows, line, line_len);
  }

  free(line);
  fclose(fp);
  E.dirty_flag = 0;
}