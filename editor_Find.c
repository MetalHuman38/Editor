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
#include "editor_Find_Call_Back.h"

void editorFind()
{
  int saved_cursor_x = E.cursor_x;
  int saved_cursor_y = E.cursor_y;
  int saved_col_offset = E.col_offset;
  int saved_row_offset = E.row_offset;

  char *query = editorPrompt("Search: %s (ESC/Arrows/Enter)", editorFindCallBack);
  if (query)
  {
    free(query);
  }
  else
  {
    E.cursor_x = saved_cursor_x;
    E.cursor_y = saved_cursor_y;
    E.col_offset = saved_col_offset;
    E.row_offset = saved_row_offset;
  }
}