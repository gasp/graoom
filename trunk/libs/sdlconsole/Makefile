##
## Makefile for graoom in /home/rannou_s/Work/xoosh/libs/tools
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Mon Jun 29 23:05:50 2009 Sebastien Rannou
##

include		../../Makefile.inc

NAMELIB		=	libSDL_console_`uname -m`-`uname -s`.a

SOURCES		= 	internal.c		\
			DT_drawtext.c		\
			SDL_console.c		\

CFLAGS		+=	-I../../includes/ -I/

all:	$(OBJECTS)
	$(AR) r $(NAMELIB) $(OBJECTS)
	$(RANLIB) $(NAMELIB)
	$(MV) $(NAMELIB) ../
	$(CP) ../$(NAMELIB) ../libSDL_console.a

clean:
	$(RM) $(OBJECTS)

fclean:	clean
	$(RM) $(NAMELIB) ../$(NAMELIB) $(BIN_TEST)

re:	fclean all
