#include "editor_FileType.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include "editorConfig.h"
#include "editor_Update_Syntax.h"
#include "editor_FileType.h"

void editorSelectSyntaxHighlight()
{
  E.syntax = NULL;
  if (E.filename == NULL)
    return;

  char *extension = strrchr(E.filename, '.');

  for (unsigned int j = 0; j < HLDB_ENTRIES; j++)
  {
    struct editorSyntax *s = &HLDB[j];
    unsigned int i = 0;
    while (s->file_match[i])
    {
      int is_extension = (s->file_match[i][0] == '.');
      if ((is_extension && extension && !strcmp(extension, s->file_match[i])) || (is_extension && strstr(E.filename, s->file_match[i])))
      {
        E.syntax = s;
        return;
      }
      i++;
    }
  }
}