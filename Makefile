# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Executable name
EXE = kilo

# Source files and object files
SRC = kilo.c enable_Raw_Mode.c disable_Raw_Mode.c termios_setup.c die.c editor_Read_Key.c editor_Process_KeyPress.c editor_Refresh_Screen.c editor_Draw_Rows.c get_Windows_Size.c init_Editor.c get_Cursor_Position.c ab_Append.c ab_Append_Free.c editor_Move_Cursor.c editor_Open.c editor_Insert_Row.c editor_Scroll.c editor_Update_Row.c editorRow_CursorX_To_RenderX.c editor_Draw_StatusBar.c editor_Set_Status_Message.c editor_Draw_Message_Bar.c editor_Row_Insert_Char.c editor_Insert_Char.c editor_Row_To_String.c editor_Save.c editor_Row_Delete_Char.c editor_Delete_Char.c editor_Delete_Row.c editor_Free_Row.c editor_Row_Append_String.c editor_Insert_New_Line.c editor_Prompt.c editor_Find.c editorRow_RenderX_To_CursorX.c editor_Find_Call_Back.c editor_Update_Syntax.c editor_Syntax_To_Color.c is_Separator.c editor_Select_Syntax_Highlight.c
OBJ = $(SRC:.c=.o)

# Targets
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(CFLAGS)

# Pattern rule to compile source files to object files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXE) $(OBJ)

