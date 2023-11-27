#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "get_Windows_Size.h"
#include "editor_Read_Key.h"
#include "get_Cursor_Position.h"

int getWindowSize(int *rows, int *cols)
{

  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
  {
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) // The C command (Cursor Forward) moves the cursor to the
      return -1;                                              // right, and the B command (Cursor Down) moves the
                                                              // cursor down. The arguments says how much to move right ot left.
    return getCursorPosition(rows, cols);
  }
  else
  {
    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;
  }
}