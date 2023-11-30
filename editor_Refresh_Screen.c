#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "editor_Draw_Rows.h"
#include "append_Buffer_Struct.h"
#include "ab_Append.h"
#include "ab_Append_Free.h"
#include "editorConfig.h"
#include "editor_Scroll.h"
#include "editor_Draw_StatusBar.h"
#include "editor_Draw_Message_Bar.h"

void editorRefreshScreen()
{
  editorScroll();

  struct appendBuffer ab = ABUF_INIT;

  abAppend(&ab, "\x1b[?25l", 6);

  abAppend(&ab, "\x1b[H", 3); // This escape sequence is only 3 bytes long, and uses the H command
                              // (cursor position ) to position the cursor.

  editorDrawRows(&ab);
  editorDrawStatusBar(&ab);
  editorDrawMessageBar(&ab);

  char buf[32];
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.cursor_y - E.row_offset) + 1, (E.render_x + 1));
  abAppend(&ab, buf, strlen(buf));

  abAppend(&ab, "\x1b[?25h", 6);

  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}