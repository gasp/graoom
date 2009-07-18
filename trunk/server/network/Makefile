##
## Makefile for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../../Makefile.inc

SOURCES	=	cleaner.c		\
		parser.c		\
		init.c			\
		connection.c		\
		loop.c			\
		read.c			\
		client.c		\

CFLAGS	+=	-I../../includes -I../includes/

all:	$(OBJECTS)
	$(MV) $(OBJECTS) ../$(OBJDIR)

clean:
	$(RM) $(OBJECTS)

fclean:	clean

re:	fclean all
