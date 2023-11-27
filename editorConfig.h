#ifndef EDITOR_CONFIG_H
#define EDITOR_CONFIG_H

#include <termios.h>

struct editorConfig
{
  int cursor_x, cursor_y;
  int screen_rows;
  int screen_cols;
  struct termios orig_termios;
};

extern struct editorConfig E;

#endif
