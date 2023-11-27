#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "editor_Draw_Rows.h"

void editorRefreshScreen()
{

  write(STDOUT_FILENO, "\x1b[2J", 4); // 4 in the parameter indicates writing 4 bytes out to the terminal.
                                      // first byte(\x1b) is the escape character or 27 in decimal.
                                      // other three bytes ([2J).

  write(STDOUT_FILENO, "\x1b[H", 3); // This escape sequence is only 3 bytes long, and uses the H command
                                     // (cursor position ) to position the cursor.

  editorDrawRows();

  write(STDOUT_FILENO, "\r\n", 3);
}