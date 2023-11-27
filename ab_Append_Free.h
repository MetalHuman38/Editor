#ifndef AB_APPEND_Free_H
#define AB_APPEND_Free_H

// Include the necessary header files for the appendBuffer structure and abAppend function.
#include "append_Buffer_Struct.h"
#include "ab_Append.h"

// Function declaration for abFree.
// This function is used to free the memory associated with an appendBuffer.
// Parameters:
// - ab: A pointer to the appendBuffer structure.
void abFree(struct appendBuffer *ab);

#endif