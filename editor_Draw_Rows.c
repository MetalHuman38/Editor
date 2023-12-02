#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "editorConfig.h"
#include "E_Row_TypeDef.h"
#include "append_Buffer_Struct.h"
#include "ab_Append.h"
#include "editor_Read_Key.h"
#include "enum_Editor_Key.h"
#include "editor_Syntax_To_Color.h"

void editorDrawRows(struct appendBuffer *ab)
{

  int y;
  for (y = 0; y < E.screen_rows; y++)
  {
    int file_row = y + E.row_offset;
    if (file_row >= E.num_rows)
    {

      if (E.num_rows == 0 && y == E.screen_rows / 3)
      {
        char welcome[80];
        int welcome_len = snprintf(welcome, sizeof(welcome), "Kilo Editor -- version %s", KILO_VERSION);
        if (welcome_len > E.screen_cols)
          welcome_len = E.screen_cols;
        int padding = (E.screen_cols - welcome_len / 2);
        if (padding)
        {
          abAppend(ab, "~", 1);
          padding--;
        }
        while (padding--)
          abAppend(ab, " ", 1);
        abAppend(ab, welcome, welcome_len);
      }
      else
      {
        abAppend(ab, "~", 1);
      }
    }
    else
    {
      int len = E.row[file_row].rsize - E.col_offset;
      if (len < 0)
        len = 0;
      if (len > E.screen_cols)
        len = E.screen_cols;
      char *c = &E.row[file_row].render[E.col_offset];
      unsigned char *highlight = &E.row[file_row].highlighting[E.col_offset];
      int current_color = -1;
      int j;
      for (j = 0; j < len; j++)
      {
        if (highlight[j] == HIGHLIGHT_NORMAL)
        {
          if (current_color != -1)
          {
            abAppend(ab, "\x1b[39m", 5);
            current_color = -1;
          }
          abAppend(ab, &c[j], 1);
        }
        else
        {
          int color = editorSyntaxToColor(highlight[j]);
          if (color != current_color)
          {
            char buffer[16];
            int clen = snprintf(buffer, sizeof(buffer), "\x1b[%dm", color);
            abAppend(ab, buffer, clen);
          }

          abAppend(ab, &c[j], 1);
        }
      }
      abAppend(ab, "\x1b[39m", 5);
    }
    abAppend(ab, "\x1b[K", 3);

    abAppend(ab, "\r\n", 2);
  }
}