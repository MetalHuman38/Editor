#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include "append_Buffer_Struct.h"
#include "editorConfig.h"
#include "E_Row_TypeDef.h"
#include "editor_Row_Delete_Char.h"

void editorFreeRow(e_row *row)
{
  free(row->render);
  free(row->chars);
}