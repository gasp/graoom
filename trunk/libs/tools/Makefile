##
## Makefile for graoom in /home/rannou_s/Work/xoosh/libs/tools
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Mon Jun 29 23:05:50 2009 Sebastien Rannou
## Last update Wed Jul  1 22:30:26 2009 Sebastien Rannou
##

SOURCES		= 	lists.c
OBJECTS		=	$(SOURCES:.c=.o)

CFLAGS		+=	-W -Wall -pedantic -ansi -I../includes/

NAMELIB		=	libtools_`uname -m`-`uname -s`.a

all:			$(OBJECTS)
			ar r $(NAMELIB) $(OBJ)
			ranlib $(NAMELIB)
			mv $(NAMELIB) ../

clean:
			rm -rf $(OBJECTS)

fclean:			clean
			rm -rf $(NAMELIB) ../$(NAMELIB)

re:			fclean all
