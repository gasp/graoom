
##
## Makefile for battletrantor in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../../Makefile.inc

SOURCES	=	base_client.c		\
		base_errors.c		\
		base_loader.c		\
		base_threads.c		\
		base_vectors.c		\

CFLAGS	+=	-I../../includes -I../includes/ -I/usr/local/include/

all:	$(OBJECTS)
	$(CP) $(OBJECTS) ../$(OBJDIR)

clean:
	$(RM) $(OBJECTS)

fclean:	clean

re:	fclean all
