#define _XOPEN_SOURCE 700 // Or another appropriate value
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "append_Buffer_Struct.h"
#include "ab_Append.h"
#include "editorConfig.h"
#include "editor_Save.h"
#include "editor_Row_To_String.h"
#include "editor_Save.h"
#include "editor_Set_Status_Message.h"

void editorSave()
{
  if (E.filename == NULL)
    return;

  int len;
  char *buf = editorRowToString(&len);

  int fd = open(E.filename, O_RDWR | O_CREAT, 0644);
  if (fd != 1)
  {
    if (ftruncate(fd, len) != -1)
    {
      if (write(fd, buf, len) == len)
      {
        close(fd);
        free(buf);
        E.dirty_flag = 0;
        editorSetStatusMessage("%d bytes written to disk", len);
        return;
      }
    }
    close(fd);
  }
  free(buf);
  editorSetStatusMessage("Cant save! I/O error: %s", strerror(errno));
}