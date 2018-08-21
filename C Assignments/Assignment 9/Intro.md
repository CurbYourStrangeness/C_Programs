For this assignment, you will write a pair of C programs, a server and a client, to play a version of the classic Poker card game: 4 card poker

The Server:
Can create an array of 52 cards to represent a standard 52 card deck of playing cards 
card is a struct that you must define and must contain two pieces of information:
The cards' value: Ace, 2, 3, ... , 9, 10, Jack, Queen, King
The cards' suit: Diamonds, Hearts, Spades, Clubs – one (above) sequence in each suit
And initialize this array so that its elements form a random sequence of the 52 cards defined above.
Install a signal handler for SIGINT so that you can terminate your server – and do so gracefully: unlink the address-name; close file(s), free allocated memory, ect.
From the UNIX command line you type <ctrl> <c>, unless the server is running in the background – in which case you look up the (server's) process id using the ps command and then signal the process by typing kill -2 <pid>
Creates a socket, binds it to a address-name known by your client and goes into an infinite listen/accept loop:
Each connection request is accepted and then:
The resulting socket file descriptor is used to send the peer process a deck of “shuffled” cards.
The resulting socket file descriptor is closed.
Restore the original signal handler for SIGINT on exit.





The Client:
Creates a socket – can be unnamed / unbound
Request a connection to the known socket address-name of your server.
Obtain a deck of “shuffled” cards from the server.
Plays a card game (at least as challenging as 4 card poker) with its user:
The player starts with 100 chips (bank roll).
The following is then repeated until the player has no more chips or they wish to cash out:
The player is asked to place a bet [1, # of chips they have]
If there are enough cards left in the deck, then a 4 card “hand” is dealt from the deck and displayed 
Otherwise a request is made of the server for a new “shuffled” deck, and then a 4 card “hand” is dealt from the deck and displayed
A determination is made as to what the player wins, or if they lose and the bank roll is updated as follows:
4 of a Kind	:  20,825 times the bet + the bet back
Straight Flush	:  6,153 times the bet + the bet back
3 of a Kind	:  108 times the bet + the bet back
Straight 	:  98 times the bet + the bet back
2 Pair		:  96 times the bet + the bet back
Flush		:  96 times the bet + the bet back
Pair		:  3 times the bet + the bet back
anything else	:  loss of bet
A report indicating number of hands played, won, lost, and final bank roll is displayed 


Sample run:


Requirements:
You may not use the pipe() or the socketpair() functions to facilitate the inter-process communication.
You must write an appropriate Makefile that builds both of your programs server.c and client.c
You must test your programs on ale - running at least two clients against your server in secession. 
Your programs must be well written: proper error checking/handling (with descriptive messages); no memory leaks, and no resource leaks.

Notes:
You can run your server in the background and your client in the foreground for initial development.
You can also open multiple session terminals (xterm, telnet) and run one program in each – better for testing multiple clients.


