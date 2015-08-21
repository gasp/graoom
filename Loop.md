# Introduction #

This is the main part of the server, it requires optimizations and stability.

Here's how it works:

```
[loop]
     [initialization of select]
     [select]
     [is there activity?]
        [yes]
           [read activity from a client] -> commands, disconnections, ...
           [write] -> informations, ...
        [no]
           [let us check on a todo list what we have to do since] -> actions associated with a timer
[/loop]
```