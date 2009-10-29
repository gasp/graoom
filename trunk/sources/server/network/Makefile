##
## Makefile for battletrantor in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../../Makefile.inc

SOURCES	=	network_cleaner.c	\
		network_parser.c	\
		network_init.c		\
		network_connection.c	\
		network_loop.c		\
		network_read.c		\
		network_write.c		\
		network_client.c	\

CFLAGS	+=	-I../../includes -I../includes/

all:	$(OBJECTS)
	$(CP) $(OBJECTS) ../$(OBJDIR)

clean:
	$(RM) $(OBJECTS)

fclean:	clean

re:	fclean all
