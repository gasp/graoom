##
## Makefile for battletrantor in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
## Last update Sat Sep  5 14:56:45 2009 Sebastien Rannou
##

include ../Makefile.inc

# There's probably a cleaner way to do this

all:
	$(MAKE) -C lists $@
	$(MAKE) -C ini $@
	$(MAKE) -C tools $@

clean:
	$(MAKE) -C lists $@
	$(MAKE) -C ini $@
	$(MAKE) -C tools $@

fclean:
	$(MAKE) -C lists $@
	$(MAKE) -C ini $@
	$(MAKE) -C tools $@

re:	fclean all

mr-proper:	fclean
	$(RM)	`$(FIND) . -name "*~"`
