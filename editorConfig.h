#ifndef EDITOR_CONFIG_H
#define EDITOR_CONFIG_H

#include <termios.h>
#include "E_Row_TypeDef.h"

struct editorConfig
{
  int cursor_x, cursor_y;
  int screen_rows;
  int screen_cols;
  int num_rows;
  e_row row;
  struct termios orig_termios;
};

extern struct editorConfig E;

#endif
