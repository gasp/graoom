##
## Makefile for graoom in /home/rannou_s/Work/xoosh/libs/tools
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Mon Jun 29 23:05:50 2009 Sebastien Rannou
## Last update Fri Jul  3 22:26:53 2009 Sebastien Rannou
##

include		../../Makefile.inc

NAMELIB		=	libtools_`uname -m`-`uname -s`.a

SOURCES		= 	lists.c				\
			ini.c				\
			tools.c				\

CFLAGS		+=	-I../../includes/

all:	$(OBJECTS)
	$(AR) r $(NAMELIB) $(OBJECTS)
	$(RANLIB) $(NAMELIB)
	$(MV) $(NAMELIB) ../

clean:
	$(RM) $(OBJECTS) $(OBJECTS_TEST)

fclean:	clean
	$(RM) $(NAMELIB) ../$(NAMELIB) $(BIN_TEST)

re:	fclean all
