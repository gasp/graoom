##
## Makefile for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
## Last update Fri Jul  3 23:08:41 2009 Sebastien Rannou
##

include ../Makefile.inc

# There's probably a cleaner way to do this

all:
	$(MAKE) -C lists $@

clean:
	$(MAKE) -C lists $@

fclean:
	$(MAKE) -C lists $@

re:	fclean all

test:
	$(MAKE) -C lists $@

mr-proper:	fclean
	$(RM)	`$(FIND) . -name "*~"`
