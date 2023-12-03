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
#include "editor_Syntax.h"
#include "editor_Update_Syntax.h"

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

char *C_HL_extensions[] = {".c", ".h", ".cpp", NULL};
char *CH_HL_keywords[] = {"switch", "if", "while", "for", "break", "continue", "return", "else", "struct", "union", "typedef", "static", "enum", "class", "case", "int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|", "void|", NULL};

struct editorSyntax HLDB[] = {
    {"c",
     C_HL_extensions,
     CH_HL_keywords,
     "//", "/*", "*/",
     HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS},
    // Define rules for other file types as needed
};

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

        int fileRow;
        for (fileRow = 0; fileRow < E.num_rows; fileRow++)
        {
          editorUpdateSyntax(&E.row[fileRow]);
        }
        return;
      }
      i++;
    }
  }
}