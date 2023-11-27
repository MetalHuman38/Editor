#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "init_Editor.h"
#include "get_Windows_Size.h"
#include "editorConfig.h"
#include "die.h"
#include "E_Row_TypeDef.h"

void initEditor()
{
  E.cursor_x = 0; // Horizontal co-ordinates of the cursor(column)
  E.cursor_y = 0; // Vertical co-ordinates of the cursor (Rows)
  E.num_rows = 0;

  if (getWindowSize(&E.screen_rows, &E.screen_cols) == -1)
    die("getWindowSize");
}