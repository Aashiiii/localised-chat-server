It was not specidied in the assignment specification that the domain, and
identifier name in the message would always start at a specific position.
We only know that it can be 256 characters.
Hence, I am considering that they can start, and end at any position in that
range.

The cases when the client is inactive, are handled by PING PONG.
PING PONG disconnects the client if inactive, and cleans the zombie processes.


