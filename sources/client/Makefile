##
## Makefile for BattleTrantor in /home/rannou_s/Work/battletrantor
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include ../Makefile.inc

all:
	$(MAKE) -C audio $@
	$(MAKE) -C base $@
	$(MAKE) -C event $@
	$(MAKE) -C graphic $@
	$(MAKE) -C network $@

	$(MAKE) -C build $@

clean:
	$(MAKE) -C audio $@
	$(MAKE) -C base $@
	$(MAKE) -C event $@
	$(MAKE) -C graphic $@
	$(MAKE) -C network $@

	$(MAKE) -C build $@

fclean:	clean
	$(MAKE) -C audio $@
	$(MAKE) -C base $@
	$(MAKE) -C event $@
	$(MAKE) -C graphic $@
	$(MAKE) -C network $@
	$(MAKE) -C base $@

	$(MAKE) -C build $@

re:	fclean all
