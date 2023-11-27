#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "editor_Draw_Rows.h"
#include "append_Buffer_Struct.h"
#include "ab_Append.h"
#include "ab_Append_Free.h"

void editorRefreshScreen()
{

  struct appendBuffer ab = ABUF_INIT;

  abAppend(&ab, "\x1b[?25l", 6);

  abAppend(&ab, "\x1b[2J", 4); // 4 in the parameter indicates writing 4 bytes out to the terminal.
                               // first byte(\x1b) is the escape character or 27 in decimal.
                               // other three bytes ([2J).

  abAppend(&ab, "\x1b[H", 3); // This escape sequence is only 3 bytes long, and uses the H command
                              // (cursor position ) to position the cursor.

  editorDrawRows(&ab);

  abAppend(&ab, "\x1b[H", 3);
  abAppend(&ab, "\x1b[?25h", 6);

  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}