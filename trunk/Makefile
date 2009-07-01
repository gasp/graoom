##
## Makefile for graoom in /home/rannou_s/Work/graoom
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
## Last update Wed Jul  1 22:50:01 2009 Sebastien Rannou
##

include Makefile.inc

# There's probably a cleaner way to do this

all:
	$(MAKE) -C libs $@
	$(MAKE) -C client $@
	$(MAKE) -C server $@

clean:
	$(MAKE) -C libs $@
	$(MAKE) -C client $@
	$(MAKE) -C server $@	

fclean:
	$(MAKE) -C libs $@
	$(MAKE) -C client $@
	$(MAKE) -C server $@

re:	fclean all

mr-proper:	fclean
	$(RM)	`$(FIND) . -name "*~"`
