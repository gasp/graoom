##
## Makefile for BattleTrantor in /home/rannou_s/Work/battletrantor
## 
## Made by Sebastien Rannou
## Login   <rannou_s@epitech.net>
## 
## Started on  Wed Jul  1 22:38:14 2009 Sebastien Rannou
##

include sources/Makefile.inc

# There's probably a cleaner way to do this

all:
	$(MAKE) -C sources $@

clean:
	$(MAKE) -C sources $@

fclean:
	$(MAKE) -C sources $@
	$(RM) 	binaries/btclient/btclient
	$(RM) 	binaries/btserver/btserv

re:	fclean all

mr-proper:	fclean
	$(RM)	`$(FIND) . -name "*~"`
