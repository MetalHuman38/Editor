#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include "editor_Set_Status_Message.h"
#include "editor_Refresh_Screen.h"
#include "editor_Read_Key.h"
#include "enum_Editor_Key.h"

char *editorPrompt(char *prompt, void (*callback)(char *, int))
{

  size_t buffer_size = 128;
  char *buffer = malloc(buffer_size);

  size_t buffer_len = 0;
  buffer[0] = '\0';

  while (1)
  {
    editorSetStatusMessage(prompt, buffer);
    editorRefreshScreen();

    int c = editorReadKey();
    if (c == DEL_KEY || c == CTRL_KEY('h') || c == BACKSPACE)
    {
      if (buffer_len != 0)
        buffer[--buffer_len] = '\0';
    }
    else if (c == '\x1b')
    {
      editorSetStatusMessage("");
      if (callback)
        callback(buffer, c);
      free(buffer);
      return NULL;
    }
    else if (c == '\r')
    {
      if (buffer_len != 0)
      {
        editorSetStatusMessage("");
        if (callback)
          callback(buffer, c);
        return buffer;
      }
    }
    else if (!iscntrl(c) && c < 128)
    {
      if (buffer_len == buffer_size - 1)
      {
        buffer_size *= 2;
        buffer = realloc(buffer, buffer_size);
      }
      buffer[buffer_len++] = c;
      buffer[buffer_len] = '\0';
    }
    if (callback)
      callback(buffer, c);
  }
}