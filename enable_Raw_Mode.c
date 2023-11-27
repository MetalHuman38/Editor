#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "enable_Raw_Mode.h"
#include "disable_Raw_Mode.h"
#include "termios_setup.h"
#include "die.h"
#include "editorConfig.h"

// struct termios orig_termios;

void enableRawMode()
{

  if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
    die("tcsetattr");
  atexit(disableRawMode); // a_text_it() Registers disableRawMode() to be called automatically when program exits.
                          // this ensures to set terminal attributes back to default.

  struct termios raw = E.orig_termios; // Terminal attributes read into by tcgetattr(function)

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); // Disables ctrl S and Q. S normally stops data from
                                                            // transmitting(pause) and Q resumes
                                                            // process. turned off, S can read as 19 byte and Q as 17 byte. M can read as 13bytes. (BRKINT triggers SIGINT), (INPCK enables parity checking.), (ISTRIP strips 8th bit of each input.)

  raw.c_iflag &= ~(CS8); // (CS8 sets character size to 8bits per byte.)

  raw.c_iflag &= ~(OPOST); // Added parameter (OPOST flag) Turns off outputting process features. ("\r\n")

  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //  This is for local flags. <termios.h> refer to it as
                                                   //("dumping ground for other state")ECHO is a bit flag as 0000..1000 in binary
                                                   // Included parameters (ICANON), (IEXTEN) (ISIG) turn off signals.

  raw.c_cc[VMIN] = 0; // sets the minimum number of bytes of input needed before read() can return.
                      // Set to (0) so that read() returns as soon as there is any input to be read.

  raw.c_cc[VTIME] = 1; // sets the maximum amount of time to wait before read() returns. It is in tenths of a second.
                       // set to (1/10) of a second, or 100 milliseconds. If read() times out, it will return 0

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    die("tcsetattr"); // TCSAFLUSH argument specify when to apply the changes.
                      // Discards any unread input
}
