#ifndef E_ROW_TYPEDEF_H
#define E_ROW_TYPEDEF_H

typedef struct e_row
{
  int idx;
  int size;
  int rsize;
  char *chars;
  char *render;
  unsigned char *highlighting;
  int highlight_open_comment;
} e_row;

#endif