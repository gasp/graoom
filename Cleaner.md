# Introduction #

The cleaner is the last step in the execution flow, it cleans up memory, fds, ...

# Details #

For each module there's an associated sub-cleaner which is called at the end of the execution, it has to clean everything that was allocated by the loader of the module. In case a sub-cleaner raises errors, the cleaner ignores them and continue to call other sub-cleaners, that may cause undefined behaviors in some cases, but as the code is quite 'closed' between each module, we can expect other sub-cleaners to continue without problems.

The error modules cleans up itself with a atexit() call, so we can raise errors in this part of the code without problems.