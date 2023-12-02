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
#include "is_Separator.h"
#include "editor_FileType.h"

char *C_HL_extensions[] = {".c", ".h", ".cpp", NULL};

struct editorSyntax HLDB[] = {
    {"c",
     C_HL_extensions,
     HL_HIGHLIGHT_NUMBERS

    },

};

void editorUpdateSyntax(e_row *row)
{
  row->highlighting = realloc(row->highlighting, row->size);
  memset(row->highlighting, HIGHLIGHT_NORMAL, row->size);

  if (E.syntax == NULL)
    return;

  int prev_sep = 1;

  int i = 0;
  while (i < row->rsize)
  {
    char c = row->render[i];
    unsigned char prev_highlight = (i > 0) ? row->highlighting[i - 1] : HIGHLIGHT_NORMAL;

    if (E.syntax->flags & HL_HIGHLIGHT_NUMBERS)
    {
      if ((isdigit(c) && (prev_sep || prev_highlight == HIGHLIGHT_NUMBER)) ||
          (c == '.' && prev_highlight == HIGHLIGHT_NUMBER))
      {
        row->highlighting[i] = HIGHLIGHT_NUMBER;
        i++;
        prev_sep = 0;
        continue;
      }
    }

    prev_sep = isSeparator(c);
    i++;
  }
}