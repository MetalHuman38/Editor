#ifndef EDITOR_CONFIG_H
#define EDITOR_CONFIG_H

#include <termios.h>

struct editorConfig
{
  struct termios orig_termios;
};

extern struct editorConfig E;

#endif
