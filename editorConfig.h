#ifndef EDITOR_CONFIG_H
#define EDITOR_CONFIG_H

#include <termios.h>
#include <time.h>
#include "E_Row_TypeDef.h"

struct editorSyntax;

struct editorConfig
{
  int cursor_x, cursor_y;
  int render_x;
  int row_offset;
  int col_offset;
  int screen_rows;
  int screen_cols;
  int num_rows;
  e_row *row;
  int dirty_flag;
  char *filename;
  char status_message[80];
  time_t statusMsg_Display_time;
  struct editorSyntax *syntax;
  struct termios orig_termios;
};

extern struct editorConfig E;

#endif
