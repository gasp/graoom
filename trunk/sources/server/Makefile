##
## Makefile for battletrantor in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../Makefile.inc

all:
	$(MAKE) -C network $@
	$(MAKE) -C base $@
	$(MAKE) -C cmd $@
	$(MAKE) -C game $@
	$(MAKE) -C exec $@

	$(MAKE) -C build $@

clean:
	$(MAKE) -C network $@
	$(MAKE) -C base $@
	$(MAKE) -C cmd $@
	$(MAKE) -C game $@
	$(MAKE) -C exec $@

	$(MAKE) -C build $@

fclean:	clean
	$(MAKE) -C network $@
	$(MAKE) -C base $@
	$(MAKE) -C cmd $@
	$(MAKE) -C game $@
	$(MAKE) -C exec $@

	$(MAKE) -C build $@

re:	fclean all
