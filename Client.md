# Introduction #

The client has some common points with the server:

  * it uses the same error system
  * it's organized around modules
  * it uses the same way to load/clean modules

The main difference with the server is the fact that each modules is a thread, we do this to be able to do several thing without blocking the client (for instance, we can have a part of the code that catch network events while another part draws on the screen), that means that if an unexpected event occurs (network disconnection?), the client will continue to run as if nothing happened.

Here is the list of modules:
  1. graphic module, this is the most important module as it computes and display graphics, this module is not in threaded because opengl needs to be initialized in the same thread that the one which displays, as opengl is loaded in the main execution flow, after having launched other threads, the main flow becomes the opengl module.
  1. network module, this one performs a dialog with the server (threaded module).
  1. audio module, which plays sounds (threaded module)
  1. event module, which catch events and has associated actions (threaded module)

To have a cleaner code and an easy way to extend it, each module as it's own structure, and is the only one to access to it, when a module needs to modify informations used by other threads, they must lock a single mutex and modify the main structure of the soft: client\_t.
Each module has access to this structure and take care of the mutex before reading or writing it.