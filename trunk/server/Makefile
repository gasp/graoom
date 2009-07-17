##
## Makefile for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../Makefile.inc

NAME	=	gserv

SOURCES	=	server.c		\
		loader.c		\
		errors.c		\
		log.c			\

CFLAGS	+=	-I../includes -I./network/

all:	$(OBJECTS)
	$(MV) $(OBJECTS) $(OBJDIR)
	$(MAKE) -C network $@
	$(MAKE) -C build $@

clean:
	$(RM) $(OBJECTS)
	$(MAKE) -C network $@
	$(MAKE) -C build $@

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) -C network $@
	$(MAKE) -C build $@

re:	fclean all
	$(MAKE) -C network $@
	$(MAKE) -C build $@
