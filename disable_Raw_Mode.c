#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "disable_Raw_Mode.h"
#include "enable_Raw_Mode.h"
#include "termios_setup.h"
#include "die.h"
#include "editorConfig.h"

void disableRawMode()
{

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
    die("tcsetattr");
}
