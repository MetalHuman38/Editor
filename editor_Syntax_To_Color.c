#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "enum_Editor_Key.h"

int editorSyntaxToColor(int highlight)
{
  switch (highlight)
  {
  case HIGHLIGHT_COMMENT:
  case HIGHLIGHT_MULTILINE_COMMENT:
    return 36;
  case HIGHLIGHT_KEYWORD1:
    return 33;
  case HIGHLIGHT_KEYWORD2:
    return 32;
  case HIGHLIGHT_STRING:
    return 35;
  case HIGHLIGHT_NUMBER:
    return 31;
  case HIGHLIGHT_MATCH:
    return 34;
  default:
    return 37;
  }
}