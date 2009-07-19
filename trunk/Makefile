##
## Makefile for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include Makefile.inc

# There's probably a cleaner way to do this

all:
	$(MAKE) -C libs $@
	$(MAKE) -C client $@
	$(MAKE) -C server $@
	$(MAKE) -C test $@

clean:
	$(MAKE) -C libs $@
	$(MAKE) -C client $@
	$(MAKE) -C server $@	
	$(MAKE) -C test $@

fclean:
	$(MAKE) -C libs $@
	$(MAKE) -C client $@
	$(MAKE) -C server $@
	$(MAKE) -C test $@

re:	fclean all

mr-proper:	fclean
	$(RM)	`$(FIND) . -name "*~"`
