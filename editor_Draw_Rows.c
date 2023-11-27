#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void editorDrawRows()
{

  int y;
  for (y = 0; y < 24; y++)
  {
    write(STDOUT_FILENO, "\r\n", 3);
  }
}