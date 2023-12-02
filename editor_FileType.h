#ifndef EDITOR_FILETYPE_H
#define EDITOR_FILETYPE_H

#include <stdio.h>
#include "editorConfig.h"

extern char *C_HL_extensions[];

struct editorSyntax
{
  char *filetype;
  char **file_match;
  int flags;
};

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

extern struct editorSyntax HLDB[];

#define HL_HIGHLIGHT_NUMBERS (1 << 0)

#endif