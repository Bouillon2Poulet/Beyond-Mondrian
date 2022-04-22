CC			= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS= -lSDL2 -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers main
OBJ_MAIN= main.o
EXEC_MAIN= main.out

# Regles compilation

all :

main : $(OBJDIR)$(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_MAIN) -o $(BINDIR)$(EXEC_MAIN) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
