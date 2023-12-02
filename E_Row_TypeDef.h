#ifndef E_ROW_TYPEDEF_H
#define E_ROW_TYPEDEF_H

typedef struct e_row
{
  int size;
  int rsize;
  char *chars;
  char *render;
  unsigned char *highlighting;
} e_row;

#endif