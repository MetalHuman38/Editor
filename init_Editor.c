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

void initEditor()
{
  if (getWindowSize(&E.screen_rows, &E.screen_cols) == -1)
    die("getWindowSize");
}