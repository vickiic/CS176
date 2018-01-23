Vicki Chen - 8757122
Ziheng Song - 9311630
Date: 12/8/17

CS 176A HW5 Programming Assignment
Hangman game using C

Server
-- in the main a tcp socket is established for communication with the server.
-- then the incoming client connections are established in multiple threads with a limit of 3 threads at a time.
-- print_thread_id is the function that is defined for each thread to communicate with the client.
-- getRand() generates a random number 0-14
-- checkGuess() is used to check the guess made by the client with the remaining words.
-- checkWin() is used to check whether the user won or not.

client
-- a tcp socket is established by using the arguments.
-- then the game proceeds according to the rules in the main loop until the user wins or run outs of 6 tries.
-- The client communicates with the server by sending a valid guess each turn and receiving remaining
trivial parts of the word to guess.
-- checkGuess() and checkWin() have the same functionality.
