# Introduction #

The protocol defines a way to communicate between the server and clients. It handles different types of clients, which have their own specific commands. We will describe here the synthax used in the protocol, and some conventions.


# Details #

## The connection ##

The connection consists of a primary dialog which aims at defining the way the communication will occur. This part will be described later.

## The communication ##

Once the communication has been initialized, the client is connected to the server and a communication takes place. This communication can be of different types, according to the nature of the client. Basically, the client and the server use the same way to communicate:

```
type:data\n
```

This synthax is used into both ways, that means that the server use it to send informations, here 'type' means the nature of the data, here is an example:

```
player_position:32:2.32:234:42\n
```

When the client sends a request, the same synthax is used, but the meaning of 'type' is different, it designs the name of the command, here is an example:

```
talk:Hi guys!
```