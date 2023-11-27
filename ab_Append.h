#ifndef AB_APPEND_H
#define AB_APPEND_H

// Include the necessary header file for the appendBuffer structure.
#include "append_Buffer_Struct.h"

// Function declaration for abAppend.
// This function is used to append a string of specified length to an appendBuffer.
// Parameters:
// - ab: A pointer to the appendBuffer structure.
// - s: A pointer to the string to be appended.
// - len: The length of the string to be appended.
void abAppend(struct appendBuffer *ab, const char *s, int len);

#endif