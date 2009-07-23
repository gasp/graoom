##
## Makefile for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../../Makefile.inc

SOURCES	=	graphic_parser.c		\
		graphic_init.c			\
		graphic_cleaner.c		\
		graphic_font.c			\
		graphic_thread.c		\
		graphic_texture.c		\

CFLAGS	+=	-I../../includes -I../includes/

all:	$(OBJECTS)
	$(CP) $(OBJECTS) ../$(OBJDIR)

clean:
	$(RM) $(OBJECTS)

fclean:	clean

re:	fclean all
