#ifndef EDITOR_SYNTAX_H
#define EDITOR_SYNTAX_H

#include <string.h>

#define HL_HIGHLIGHT_NUMBERS (1 << 0)
#define HL_HIGHLIGHT_STRINGS (1 << 0)

struct editorSyntax
{
  char *filetype;
  char **file_match;
  char **keywords;
  char *singleline_comment_start;
  char *multiline_comment_start;
  char *multiline_comment_end;
  int flags;
};

extern struct editorSyntax HLDB[];
extern int HLDB_ENTRIES;

#endif
