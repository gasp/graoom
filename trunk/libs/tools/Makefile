##
## Makefile for graoom in /home/rannou_s/Work/xoosh/libs/tools
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Mon Jun 29 23:05:50 2009 Sebastien Rannou
## Last update Wed Jul  1 22:37:47 2009 Sebastien Rannou
##

include		../../Makefile.inc

NAMELIB		=	libtools_`uname -m`-`uname -s`.a

SOURCES		= 	lists.c
OBJECTS		=	$(SOURCES:.c=.o)

CFLAGS		+=	-I../../includes/

all:			$(OBJECTS)
			$(AR) r $(NAMELIB) $(OBJ)
			$(RANLIB) $(NAMELIB)
			$(MV) $(NAMELIB) ../

clean:
			$(RM) $(OBJECTS)

fclean:			clean
			$(RM) $(NAMELIB) ../$(NAMELIB)

re:			fclean all
