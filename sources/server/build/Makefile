##
## Makefile for battletrantor in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../../Makefile.inc

NAME	=	btserv

CFLAGS	+=	-I../../includes/
LIBS	=	-ltools_`uname -m`-`uname -s` -L../../libs/

all:
	$(CC) *.o -o $(NAME) $(LIBS)
	$(MV) $(NAME) ../../$(BINDIR)/btserver/

clean:
	$(RM) *.o

fclean:	clean
	$(RM) $(NAME)

re:
	$(RM) $(NAME)
	$(MAKE) all
