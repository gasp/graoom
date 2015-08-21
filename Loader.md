# Introduction #

The server's loader is the first step in the execution of the program. Its goals are to initialize everything in a way that allows to add easily new modules.

# How it works #

The loader is composed of three parts:

  1. Checking of data integrity, this checks all internal files that must not be changed by the user (they are in private's directory)

  1. Loading of configuration files, these files are all present under **public/** directory. They are managed by a primary file called loader.ini, which contain the list of secondary ini files to load. During this part, everything is checked, if there's an error, we raise it with an explicit message.

  1. Initialization of each modules (network, game, ...).

If the loader fails in any of these parts, the server doesn't try to host a game, and directly jumps to the cleaner so as to destroy all was previously set before the error raised.