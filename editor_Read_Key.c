#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "editor_Process_KeyPress.h"
#include "die.h"
#include "enum_Editor_Key.h"

int editorReadKey()
{
  int nread;
  char c;

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
  {
    if (nread == -1 && errno != EAGAIN)
      die("read");
  }
  if (c == '\x1b')
  {
    char seq[3];

    if (read(STDIN_FILENO, &seq[0], 1) != 1)
      return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
      return '\x1b';

    if (seq[0] == '[')
    {
      switch (seq[1])
      {
      case 'A':
        return ARROW_UP;
      case 'B':
        return ARROW_DOWN;
      case 'C':
        return ARROW_RIGHT;
      case 'D':
        return ARROW_LEFT;
      }
    }
    return '\x1b';
  }
  else
  {
    return c;
  }
}
