# Introduction #

This is a place where anyone can share its ideas concerning the server side. Don't be shy, you are welcome!

# The tree #

The server has two subdirectories which are both dedicated to different purposes:
  * the **public/** directory contains informations that can be customised, most of server's configuration will go here (network port, number of players, ...). Every node in this directory can be altered, the server will try to run anyway. Note that it can also contains data which integrity will be checked (this is the case of maps for instance, which have a checksum in their header).
  * the **private/** directory, which contains data that **shall not be changed** (a checksum is performed on each item from these directory). Checksum is performed with constant pre-defined in the binary, these are build before creating a tarball. Typically, it will contains data required by the server to perform internal operations such as loading of ini files, default settings, checks, ...

# Main steps #

Here are the different steps which happen when the server is launched:

  * loading (see [Loader](Loader.md) for more informations), consisting of a primary load of ini files which contains configurations for each module, then loaded one by one, if something goes wrong, the server doesn't run and immediately go to the cleaner. This part is not crucial but requires a good organisation, so we won't focus on optimisation here, but on factoring.

  * execution (see [Loop](Loop.md)) where the main job is made. This is the crucial part of the program, if something is slow here, everything will be, so it requires a minimum of optimisations and good design. In this part of the program, we treat demands and call the appropriated module (a new connection, a player is moving, ...), this part must not bug whatever happen: no memory left, someone has crashed, fd is invalid, ..., nevermind.

  * cleaning up (see [Cleaner](Cleaner.md)) which cleans up memory, fds, sockets, ... before leaving the program.

# Error handler #

The current error handler works with a list of error codes (defined in errors.h/errors.c) with an associated message, and a flag which determine what will be done when raised.

This flag can be set to several combining values which will change the behavior of the server:

  * ERR\_T\_DISPLAY: the error will be output when in non-daemon mode
  * ERR\_T\_LOG: the error will be logged in an error file
  * ERR\_T\_DIE: the server will stop

Some additional flags may appear in the future.