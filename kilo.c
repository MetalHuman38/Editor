#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdarg.h>
#include "enable_Raw_Mode.h"
#include "disable_Raw_Mode.h"
#include "termios_setup.h"
#include "die.h"
#include "editor_Read_Key.h"
#include "editor_Process_KeyPress.h"
#include "editor_Refresh_Screen.h"
#include "editorConfig.h"
#include "get_Windows_Size.h"
#include "init_Editor.h"
#include "append_Buffer_Struct.h"
#include "ab_Append.h"
#include "enum_Editor_Key.h"
#include "E_Row_TypeDef.h"
#include "editor_Open.h"
#include "editor_Set_Status_Message.h"
#include "editor_Draw_Message_Bar.h"

struct editorConfig E;

struct appendBugger;

int main(int argc, char *argv[])
{
  enableRawMode();
  initEditor();
  if (argc >= 2)
  {
    editorOpen(argv[1]);
  }

  editorSetStatusMessage("HELP: Ctrl-Q = quit");

  // Prints out each bytes read into the console.
  while (1) // Program exit when q is included after every character.
  {
    editorRefreshScreen();
    editorProcessKeyPress();
  }

  return 0;
}