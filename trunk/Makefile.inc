##
## Makefile.inc for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:33:22 2009 Sebastien Rannou
## Last update Fri Jul  3 22:26:43 2009 Sebastien Rannou
##

# Binary settings

CC	=	gcc
RM	=	rm -rf
AR	=	ar
RANLIB	=	ranlib
MV	=	mv
MAKE	=	make
FIND	=	find

# Compilation settings

CFLAGS	+=	-W -Wall -pedantic -ansi -Wstrict-prototypes -Wno-error

# Compilation settings (dev)

CFLAGS	+=	 -ggdb3

# Shortcut

OBJECTS	=	$(SOURCES:.c=.o)

# Common rules

# First rule is default's one, let's all be that one

all:

# Flymake for emacs

check-syntax:
	$(CC) -W -Wall -pedantic -ansi -Wstrict-prototypes -fsyntax-only $(SRC) $(CFLAGS)