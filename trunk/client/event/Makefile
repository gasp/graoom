##
## Makefile for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../../Makefile.inc

SOURCES	=	event_parser.c		\
		event_init.c		\
		event_cleaner.c		\
		event_thread.c		\
		event_behavior.c	\
		event_play.c		\
		event_console.c		\

CFLAGS	+=	-I../../includes -I../includes/

all:	$(OBJECTS)
	$(CP) $(OBJECTS) ../$(OBJDIR)

clean:
	$(RM) $(OBJECTS)

fclean:	clean

re:	fclean all
