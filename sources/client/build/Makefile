##
## Makefile for battletrantor in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../../Makefile.inc

NAME	=	btclient

CFLAGS	+=	-I../../includes/ -I/usr/local/include/
LIBS	=	-L../../libs/ -lSDL -lSDL_net	\
		-lSDL_ttf -ltools -lSDL_console	\
		-lGL -lGLU -lSDL_image		\
		-lmodels			\
		-L/usr/local/lib/

all:
	$(CC) *.o -o $(NAME) $(LIBS)
	$(MV) $(NAME) ../../$(BINDIR)/btclient/

clean:
	$(RM) *.o

fclean:	clean
	$(RM) $(NAME)

re:
	$(RM) $(NAME)
	$(MAKE) all
