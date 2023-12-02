#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "editor_Update_Row.h"
#include "E_Row_TypeDef.h"
#include "editorConfig.h"
#include "editor_Read_Key.h"
#include "enum_Editor_Key.h"

int editorSyntaxToColor(int highlight)
{
  switch (highlight)
  {
  case HIGHLIGHT_NUMBER:
    return 31;
  case HIGHLIGHT_MATCH:
    return 34;
  default:
    return 37;
  }
}