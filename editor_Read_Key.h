#ifndef EDITOR_READ_KEY_H
#define EDITOR_READ_KEY_H

#define CTRL_KEY(k) ((k) & 0x1f)

// Function waits for one keypress and returns it later.
char editorReadKey();

#endif