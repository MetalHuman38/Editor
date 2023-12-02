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
#include "editor_Read_Key.h"
#include "editor_Prompt.h"
#include "editorConfig.h"
#include "editorRow_RenderX_To_CursorX.h"
#include "editor_Find.h"
#include "enum_Editor_Key.h"
#include "editor_Find_Call_Back.h"

void editorFindCallBack(char *query, int key)
{
  static int last_match = -1;
  static int direction = 1;

  static int saved_highlight_line;
  static char *saved_highlight = NULL;

  if (saved_highlight)
  {
    memcpy(E.row[saved_highlight_line].highlighting, saved_highlight, E.row[saved_highlight_line].rsize);
    free(saved_highlight);
    saved_highlight = NULL;
  }

  if (key == '\r' || key == '\x1b')
  {
    last_match = -1;
    direction = 1;
    return;
  }
  else if (key == ARROW_RIGHT || key == ARROW_DOWN)
  {
    direction = 1;
  }
  else if (key == ARROW_LEFT || key == ARROW_UP)
  {
    direction = -1;
  }
  else
  {
    last_match = -1;
    direction = 1;
  }

  if (last_match == -1)
    direction = 1;
  int current = last_match;
  int i;
  for (i = 0; i < E.num_rows; i++)
  {
    current += direction;
    if (current == -1)
      current = E.num_rows - 1;
    else if (current == E.num_rows)
      current = 0;

    e_row *row = &E.row[current];
    char *match = strstr(row->render, query);
    if (match)
    {
      last_match = current;
      E.cursor_y = current;
      E.cursor_x = editorRowRxToCx(row, match - row->render);
      E.row_offset = E.num_rows;

      saved_highlight_line = current;
      saved_highlight = malloc(row->size);
      memcpy(saved_highlight, row->highlighting, row->rsize);
      memset(&row->highlighting[match - row->render], HIGHLIGHT_MATCH, strlen(query));
      break;
    }
  }
}