##
## Makefile for graoom in /home/rannou_s/Work/graoom/test/lists
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Fri Jul  3 22:26:00 2009 Sebastien Rannou
## Last update Fri Jul  3 23:14:52 2009 Sebastien Rannou
##

include ../../Makefile.inc

SOURCES		=	main.c

CFLAGS		+=	-I../../includes/
LDFLAGS		+=	-L../../libs
NAME		=	ini

all:	$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(NAME) -ltools_`uname -m`-`uname -s`

clean: 
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	$(MAKE) all
	php run.php
