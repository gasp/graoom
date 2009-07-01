##
## Makefile.inc for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:33:22 2009 Sebastien Rannou
## Last update Wed Jul  1 22:52:00 2009 Sebastien Rannou
##

# Binary settings

CC	=	gcc -O3 -ggdb3
RM	=	rm -rf
AR	=	ar
RANLIB	=	ranlib
MV	=	mv
MAKE	=	make
FIND	=	find

# Compilation settings

CFLAGS	+=	-W -Wall -pedantic -ansi -Wstrict-prototypes -Wno-error

# Common rules

# Flymake for emacs

check-syntax:
	$(CC) -W -Wall -pedantic -ansi -Wstrict-prototypes -fsyntax-only $(SRC) $(CFLAGS)
