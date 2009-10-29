##
## Makefile for battletrantor in /home/rannou_s/Work/xoosh/libs/tools
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Mon Jun 29 23:05:50 2009 Sebastien Rannou
##

include		../../Makefile.inc

NAMELIB		=	libmodels_`uname -m`-`uname -s`.a

SOURCES		= 	mdl.c			\

CFLAGS		+=	-I../../includes/ -I/usr/local/include/

all:	$(OBJECTS)
	$(AR) r $(NAMELIB) $(OBJECTS)
	$(RANLIB) $(NAMELIB)
	$(MV) $(NAMELIB) ../
	$(CP) ../$(NAMELIB) ../libmodels.a

clean:
	$(RM) $(OBJECTS) $(OBJECTS_TEST)

fclean:	clean
	$(RM) $(NAMELIB) ../$(NAMELIB) $(BIN_TEST)

re:	fclean all
