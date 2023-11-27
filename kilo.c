#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
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

struct editorConfig E;

int main()
{
  enableRawMode();
  initEditor();

  // Prints out each bytes read into the console.
  while (1) // Program exit when q is included after every character.
  {
    editorRefreshScreen();
    editorProcessKeyPress();
  }

  return 0;
}