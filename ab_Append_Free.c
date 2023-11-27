// Include standard C library headers.
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

// Include your custom header files.
#include "append_Buffer_Struct.h"
#include "ab_Append.h"

// Function definition for abFree.
// This function is used to free the memory associated with an appendBuffer.
// Parameters:
// - ab: A pointer to the appendBuffer structure.
void abFree(struct appendBuffer *ab)
{
  free(ab->b); // Free the memory pointed to by ab->b.
}