#ifndef EDITOR_READ_KEY_H
#define EDITOR_READ_KEY_H

#define KILO_VERSION "0.0.1"
#define KILO_TAB_STOP 8

#define CTRL_KEY(k) ((k) & 0x1f)

// Function waits for one keypress and returns it later.
int editorReadKey();

#endif