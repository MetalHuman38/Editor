#ifndef APPEND_BUFFER_STRUCT_H
#define APPEND_BUFFER_STRUCT_H

// Definition of the appendBuffer structure.
struct appendBuffer
{
  char *b; // Pointer to a character buffer.
  int len; // Length of the buffer.
};

// Macro definition for initializing an instance of struct appendBuffer.
#define ABUF_INIT \
  {               \
    NULL, 0       \
  }

#endif