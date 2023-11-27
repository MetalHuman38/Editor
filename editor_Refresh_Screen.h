#ifndef EDITOR_REFRESH_SCREEN_H
#define EDITOR_REFRESH_SCREEN_H

// Function writes an escape sequence to the terminal. Escape sequence always start with an escape char(27) followed by a [ character. Purpose is to instruct terminal to do various text formatting tasks.(e.g coloring text, moving cursor around and clearing part of the screen.)
void editorRefreshScreen();

#endif