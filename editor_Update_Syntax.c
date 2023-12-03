#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "enum_Editor_Key.h"
#include "editor_Syntax.h"
#include "editorConfig.h"
#include "is_Separator.h"

void editorUpdateSyntax(e_row *row)
{
  row->highlighting = realloc(row->highlighting, row->size);
  memset(row->highlighting, HIGHLIGHT_NORMAL, row->size);

  if (E.syntax == NULL)
    return;

  char **keywords = E.syntax->keywords;

  char *scs = E.syntax->singleline_comment_start;
  char *mcs = E.syntax->multiline_comment_start;
  char *mce = E.syntax->multiline_comment_end;
  int scs_len = scs ? strlen(scs) : 0;
  int mcs_len = mcs ? strlen(mcs) : 0;
  int mce_len = mce ? strlen(mce) : 0;

  int prev_sep = 1;
  int in_string = 0;
  int in_comment = (row->idx > 0 && E.row[row->idx - 1].highlight_open_comment);

  int i = 0;
  while (i < row->rsize)
  {
    char c = row->render[i];
    unsigned char prev_highlight = (i > 0) ? row->highlighting[i - 1] : HIGHLIGHT_NORMAL;

    if (scs_len && !in_string && !in_comment)
    {
      if (!strncmp(&row->render[i], scs, scs_len))
      {
        memset(&row->highlighting[i], HIGHLIGHT_COMMENT, row->size - i);
        break;
      }
    }

    if (mcs_len && mce_len && !in_string)
    {
      if (in_comment)
      {
        row->highlighting[i] = HIGHLIGHT_MULTILINE_COMMENT;
        if (!strncmp(&row->render[i], mce, mce_len))
        {
          i += mce_len;
          in_comment = 0;
          prev_sep = 1;
          continue;
        }
        else
        {
          i++;
          continue;
        }
      }
      else if (!strncmp(&row->render[i], mcs, mcs_len))
      {
        memset(&row->highlighting[i], HIGHLIGHT_MULTILINE_COMMENT, mcs_len);
        i += mcs_len;
        in_comment = 1;
        continue;
      }
    }
    if (E.syntax->flags & HL_HIGHLIGHT_STRINGS)
    {
      if (in_string)
      {
        row->highlighting[i] = HIGHLIGHT_STRING;
        if (c == '\\' && i + 1 < row->rsize)
        {
          row->highlighting[i + 1] = HIGHLIGHT_STRING;
          i += 2;
          continue;
        }
        if (c == in_string)
          in_string = 0;
        i++;
        prev_sep = 1;
        continue;
      }
      else
      {
        if (c == '"' || c == '\'')
        {
          in_string = c;
          row->highlighting[i] = HIGHLIGHT_STRING;
          i++;
          continue;
        }
      }
    }

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

    if (prev_sep)
    {
      int j;
      for (j = 0; keywords[j]; j++)
      {
        int keywords_len = strlen(keywords[j]);
        int keyword2 = keywords[j][keywords_len - 1] == '|';
        if (keyword2)
          keywords_len--;

        if (!strncmp(&row->render[i], keywords[j], keywords_len) && isSeparator(row->render[i + keywords_len]))
        {
          memset(&row->highlighting[i], keyword2 ? HIGHLIGHT_KEYWORD2 : HIGHLIGHT_KEYWORD1, keywords_len);
          i += keywords_len;
          break;
        }
      }
      if (keywords[j] != NULL)
      {
        prev_sep = 0;
        continue;
      }
    }

    prev_sep = isSeparator(c);
    i++;
  }
  int changed = (row->highlight_open_comment != in_comment);
  row->highlight_open_comment = in_comment;
  if (changed && row->idx + 1 < E.num_rows)
    editorUpdateSyntax(&E.row[row->idx + 1]);
}